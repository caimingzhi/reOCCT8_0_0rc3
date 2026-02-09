#pragma once

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

template <class RangeSplitter, class BaseAlgo>
class BRepMesh_NodeInsertionMeshAlgo : public BaseAlgo
{
public:
  BRepMesh_NodeInsertionMeshAlgo() = default;

  ~BRepMesh_NodeInsertionMeshAlgo() override = default;

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

  gp_Pnt2d getNodePoint2d(const BRepMesh_Vertex& theVertex) const override
  {
    return myRangeSplitter.Scale(theVertex.Coord(), false);
  }

  const RangeSplitter& getRangeSplitter() const { return myRangeSplitter; }

  const occ::handle<BRepMesh_Classifier>& getClassifier() const { return myClassifier; }

private:
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

        aEndIndex = aPCurve->ParametersNb() - 1;
        aPointIt  = (std::min)(0, aEndIndex);
        aInc      = 1;
      }
      else
      {

        aPointIt  = aPCurve->ParametersNb() - 1;
        aEndIndex = (std::min)(0, aPointIt);
        aInc      = -1;
      }

      for (; aPointIt != aEndIndex; aPointIt += aInc)
      {
        const gp_Pnt2d& aPnt2d = aPCurve->GetPoint(aPointIt);
        aWirePoints->Append(&aPnt2d);
        myRangeSplitter.AddPoint(aPnt2d);
      }
    }

    return aWirePoints;
  }

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

  void insertInternalVertex(const TopoDS_Vertex& theVertex)
  {
    try
    {
      OCC_CATCH_SIGNALS

      gp_Pnt2d aPnt2d = BRep_Tool::Parameters(theVertex, this->getDFace()->GetFace());

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

template <class RangeSplitter, class BaseAlgo>
class BRepMesh_DelaunayNodeInsertionMeshAlgo
    : public BRepMesh_NodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
{
private:
  typedef BRepMesh_NodeInsertionMeshAlgo<RangeSplitter, BaseAlgo> InsertionBaseClass;

public:
  BRepMesh_DelaunayNodeInsertionMeshAlgo()
      : myIsPreProcessSurfaceNodes(false)
  {
  }

  ~BRepMesh_DelaunayNodeInsertionMeshAlgo() override = default;

  bool IsPreProcessSurfaceNodes() const { return myIsPreProcessSurfaceNodes; }

  void SetPreProcessSurfaceNodes(const bool isPreProcessSurfaceNodes)
  {
    myIsPreProcessSurfaceNodes = isPreProcessSurfaceNodes;
  }

protected:
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

  std::pair<int, int> getCellsCount(const int theVerticesNb) override
  {
    return BRepMesh_GeomTool::CellsCount(this->getDFace()->GetSurface(),
                                         theVerticesNb,
                                         this->getDFace()->GetDeflection(),
                                         &this->getRangeSplitter());
  }

  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    if (!theRange.More())
    {
      return;
    }

    InsertionBaseClass::postProcessMesh(theMesher, Message_ProgressRange());

    if (!myIsPreProcessSurfaceNodes)
    {
      const Handle(IMeshData::ListOfPnt2d) aSurfaceNodes =
        this->getRangeSplitter().GenerateSurfaceNodes(this->getParameters());

      insertNodes(aSurfaceNodes, theMesher, theRange);
    }
  }

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

template <class RangeSplitter, class BaseAlgo>
class BRepMesh_DelaunayDeflectionControlMeshAlgo
    : public BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
{
private:
  typedef BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BaseAlgo>
    DelaunayInsertionBaseClass;

public:
  BRepMesh_DelaunayDeflectionControlMeshAlgo()
      : myMaxSqDeflection(-1.),
        mySqMinSize(-1.),
        myIsAllDegenerated(false),
        myCircles(nullptr)
  {
  }

  ~BRepMesh_DelaunayDeflectionControlMeshAlgo() override = default;

protected:
  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    Message_ProgressScope aPS(theRange, "Post process mesh", 2);

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

      myMaxSqDeflection  = -1.;
      myIsAllDegenerated = true;
      myControlNodes->Clear();

      if (this->getStructure()->ElementsOfDomain().Extent() < 1)
      {
        break;
      }

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

  void getTriangleInfo(const BRepMesh_Triangle& theTriangle,
                       const int (&theNodesIndices)[3],
                       TriangleNodeInfo (&theInfo)[3]) const
  {
    const int(&e)[3] = theTriangle.myEdges;
    for (int i = 0; i < 3; ++i)
    {
      const BRepMesh_Vertex& aVertex = this->getStructure()->GetNode(theNodesIndices[i]);
      theInfo[i].Point2d             = this->getRangeSplitter().Scale(aVertex.Coord(), false).XY();
      theInfo[i].Point               = this->getNodesMap()->Value(aVertex.Location3d()).XYZ();
      theInfo[i].isFrontierLink =
        (this->getStructure()->GetLink(e[i]).Movability() == BRepMesh_Frontier);
    }
  }

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

  bool checkTriangleArea2d(const TriangleNodeInfo (&theNodesInfo)[3])
  {
    const gp_Vec2d aLink2d1(theNodesInfo[0].Point2d, theNodesInfo[1].Point2d);
    const gp_Vec2d aLink2d2(theNodesInfo[1].Point2d, theNodesInfo[2].Point2d);

    const double MinimalArea2d = 1.e-9;
    return (std::abs(aLink2d1 ^ aLink2d2) > MinimalArea2d);
  }

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

  void splitLinks(const TriangleNodeInfo (&theNodesInfo)[3], const int (&theNodesIndices)[3])
  {

    for (int i = 0; i < 3; ++i)
    {
      if (theNodesInfo[i].isFrontierLink)
      {
        continue;
      }

      const int j = (i + 1) % 3;

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

  bool rejectSplitLinksForMinSize(const TriangleNodeInfo& theNodeInfo1,
                                  const TriangleNodeInfo& theNodeInfo2,
                                  const gp_XY&            theMidPoint)
  {
    const gp_Pnt aPnt = getPoint3d(theMidPoint);
    return ((theNodeInfo1.Point - aPnt.XYZ()).SquareModulus() < mySqMinSize
            || (theNodeInfo2.Point - aPnt.XYZ()).SquareModulus() < mySqMinSize);
  }

  bool checkLinkEndsForAngularDeviation(const TriangleNodeInfo& theNodeInfo1,
                                        const TriangleNodeInfo& theNodeInfo2,
                                        const gp_XY&)
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

  gp_Pnt getPoint3d(const gp_XY& thePnt2d)
  {
    gp_Pnt aPnt;
    this->getDFace()->GetSurface()->D0(thePnt2d.X(), thePnt2d.Y(), aPnt);
    return aPnt;
  }

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
