#pragma once

#include <BRepExtrema_ElementFilter.hpp>
#include <NCollection_DataMap.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <BRepExtrema_TriangleSet.hpp>
#include <BVH_Distance.hpp>
#include <BVH_Tools.hpp>
#include <Poly_Triangulation.hpp>

class BRepExtrema_ProximityDistTool
    : public BVH_Distance<double, 3, BVH_Vec3d, BRepExtrema_TriangleSet>
{
public:
  typedef typename BVH_Tools<double, 3>::BVH_PrjStateInTriangle BVH_PrjState;

  enum ProxPnt_Status
  {
    ProxPnt_Status_BORDER,
    ProxPnt_Status_MIDDLE,
    ProxPnt_Status_UNKNOWN
  };

public:
  struct PrjState
  {
    PrjState()
        : myTrgIdx(0),
          myPrjState(BVH_PrjState::BVH_PrjStateInTriangle_INNER),
          myNumberOfFirstNode(0),
          myNumberOfLastNode(0)
    {
    }

    PrjState(const int          theTrgIdx,
             const BVH_PrjState thePrjState,
             const int          theNumberOfFirstNode,
             const int          theNumberOfLastNode)
        : myTrgIdx(theTrgIdx),
          myPrjState(thePrjState),
          myNumberOfFirstNode(theNumberOfFirstNode),
          myNumberOfLastNode(theNumberOfLastNode)
    {
    }

    int GetTrgIdx() const { return myTrgIdx; }

    BVH_PrjState GetPrjState() const { return myPrjState; }

    int GetNumberOfFirstNode() const { return myNumberOfFirstNode; }

    int GetNumberOfLastNode() const { return myNumberOfLastNode; }

  private:
    int          myTrgIdx;
    BVH_PrjState myPrjState;

    int myNumberOfFirstNode;
    int myNumberOfLastNode;
  };

public:
  Standard_EXPORT BRepExtrema_ProximityDistTool();

  Standard_EXPORT BRepExtrema_ProximityDistTool(
    const occ::handle<BRepExtrema_TriangleSet>& theSet1,
    const int                                   theNbSamples1,
    const BVH_Array3d&                          theAddVertices1,
    const NCollection_Vector<ProxPnt_Status>&   theAddStatus1,
    const occ::handle<BRepExtrema_TriangleSet>& theSet2,
    const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
    const NCollection_Vector<TopoDS_Shape>&     theShapeList2);

public:
  Standard_EXPORT void LoadTriangleSets(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                                        const occ::handle<BRepExtrema_TriangleSet>& theSet2);

  Standard_EXPORT void LoadShapeLists(const NCollection_Vector<TopoDS_Shape>& theShapeList1,
                                      const NCollection_Vector<TopoDS_Shape>& theShapeList2);

  void LoadAdditionalPointsFirstSet(const BVH_Array3d&                        theAddVertices1,
                                    const NCollection_Vector<ProxPnt_Status>& theAddStatus1);

  Standard_EXPORT void Perform();

public:
  Standard_EXPORT bool RejectNode(const BVH_Vec3d& theCornerMin,
                                  const BVH_Vec3d& theCornerMax,
                                  double&          theMetric) const override;

  Standard_EXPORT bool Accept(const int theSgmIdx, const double&) override;

public:
  Standard_EXPORT static bool IsNodeOnBorder(const int                              theNodeIdx,
                                             const occ::handle<Poly_Triangulation>& theTr);

  Standard_EXPORT static bool IsEdgeOnBorder(const int theTrgIdx,
                                             const int theFirstEdgeNodeIdx,
                                             const int theSecondEdgeNodeIdx,
                                             const occ::handle<Poly_Triangulation>& theTr);

public:
  void ProximityPoints(BVH_Vec3d& thePoint1, BVH_Vec3d& thePoint2) const
  {
    thePoint1 = myPnt1;
    thePoint2 = myPnt2;
  }

  void ProximityPointsStatus(ProxPnt_Status& thePointStatus1, ProxPnt_Status& thePointStatus2) const
  {
    thePointStatus1 = myPntStatus1;
    thePointStatus2 = myPntStatus2;
  }

  double ProximityDistance() const { return myProxDist; }

protected:
  Standard_EXPORT double ComputeDistance();

  Standard_EXPORT void DefineStatusProxPnt();

private:
  void goThroughtSet1(const BVH_Array3d& aVertices1, const bool theIsAdditionalSet);

  void defineStatusProxPnt1();

  void defineStatusProxPnt2();

protected:
  double myMinDistance;

  BVH_Vec3d myMinDistPoint;

  BVH_Vec3d myExtremaPoint;

  double myProxDist;

  BVH_Vec3d myPnt1, myPnt2;

  ProxPnt_Status myPntStatus1, myPntStatus2;

private:
  occ::handle<BRepExtrema_TriangleSet> mySet1;

  occ::handle<BRepExtrema_TriangleSet> mySet2;

  NCollection_Vector<TopoDS_Shape> myShapeList1;

  NCollection_Vector<TopoDS_Shape> myShapeList2;

  int myNbSamples1;

  int         myIsProxVtx1FromAddSet;
  BVH_Array3d myAddVertices1;

  NCollection_Vector<ProxPnt_Status> myAddStatus1;

  int myProxVtxIdx1;

  PrjState myProxPrjState;

  PrjState myExtPrjState;

  PrjState myMinPrjState;
};
