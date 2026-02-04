#pragma once

// Created on: 2016-07-07
// Copyright (c) 2016 OPEN CASCADE SAS
// Created by: Oleg AGASHIN
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// Created on: 2016-07-07
// Copyright (c) 2016 OPEN CASCADE SAS
// Created by: Oleg AGASHIN
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


#include <BRepMesh_Classifier.hpp>
#include <IMeshData_Wire.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshData_PCurve.hpp>
#include <BRepMesh_Vertex.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Vertex.hpp>
#include <BRep_Tool.hpp>
#include <Standard_ErrorHandler.hpp>
#include <BRepMesh_Delaun.hpp>

//! Extends base meshing algo in order to enable possibility
//! of addition of free vertices into the mesh.
template <class RangeSplitter, class BaseAlgo>
class BRepMesh_NodeInsertionMeshAlgo : public BaseAlgo
{
public:
  //! Constructor.
  BRepMesh_NodeInsertionMeshAlgo() = default;

  //! Destructor.
  ~BRepMesh_NodeInsertionMeshAlgo() override = default;

  //! Performs processing of the given face.
  void Perform(const IMeshData::IFaceHandle& theDFace,
               const IMeshTools_Parameters&  theParameters,
               const Message_ProgressRange&  theRange) override
  {
    myRangeSplitter.Reset(theDFace, theParameters);
    myClassifier = new BRepMesh_Classifier;
    if (!theRange.More())
    {
      return;
    }
    BaseAlgo::Perform(theDFace, theParameters, theRange);
    myClassifier.Nullify();
  }

protected:
  typedef NCollection_Shared<NCollection_Sequence<const gp_Pnt2d*>> SequenceOfPnt2d;

  //! Performs initialization of data structure using existing model data.
  bool initDataStructure() override
  {
    occ::handle<NCollection_IncAllocator> aTmpAlloc = new NCollection_IncAllocator;

    const IMeshData::IFaceHandle&                    aDFace = this->getDFace();
    NCollection_Array1<occ::handle<SequenceOfPnt2d>> aWires(0, aDFace->WiresNb() - 1);
    for (int aWireIt = 0; aWireIt < aDFace->WiresNb(); ++aWireIt)
    {
      const IMeshData::IWireHandle& aDWire = aDFace->GetWire(aWireIt);
      if (aDWire->IsSet(IMeshData_SelfIntersectingWire)
          || (aDWire->IsSet(IMeshData_OpenWire) && aWireIt != 0))
      {
        continue;
      }

      aWires(aWireIt) = collectWirePoints(aDWire, aTmpAlloc);
    }

    myRangeSplitter.AdjustRange();
    if (!myRangeSplitter.IsValid())
    {
      aDFace->SetStatus(IMeshData_Failure);
      return false;
    }

    const std::pair<double, double>& aDelta    = myRangeSplitter.GetDelta();
    const std::pair<double, double>& aTolUV    = myRangeSplitter.GetToleranceUV();
    const double                     uCellSize = 14.0 * aTolUV.first;
    const double                     vCellSize = 14.0 * aTolUV.second;

    this->getStructure()->Data()->SetCellSize(uCellSize / aDelta.first, vCellSize / aDelta.second);
    this->getStructure()->Data()->SetTolerance(aTolUV.first / aDelta.first,
                                               aTolUV.second / aDelta.second);

    for (int aWireIt = 0; aWireIt < aDFace->WiresNb(); ++aWireIt)
    {
      const occ::handle<SequenceOfPnt2d>& aWire = aWires(aWireIt);
      if (!aWire.IsNull() && !aWire->IsEmpty())
      {
        myClassifier->RegisterWire(*aWire,
                                   aTolUV,
                                   myRangeSplitter.GetRangeU(),
                                   myRangeSplitter.GetRangeV());
      }
    }

    if (this->getParameters().InternalVerticesMode)
    {
      insertInternalVertices();
    }

    return BaseAlgo::initDataStructure();
  }

  //! Adds the given 2d point to mesh data structure.
  //! Returns index of node in the structure.
  int addNodeToStructure(const gp_Pnt2d&                thePoint,
                         const int                      theLocation3d,
                         const BRepMesh_DegreeOfFreedom theMovability,
                         const bool                     isForceAdd) override
  {
    return BaseAlgo::addNodeToStructure(myRangeSplitter.Scale(thePoint, true),
                                        theLocation3d,
                                        theMovability,
                                        isForceAdd);
  }

  //! Returns 2d point associated to the given vertex.
  gp_Pnt2d getNodePoint2d(const BRepMesh_Vertex& theVertex) const override
  {
    return myRangeSplitter.Scale(theVertex.Coord(), false);
  }

  //! Returns range splitter.
  const RangeSplitter& getRangeSplitter() const { return myRangeSplitter; }

  //! Returns classifier.
  const occ::handle<BRepMesh_Classifier>& getClassifier() const { return myClassifier; }

private:
  //! Creates collection of points representing discrete wire.
  occ::handle<SequenceOfPnt2d> collectWirePoints(
    const IMeshData::IWireHandle&                theDWire,
    const occ::handle<NCollection_IncAllocator>& theAllocator)
  {
    occ::handle<SequenceOfPnt2d> aWirePoints = new SequenceOfPnt2d(theAllocator);
    for (int aEdgeIt = 0; aEdgeIt < theDWire->EdgesNb(); ++aEdgeIt)
    {
      const IMeshData::IEdgeHandle    aDEdge = theDWire->GetEdge(aEdgeIt);
      const IMeshData::IPCurveHandle& aPCurve =
        aDEdge->GetPCurve(this->getDFace().get(), theDWire->GetEdgeOrientation(aEdgeIt));

      int aPointIt, aEndIndex, aInc;
      if (aPCurve->IsForward())
      {
        // For an infinite cylinder (for example)
        // aPCurve->ParametersNb() == 0

        aEndIndex = aPCurve->ParametersNb() - 1;
        aPointIt  = (std::min)(0, aEndIndex);
        aInc      = 1;
      }
      else
      {
        // For an infinite cylinder (for example)
        // aPCurve->ParametersNb() == 0

        aPointIt  = aPCurve->ParametersNb() - 1;
        aEndIndex = (std::min)(0, aPointIt);
        aInc      = -1;
      }

      // For an infinite cylinder (for example)
      // this cycle will not be executed.
      for (; aPointIt != aEndIndex; aPointIt += aInc)
      {
        const gp_Pnt2d& aPnt2d = aPCurve->GetPoint(aPointIt);
        aWirePoints->Append(&aPnt2d);
        myRangeSplitter.AddPoint(aPnt2d);
      }
    }

    return aWirePoints;
  }

  //! Iterates over internal vertices of a face and
  //! creates corresponding nodes in data structure.
  void insertInternalVertices()
  {
    TopExp_Explorer aExplorer(this->getDFace()->GetFace(), TopAbs_VERTEX, TopAbs_EDGE);
    for (; aExplorer.More(); aExplorer.Next())
    {
      const TopoDS_Vertex& aVertex = TopoDS::Vertex(aExplorer.Current());
      if (aVertex.Orientation() != TopAbs_INTERNAL)
      {
        continue;
      }

      insertInternalVertex(aVertex);
    }
  }

  //! Inserts the given vertex into mesh.
  void insertInternalVertex(const TopoDS_Vertex& theVertex)
  {
    try
    {
      OCC_CATCH_SIGNALS

      gp_Pnt2d aPnt2d = BRep_Tool::Parameters(theVertex, this->getDFace()->GetFace());
      // check UV values for internal vertices
      if (myClassifier->Perform(aPnt2d) != TopAbs_IN)
        return;

      this->registerNode(BRep_Tool::Pnt(theVertex), aPnt2d, BRepMesh_Fixed, false);
    }
    catch (Standard_Failure const&)
    {
    }
  }

private:
  RangeSplitter                    myRangeSplitter;
  occ::handle<BRepMesh_Classifier> myClassifier;
};


#include <BRepMesh_GeomTool.hpp>

//! Extends base Delaunay meshing algo in order to enable possibility
//! of addition of free vertices and internal nodes into the mesh.
template <class RangeSplitter, class BaseAlgo>
class BRepMesh_DelaunayNodeInsertionMeshAlgo
    : public BRepMesh_NodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
{
private:
  // Typedef for OCCT RTTI
  typedef BRepMesh_NodeInsertionMeshAlgo<RangeSplitter, BaseAlgo> InsertionBaseClass;

public:
  //! Constructor.
  BRepMesh_DelaunayNodeInsertionMeshAlgo()
      : myIsPreProcessSurfaceNodes(false)
  {
  }

  //! Destructor.
  ~BRepMesh_DelaunayNodeInsertionMeshAlgo() override = default;

  //! Returns PreProcessSurfaceNodes flag.
  bool IsPreProcessSurfaceNodes() const { return myIsPreProcessSurfaceNodes; }

  //! Sets PreProcessSurfaceNodes flag.
  //! If TRUE, registers surface nodes before generation of base mesh.
  //! If FALSE, inserts surface nodes after generation of base mesh.
  void SetPreProcessSurfaceNodes(const bool isPreProcessSurfaceNodes)
  {
    myIsPreProcessSurfaceNodes = isPreProcessSurfaceNodes;
  }

protected:
  //! Performs initialization of data structure using existing model data.
  bool initDataStructure() override
  {
    if (!InsertionBaseClass::initDataStructure())
    {
      return false;
    }

    if (myIsPreProcessSurfaceNodes)
    {
      const Handle(IMeshData::ListOfPnt2d) aSurfaceNodes =
        this->getRangeSplitter().GenerateSurfaceNodes(this->getParameters());

      registerSurfaceNodes(aSurfaceNodes);
    }

    return true;
  }

  //! Returns size of cell to be used by acceleration circles grid structure.
  std::pair<int, int> getCellsCount(const int theVerticesNb) override
  {
    return BRepMesh_GeomTool::CellsCount(this->getDFace()->GetSurface(),
                                         theVerticesNb,
                                         this->getDFace()->GetDeflection(),
                                         &this->getRangeSplitter());
  }

  //! Performs processing of generated mesh. Generates surface nodes and inserts them into
  //! structure.
  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    if (!theRange.More())
    {
      return;
    }
    // clang-format off
    InsertionBaseClass::postProcessMesh (theMesher, Message_ProgressRange()); // shouldn't be range passed here?
    // clang-format on

    if (!myIsPreProcessSurfaceNodes)
    {
      const Handle(IMeshData::ListOfPnt2d) aSurfaceNodes =
        this->getRangeSplitter().GenerateSurfaceNodes(this->getParameters());

      insertNodes(aSurfaceNodes, theMesher, theRange);
    }
  }

  //! Inserts nodes into mesh.
  bool insertNodes(const Handle(IMeshData::ListOfPnt2d)& theNodes,
                   BRepMesh_Delaun&                      theMesher,
                   const Message_ProgressRange&          theRange)
  {
    if (theNodes.IsNull() || theNodes->IsEmpty())
    {
      return false;
    }

    IMeshData::VectorOfInteger       aVertexIndexes(theNodes->Size(), this->getAllocator());
    IMeshData::ListOfPnt2d::Iterator aNodesIt(*theNodes);
    for (int aNodeIt = 1; aNodesIt.More(); aNodesIt.Next(), ++aNodeIt)
    {
      const gp_Pnt2d& aPnt2d = aNodesIt.Value();
      if (this->getClassifier()->Perform(aPnt2d) == TopAbs_IN)
      {
        aVertexIndexes.Append(
          this->registerNode(this->getRangeSplitter().Point(aPnt2d), aPnt2d, BRepMesh_Free, false));
      }
    }

    theMesher.AddVertices(aVertexIndexes, theRange);
    if (!theRange.More())
    {
      return false;
    }
    return !aVertexIndexes.IsEmpty();
  }

private:
  //! Registers surface nodes in data structure.
  bool registerSurfaceNodes(const Handle(IMeshData::ListOfPnt2d)& theNodes)
  {
    if (theNodes.IsNull() || theNodes->IsEmpty())
    {
      return false;
    }

    bool                             isAdded = false;
    IMeshData::ListOfPnt2d::Iterator aNodesIt(*theNodes);
    for (int aNodeIt = 1; aNodesIt.More(); aNodesIt.Next(), ++aNodeIt)
    {
      const gp_Pnt2d& aPnt2d = aNodesIt.Value();
      if (this->getClassifier()->Perform(aPnt2d) == TopAbs_IN)
      {
        isAdded = true;
        this->registerNode(this->getRangeSplitter().Point(aPnt2d), aPnt2d, BRepMesh_Free, false);
      }
    }

    return isAdded;
  }

private:
  bool myIsPreProcessSurfaceNodes;
};


#include <BRepMesh_GeomTool.hpp>
#include <GeomLib.hpp>

//! Extends node insertion Delaunay meshing algo in order to control
//! deflection of generated triangles. Splits triangles failing the check.
template <class RangeSplitter, class BaseAlgo>
class BRepMesh_DelaunayDeflectionControlMeshAlgo
    : public BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
{
private:
  // Typedef for OCCT RTTI
  typedef BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
    DelaunayInsertionBaseClass;

public:
  //! Constructor.
  BRepMesh_DelaunayDeflectionControlMeshAlgo()
      : myMaxSqDeflection(-1.),
        mySqMinSize(-1.),
        myIsAllDegenerated(false),
        myCircles(nullptr)
  {
  }

  //! Destructor.
  ~BRepMesh_DelaunayDeflectionControlMeshAlgo() override = default;

protected:
  //! Performs processing of generated mesh. Generates surface nodes and inserts them into
  //! structure.
  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    Message_ProgressScope aPS(theRange, "Post process mesh", 2);
    // Insert surface nodes.
    DelaunayInsertionBaseClass::postProcessMesh(theMesher, aPS.Next());
    if (!aPS.More())
    {
      return;
    }

    if (this->getParameters().ControlSurfaceDeflection
        && this->getStructure()->ElementsOfDomain().Extent() > 0)
    {
      optimizeMesh(theMesher, aPS.Next());
    }
    else
    {
      aPS.Next();
    }
  }

  //! Checks deviation of a mesh from geometrical surface.
  //! Inserts additional nodes in case of huge deviation.
  virtual void optimizeMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange)
  {
    occ::handle<NCollection_IncAllocator> aTmpAlloc =
      new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE);

    mySqMinSize = this->getParameters().MinSize * this->getParameters().MinSize;
    myCouplesMap =
      new IMeshData::MapOfOrientedEdges(3 * this->getStructure()->ElementsOfDomain().Extent(),
                                        aTmpAlloc);
    myControlNodes = new IMeshData::ListOfPnt2d(aTmpAlloc);
    myCircles      = &theMesher.Circles();

    const int             aIterationsNb = 11;
    bool                  isInserted    = true;
    Message_ProgressScope aPS(theRange, "Iteration", aIterationsNb);
    for (int aPass = 1; aPass <= aIterationsNb && isInserted && !myIsAllDegenerated; ++aPass)
    {
      if (!aPS.More())
      {
        return;
      }
      // Reset stop condition
      myMaxSqDeflection  = -1.;
      myIsAllDegenerated = true;
      myControlNodes->Clear();

      if (this->getStructure()->ElementsOfDomain().Extent() < 1)
      {
        break;
      }
      // Iterate on current triangles
      IMeshData::IteratorOfMapOfInteger aTriangleIt(this->getStructure()->ElementsOfDomain());
      for (; aTriangleIt.More(); aTriangleIt.Next())
      {
        const BRepMesh_Triangle& aTriangle = this->getStructure()->GetElement(aTriangleIt.Key());
        splitTriangleGeometry(aTriangle);
      }

      isInserted = this->insertNodes(myControlNodes, theMesher, aPS.Next());
    }

    myCouplesMap.Nullify();
    myControlNodes.Nullify();

    if (!(myMaxSqDeflection < 0.))
    {
      this->getDFace()->SetDeflection(std::sqrt(myMaxSqDeflection));
    }
  }

private:
  //! Contains geometrical data related to node of triangle.
  struct TriangleNodeInfo
  {
    TriangleNodeInfo()
        : isFrontierLink(false)
    {
    }

    gp_XY  Point2d;
    gp_XYZ Point;
    bool   isFrontierLink;
  };

  //! Functor computing deflection of a point from surface.
  class NormalDeviation
  {
  public:
    NormalDeviation(const gp_Pnt& theRefPnt, const gp_Vec& theNormal)
        : myRefPnt(theRefPnt),
          myNormal(theNormal)
    {
    }

    double SquareDeviation(const gp_Pnt& thePoint) const
    {
      const double aDeflection = std::abs(myNormal.Dot(gp_Vec(myRefPnt, thePoint)));
      return aDeflection * aDeflection;
    }

  private:
    NormalDeviation(const NormalDeviation& theOther) = delete;

    void operator=(const NormalDeviation& theOther) = delete;

  private:
    const gp_Pnt& myRefPnt;
    const gp_Vec& myNormal;
  };

  //! Functor computing deflection of a point on triangle link from surface.
  class LineDeviation
  {
  public:
    LineDeviation(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2)
        : myPnt1(thePnt1),
          myPnt2(thePnt2)
    {
    }

    double SquareDeviation(const gp_Pnt& thePoint) const
    {
      return BRepMesh_GeomTool::SquareDeflectionOfSegment(myPnt1, myPnt2, thePoint);
    }

  private:
    LineDeviation(const LineDeviation& theOther) = delete;

    void operator=(const LineDeviation& theOther) = delete;

  private:
    const gp_Pnt& myPnt1;
    const gp_Pnt& myPnt2;
  };

  //! Returns nodes info of the given triangle.
  void getTriangleInfo(const BRepMesh_Triangle& theTriangle,
                       const int (&theNodesIndices)[3],
                       TriangleNodeInfo (&theInfo)[3]) const
  {
    const int (&e)[3] = theTriangle.myEdges;
    for (int i = 0; i < 3; ++i)
    {
      const BRepMesh_Vertex& aVertex = this->getStructure()->GetNode(theNodesIndices[i]);
      theInfo[i].Point2d             = this->getRangeSplitter().Scale(aVertex.Coord(), false).XY();
      theInfo[i].Point               = this->getNodesMap()->Value(aVertex.Location3d()).XYZ();
      theInfo[i].isFrontierLink =
        (this->getStructure()->GetLink(e[i]).Movability() == BRepMesh_Frontier);
    }
  }

  // Check geometry of the given triangle. If triangle does not suit specified deflection, inserts
  // new point.
  void splitTriangleGeometry(const BRepMesh_Triangle& theTriangle)
  {
    if (theTriangle.Movability() != BRepMesh_Deleted)
    {
      int aNodexIndices[3];
      this->getStructure()->ElementNodes(theTriangle, aNodexIndices);

      TriangleNodeInfo aNodesInfo[3];
      getTriangleInfo(theTriangle, aNodexIndices, aNodesInfo);

      gp_Vec aNormal;
      gp_Vec aLinkVec[3];
      if (computeTriangleGeometry(aNodesInfo, aLinkVec, aNormal))
      {
        myIsAllDegenerated = false;

        const gp_XY aCenter2d =
          (aNodesInfo[0].Point2d + aNodesInfo[1].Point2d + aNodesInfo[2].Point2d) / 3.;

        usePoint(aCenter2d, NormalDeviation(aNodesInfo[0].Point, aNormal));
        splitLinks(aNodesInfo, aNodexIndices);
      }
    }
  }

  //! Updates array of links vectors.
  //! @return False on degenerative triangle.
  bool computeTriangleGeometry(const TriangleNodeInfo (&theNodesInfo)[3],
                               gp_Vec (&theLinks)[3],
                               gp_Vec& theNormal)
  {
    if (checkTriangleForDegenerativityAndGetLinks(theNodesInfo, theLinks))
    {
      if (checkTriangleArea2d(theNodesInfo))
      {
        if (computeNormal(theLinks[0], theLinks[1], theNormal))
        {
          return true;
        }
      }
    }

    return false;
  }

  //! Updates array of links vectors.
  //! @return False on degenerative triangle.
  bool checkTriangleForDegenerativityAndGetLinks(const TriangleNodeInfo (&theNodesInfo)[3],
                                                 gp_Vec (&theLinks)[3])
  {
    const double MinimalSqLength3d = 1.e-12;
    for (int i = 0; i < 3; ++i)
    {
      theLinks[i] = theNodesInfo[(i + 1) % 3].Point - theNodesInfo[i].Point;
      if (theLinks[i].SquareMagnitude() < MinimalSqLength3d)
      {
        return false;
      }
    }

    return true;
  }

  //! Checks area of triangle in parametric space for degenerativity.
  //! @return False on degenerative triangle.
  bool checkTriangleArea2d(const TriangleNodeInfo (&theNodesInfo)[3])
  {
    const gp_Vec2d aLink2d1(theNodesInfo[0].Point2d, theNodesInfo[1].Point2d);
    const gp_Vec2d aLink2d2(theNodesInfo[1].Point2d, theNodesInfo[2].Point2d);

    const double MinimalArea2d = 1.e-9;
    return (std::abs(aLink2d1 ^ aLink2d2) > MinimalArea2d);
  }

  //! Computes normal using two link vectors.
  //! @return True on success, False in case of normal of null magnitude.
  bool computeNormal(const gp_Vec& theLink1, const gp_Vec& theLink2, gp_Vec& theNormal)
  {
    const gp_Vec aNormal(theLink1 ^ theLink2);
    if (aNormal.SquareMagnitude() > gp::Resolution())
    {
      theNormal = aNormal.Normalized();
      return true;
    }

    return false;
  }

  //! Computes deflection of midpoints of triangles links.
  //! @return True if point fits specified deflection.
  void splitLinks(const TriangleNodeInfo (&theNodesInfo)[3], const int (&theNodesIndices)[3])
  {
    // Check deflection at triangle links
    for (int i = 0; i < 3; ++i)
    {
      if (theNodesInfo[i].isFrontierLink)
      {
        continue;
      }

      const int j = (i + 1) % 3;
      // Check if this link was already processed
      int aFirstVertex, aLastVertex;
      if (theNodesIndices[i] < theNodesIndices[j])
      {
        aFirstVertex = theNodesIndices[i];
        aLastVertex  = theNodesIndices[j];
      }
      else
      {
        aFirstVertex = theNodesIndices[j];
        aLastVertex  = theNodesIndices[i];
      }

      if (myCouplesMap->Add(BRepMesh_OrientedEdge(aFirstVertex, aLastVertex)))
      {
        const gp_XY aMidPnt2d = (theNodesInfo[i].Point2d + theNodesInfo[j].Point2d) / 2.;

        if (!usePoint(aMidPnt2d, LineDeviation(theNodesInfo[i].Point, theNodesInfo[j].Point)))
        {
          if (!rejectSplitLinksForMinSize(theNodesInfo[i], theNodesInfo[j], aMidPnt2d))
          {
            if (!checkLinkEndsForAngularDeviation(theNodesInfo[i], theNodesInfo[j], aMidPnt2d))
            {
              myControlNodes->Append(aMidPnt2d);
            }
          }
        }
      }
    }
  }

  //! Checks that two links produced as the result of a split of
  //! the given link by the middle point fit MinSize requirement.
  bool rejectSplitLinksForMinSize(const TriangleNodeInfo& theNodeInfo1,
                                  const TriangleNodeInfo& theNodeInfo2,
                                  const gp_XY&            theMidPoint)
  {
    const gp_Pnt aPnt = getPoint3d(theMidPoint);
    return ((theNodeInfo1.Point - aPnt.XYZ()).SquareModulus() < mySqMinSize
            || (theNodeInfo2.Point - aPnt.XYZ()).SquareModulus() < mySqMinSize);
  }

  //! Checks the given point (located between the given nodes)
  //! for specified angular deviation.
  bool checkLinkEndsForAngularDeviation(const TriangleNodeInfo& theNodeInfo1,
                                        const TriangleNodeInfo& theNodeInfo2,
                                        const gp_XY& /*theMidPoint*/)
  {
    gp_Dir                           aNorm1, aNorm2;
    const occ::handle<Geom_Surface>& aSurf = this->getDFace()->GetSurface()->Surface().Surface();

    if ((GeomLib::NormEstim(aSurf, theNodeInfo1.Point2d, Precision::Confusion(), aNorm1) == 0)
        && (GeomLib::NormEstim(aSurf, theNodeInfo2.Point2d, Precision::Confusion(), aNorm2) == 0))
    {
      double anAngle = aNorm1.Angle(aNorm2);
      if (anAngle > this->getParameters().AngleInterior)
      {
        return false;
      }
    }

    return true;
  }

  //! Returns 3d point corresponding to the given one in 2d space.
  gp_Pnt getPoint3d(const gp_XY& thePnt2d)
  {
    gp_Pnt aPnt;
    this->getDFace()->GetSurface()->D0(thePnt2d.X(), thePnt2d.Y(), aPnt);
    return aPnt;
  }

  //! Computes deflection of the given point and caches it for
  //! insertion in case if it overflows deflection.
  //! @return True if point has been cached for insertion.
  template <class DeflectionFunctor>
  bool usePoint(const gp_XY& thePnt2d, const DeflectionFunctor& theDeflectionFunctor)
  {
    const gp_Pnt aPnt = getPoint3d(thePnt2d);
    if (!checkDeflectionOfPointAndUpdateCache(thePnt2d,
                                              aPnt,
                                              theDeflectionFunctor.SquareDeviation(aPnt)))
    {
      myControlNodes->Append(thePnt2d);
      return true;
    }

    return false;
  }

  //! Checks the given point for specified linear deflection.
  //! Updates value of total mesh defleciton.
  bool checkDeflectionOfPointAndUpdateCache(const gp_XY&  thePnt2d,
                                            const gp_Pnt& thePnt3d,
                                            const double  theSqDeflection)
  {
    if (theSqDeflection > myMaxSqDeflection)
    {
      myMaxSqDeflection = theSqDeflection;
    }

    const double aSqDeflection =
      this->getDFace()->GetDeflection() * this->getDFace()->GetDeflection();
    if (theSqDeflection < aSqDeflection)
    {
      return true;
    }

    return rejectByMinSize(thePnt2d, thePnt3d);
  }

  //! Checks distance between the given node and nodes of triangles
  //! shot by it for MinSize criteria.
  //! This check is expected to roughly estimate and prevent
  //! generation of triangles with sides smaller than MinSize.
  bool rejectByMinSize(const gp_XY& thePnt2d, const gp_Pnt& thePnt3d)
  {
    IMeshData::MapOfInteger   aUsedNodes;
    IMeshData::ListOfInteger& aCirclesList =
      const_cast<BRepMesh_CircleTool&>(*myCircles)
        .Select(this->getRangeSplitter().Scale(thePnt2d, true).XY());

    IMeshData::ListOfInteger::Iterator aCircleIt(aCirclesList);
    for (; aCircleIt.More(); aCircleIt.Next())
    {
      const BRepMesh_Triangle& aTriangle = this->getStructure()->GetElement(aCircleIt.Value());

      int aNodes[3];
      this->getStructure()->ElementNodes(aTriangle, aNodes);

      for (int i = 0; i < 3; ++i)
      {
        if (!aUsedNodes.Contains(aNodes[i]))
        {
          aUsedNodes.Add(aNodes[i]);
          const BRepMesh_Vertex& aVertex = this->getStructure()->GetNode(aNodes[i]);
          const gp_Pnt&          aPoint  = this->getNodesMap()->Value(aVertex.Location3d());

          if (thePnt3d.SquareDistance(aPoint) < mySqMinSize)
          {
            return true;
          }
        }
      }
    }

    return false;
  }

private:
  double                                myMaxSqDeflection;
  double                                mySqMinSize;
  bool                                  myIsAllDegenerated;
  Handle(IMeshData::MapOfOrientedEdges) myCouplesMap;
  Handle(IMeshData::ListOfPnt2d)        myControlNodes;
  const BRepMesh_CircleTool*            myCircles;
};

