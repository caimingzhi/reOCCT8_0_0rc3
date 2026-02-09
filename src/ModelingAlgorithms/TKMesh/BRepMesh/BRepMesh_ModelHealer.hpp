#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshData_Model.hpp>
#include <TopoDS_Vertex.hpp>

class BRepMesh_ModelHealer : public IMeshTools_ModelAlgo
{
public:
  Standard_EXPORT BRepMesh_ModelHealer();

  Standard_EXPORT ~BRepMesh_ModelHealer() override;

  void operator()(const int theEdgeIndex) const { process(theEdgeIndex); }

  void operator()(const IMeshData::IFaceHandle& theDFace) const { process(theDFace); }

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelHealer, IMeshTools_ModelAlgo)

protected:
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;

private:
  void process(const int theFaceIndex) const
  {
    const IMeshData::IFaceHandle& aDFace = myModel->GetFace(theFaceIndex);
    process(aDFace);
  }

  void process(const IMeshData::IFaceHandle& theDFace) const;

  void amplifyEdges();

  TopoDS_Vertex getCommonVertex(const IMeshData::IEdgeHandle& theEdge1,
                                const IMeshData::IEdgeHandle& theEdge2) const;

  bool connectClosestPoints(const IMeshData::IPCurveHandle& thePrevDEdge,
                            const IMeshData::IPCurveHandle& theCurrDEdge,
                            const IMeshData::IPCurveHandle& theNextDEdge) const;

  double closestPoint(gp_Pnt2d&  theRefPnt,
                      gp_Pnt2d&  theFristPnt,
                      gp_Pnt2d&  theSecondPnt,
                      gp_Pnt2d*& theClosestPnt) const
  {

    const double aSqDist1 = theRefPnt.SquareDistance(theFristPnt);
    const double aSqDist2 = theRefPnt.SquareDistance(theSecondPnt);
    if (aSqDist1 < aSqDist2)
    {
      theClosestPnt = &theFristPnt;
      return aSqDist1;
    }

    theClosestPnt = &theSecondPnt;
    return aSqDist2;
  }

  double closestPoints(gp_Pnt2d&  theFirstPnt1,
                       gp_Pnt2d&  theSecondPnt1,
                       gp_Pnt2d&  theFirstPnt2,
                       gp_Pnt2d&  theSecondPnt2,
                       gp_Pnt2d*& theClosestPnt1,
                       gp_Pnt2d*& theClosestPnt2) const
  {
    gp_Pnt2d *   aCurrPrevUV1 = nullptr, *aCurrPrevUV2 = nullptr;
    const double aSqDist1 = closestPoint(theFirstPnt1, theFirstPnt2, theSecondPnt2, aCurrPrevUV1);
    const double aSqDist2 = closestPoint(theSecondPnt1, theFirstPnt2, theSecondPnt2, aCurrPrevUV2);
    if (aSqDist1 - aSqDist2 < gp::Resolution())
    {
      theClosestPnt1 = &theFirstPnt1;
      theClosestPnt2 = aCurrPrevUV1;
      return aSqDist1;
    }

    theClosestPnt1 = &theSecondPnt1;
    theClosestPnt2 = aCurrPrevUV2;
    return aSqDist2;
  }

  void adjustSamePoints(gp_Pnt2d*& theMajorSamePnt1,
                        gp_Pnt2d*& theMinorSamePnt1,
                        gp_Pnt2d*& theMajorSamePnt2,
                        gp_Pnt2d*& theMinorSamePnt2,
                        gp_Pnt2d&  theMajorFirstPnt,
                        gp_Pnt2d&  theMajorLastPnt,
                        gp_Pnt2d&  theMinorFirstPnt,
                        gp_Pnt2d&  theMinorLastPnt) const
  {
    if (theMajorSamePnt2 == theMajorSamePnt1)
    {
      theMajorSamePnt2 =
        (theMajorSamePnt2 == &theMajorFirstPnt) ? &theMajorLastPnt : &theMajorFirstPnt;
      closestPoint(*theMajorSamePnt2, theMinorFirstPnt, theMinorLastPnt, theMinorSamePnt2);
    }

    *theMajorSamePnt1 = *theMinorSamePnt1;
    *theMajorSamePnt2 = *theMinorSamePnt2;
  }

  void fixFaceBoundaries(const IMeshData::IFaceHandle& theDFace) const;

  bool isParallel() const { return (myParameters.InParallel && myModel->FacesNb() > 1); }

  bool popEdgesToUpdate(IMeshData::MapOfIEdgePtr& theEdgesToUpdate);

private:
  occ::handle<IMeshData_Model>                     myModel;
  IMeshTools_Parameters                            myParameters;
  Handle(IMeshData::DMapOfIFacePtrsMapOfIEdgePtrs) myFaceIntersectingEdges;
};
