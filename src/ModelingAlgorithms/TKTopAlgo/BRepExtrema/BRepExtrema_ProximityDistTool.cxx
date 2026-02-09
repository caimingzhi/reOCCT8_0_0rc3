#include <BRepExtrema_ProximityDistTool.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pln.hpp>
#include <Precision.hpp>
#include <Poly_Connect.hpp>
#include <Standard_NullValue.hpp>
#include <TopoDS.hpp>

BRepExtrema_ProximityDistTool::BRepExtrema_ProximityDistTool()
    : myMinDistance(std::numeric_limits<double>::max()),
      myProxDist(-1.),
      myPntStatus1(ProxPnt_Status_UNKNOWN),
      myPntStatus2(ProxPnt_Status_UNKNOWN),
      myNbSamples1(0),
      myProxVtxIdx1(-1)
{
}

BRepExtrema_ProximityDistTool::BRepExtrema_ProximityDistTool(
  const occ::handle<BRepExtrema_TriangleSet>& theSet1,
  const int                                   theNbSamples1,
  const BVH_Array3d&                          theAddVertices1,
  const NCollection_Vector<ProxPnt_Status>&   theAddStatus1,
  const occ::handle<BRepExtrema_TriangleSet>& theSet2,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList2)
    : myMinDistance(std::numeric_limits<double>::max()),
      myProxDist(-1.),
      myPntStatus1(ProxPnt_Status_UNKNOWN),
      myPntStatus2(ProxPnt_Status_UNKNOWN),
      myNbSamples1(theNbSamples1),
      myProxVtxIdx1(-1)
{
  LoadTriangleSets(theSet1, theSet2);
  LoadShapeLists(theShapeList1, theShapeList2);
  LoadAdditionalPointsFirstSet(theAddVertices1, theAddStatus1);
}

void BRepExtrema_ProximityDistTool::LoadTriangleSets(
  const occ::handle<BRepExtrema_TriangleSet>& theSet1,
  const occ::handle<BRepExtrema_TriangleSet>& theSet2)
{
  mySet1 = theSet1;
  mySet2 = theSet2;
}

void BRepExtrema_ProximityDistTool::LoadShapeLists(
  const NCollection_Vector<TopoDS_Shape>& theShapeList1,
  const NCollection_Vector<TopoDS_Shape>& theShapeList2)
{
  myShapeList1 = theShapeList1;
  myShapeList2 = theShapeList2;
}

void BRepExtrema_ProximityDistTool::LoadAdditionalPointsFirstSet(
  const BVH_Array3d&                        theAddVertices1,
  const NCollection_Vector<ProxPnt_Status>& theAddStatus1)
{
  myAddVertices1 = theAddVertices1;
  myAddStatus1   = theAddStatus1;
}

void BRepExtrema_ProximityDistTool::goThroughtSet1(const BVH_Array3d& theVertices1,
                                                   const bool         theIsAdditionalSet)
{
  int aVtxSize = (int)theVertices1.size();
  int aVtxStep = std::max(myNbSamples1 <= 0 ? 1 : aVtxSize / myNbSamples1, 1);
  for (int aVtxIdx = 0; aVtxIdx < aVtxSize; aVtxIdx += aVtxStep)
  {
    myDistance    = std::numeric_limits<double>::max();
    myMinDistance = std::numeric_limits<double>::max();
    myIsDone      = false;
    SetObject(theVertices1[aVtxIdx]);

    ComputeDistance();

    if (!IsDone() && myProxDist < 0.)
      return;

    if (IsDone() && myDistance > myProxDist)
    {
      myPnt1                 = theVertices1[aVtxIdx];
      myPnt2                 = myExtremaPoint;
      myProxDist             = myDistance;
      myProxVtxIdx1          = aVtxIdx;
      myIsProxVtx1FromAddSet = theIsAdditionalSet;
      myProxPrjState         = myExtPrjState;
    }
  }
}

void BRepExtrema_ProximityDistTool::Perform()
{
  SetBVHSet(mySet2.get());
  goThroughtSet1(mySet1->GetVertices(), false);
  goThroughtSet1(myAddVertices1, true);

  myIsDone = myProxDist > -1.;
  if (myIsDone)
  {
    DefineStatusProxPnt();
  }
}

static double pointBoxSquareMaxDistance(const BVH_Vec3d& thePoint,
                                        const BVH_Vec3d& theCMin,
                                        const BVH_Vec3d& theCMax)
{
  double aDist = 0;
  for (int i = 0; i < 3; ++i)
  {
    if (thePoint[i] <= 0.5 * (theCMax[i] + theCMin[i]))
    {
      double d = theCMax[i] - thePoint[i];
      d *= d;
      aDist += d;
    }
    else
    {
      double d = thePoint[i] - theCMin[i];
      d *= d;
      aDist += d;
    }
  }
  return aDist;
}

bool BRepExtrema_ProximityDistTool::RejectNode(const BVH_Vec3d& theCornerMin,
                                               const BVH_Vec3d& theCornerMax,
                                               double&          theMetric) const
{
  theMetric =
    sqrt(BVH_Tools<double, 3>::PointBoxSquareDistance(myObject, theCornerMin, theCornerMax));

  double aMaxMetric = sqrt(pointBoxSquareMaxDistance(myObject, theCornerMin, theCornerMax));

  return theMetric > myDistance || aMaxMetric < myProxDist;
}

bool BRepExtrema_ProximityDistTool::Accept(const int theTrgIdx, const double&)
{
  BVH_Vec3d aTrgVert1;
  BVH_Vec3d aTrgVert2;
  BVH_Vec3d aTrgVert3;

  BVH_PrjState aBVH_PrjState;
  int          aNumberOfFirstNode = -1;
  int          aNumberOfLastNode  = -1;

  mySet2->GetVertices(theTrgIdx, aTrgVert1, aTrgVert2, aTrgVert3);

  BVH_Vec3d aNearestPnt = BVH_Tools<double, 3>::PointTriangleProjection(myObject,
                                                                        aTrgVert1,
                                                                        aTrgVert2,
                                                                        aTrgVert3,
                                                                        &aBVH_PrjState,
                                                                        &aNumberOfFirstNode,
                                                                        &aNumberOfLastNode);

  PrjState  aPrjState(theTrgIdx, aBVH_PrjState, aNumberOfFirstNode, aNumberOfLastNode);
  BVH_Vec3d aDirect     = myObject - aNearestPnt;
  double    aSqDistance = aDirect.Dot(aDirect);

  if (aSqDistance > Precision::SquareConfusion())
  {
    const BVH_Vec3d aAB = aTrgVert2 - aTrgVert1;

    BVH_Vec3d aNorm;
    if (aTrgVert2.IsEqual(aTrgVert3))
    {
      const BVH_Vec3d aAP = myObject - aTrgVert1;
      aNorm               = BVH_Vec3d::Cross(BVH_Vec3d::Cross(aAP, aAB), aAB);
    }
    else
    {
      const BVH_Vec3d aAC = aTrgVert3 - aTrgVert1;
      aNorm               = BVH_Vec3d::Cross(aAB, aAC);
    }

    double aNormSqLen = aNorm.Dot(aNorm);

    const BVH_Vec3d aCrossCross      = BVH_Vec3d::Cross(aDirect, aNorm);
    double          aCrossCrossSqLen = aCrossCross.Dot(aCrossCross);
    if (aCrossCrossSqLen > Precision::SquareConfusion() * aSqDistance * aNormSqLen)
    {

      if (myMinDistance - sqrt(aSqDistance) > Precision::Confusion())
      {
        myMinDistance  = sqrt(aSqDistance);
        myMinDistPoint = aNearestPnt;
        myMinPrjState  = aPrjState;
      }

      return false;
    }
  }

  if (myDistance - sqrt(aSqDistance) > Precision::Confusion())
  {
    myDistance     = sqrt(aSqDistance);
    myExtremaPoint = aNearestPnt;
    myExtPrjState  = aPrjState;

    return true;
  }

  return false;
}

double BRepExtrema_ProximityDistTool::ComputeDistance()
{
  myIsDone = this->Select() > 0;

  if (!myIsDone)
  {
    if (myMinDistance < std::numeric_limits<double>::max())
    {
      myExtremaPoint = myMinDistPoint;
      myExtPrjState  = myMinPrjState;
      myIsDone       = true;
    }

    myDistance = myMinDistance;
  }

  return myDistance;
}

bool BRepExtrema_ProximityDistTool::IsNodeOnBorder(const int theNodeIdx,
                                                   const occ::handle<Poly_Triangulation>& theTr)
{
  Poly_Connect aPolyConnect(theTr);

  int aContTrg;
  for (aPolyConnect.Initialize(theNodeIdx); aPolyConnect.More(); aPolyConnect.Next())
  {
    aContTrg = aPolyConnect.Value();

    int aContTrgNodes[3];

    theTr->Triangle(aContTrg).Get(aContTrgNodes[0], aContTrgNodes[1], aContTrgNodes[2]);

    int aAdjTrg[3];
    aPolyConnect.Triangles(aContTrg, aAdjTrg[0], aAdjTrg[1], aAdjTrg[2]);

    for (int j = 0; j < 3; j++)
    {
      int k = (j + 1) % 3;
      if (aAdjTrg[j] == 0)
      {

        if (aContTrgNodes[j] == theNodeIdx || aContTrgNodes[k] == theNodeIdx)
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool BRepExtrema_ProximityDistTool::IsEdgeOnBorder(const int theTrgIdx,
                                                   const int theFirstEdgeNodeIdx,
                                                   const int theSecondEdgeNodeIdx,
                                                   const occ::handle<Poly_Triangulation>& theTr)
{
  Poly_Connect aPolyConnect(theTr);

  int aAdjTrg[3];

  aPolyConnect.Triangles(theTrgIdx, aAdjTrg[0], aAdjTrg[1], aAdjTrg[2]);

  for (int j = 0; j < 3; j++)
  {
    int k = (j + 1) % 3;
    if (aAdjTrg[j] == 0)
    {

      if (j == theFirstEdgeNodeIdx && k == theSecondEdgeNodeIdx)
      {
        return true;
      }
    }
  }

  return false;
}

void BRepExtrema_ProximityDistTool::defineStatusProxPnt1()
{
  if (myIsProxVtx1FromAddSet)
  {
    myPntStatus1 = myAddStatus1[myProxVtxIdx1];
    return;
  }

  int aFaceID1 = mySet1->GetShapeIDOfVtx(myProxVtxIdx1);

  if (myShapeList1(aFaceID1).ShapeType() == TopAbs_EDGE)
  {
    const BVH_Array3d& aVertices1 = mySet1->GetVertices();
    int                aVtxSize   = (int)aVertices1.size();
    int                aLastIdx   = aVtxSize - 1;

    if ((aVertices1[0] - aVertices1[aLastIdx]).Modulus() < Precision::Confusion())
    {
      myPntStatus1 = ProxPnt_Status_MIDDLE;
      return;
    }

    if (myProxVtxIdx1 == 0 || myProxVtxIdx1 == aLastIdx)
    {
      myPntStatus1 = ProxPnt_Status_BORDER;
    }
    else
    {
      myPntStatus1 = ProxPnt_Status_MIDDLE;
    }
  }
  else if (myShapeList1(aFaceID1).ShapeType() == TopAbs_FACE)
  {
    int aNodeIdx = mySet1->GetVtxIdxInShape(myProxVtxIdx1) + 1;

    TopLoc_Location                 aLocation;
    const TopoDS_Face&              aF  = TopoDS::Face(myShapeList1(aFaceID1));
    occ::handle<Poly_Triangulation> aTr = BRep_Tool::Triangulation(aF, aLocation);

    if (IsNodeOnBorder(aNodeIdx, aTr))
    {
      myPntStatus1 = ProxPnt_Status_BORDER;
    }
    else
    {
      myPntStatus1 = ProxPnt_Status_MIDDLE;
    }
  }
}

void BRepExtrema_ProximityDistTool::defineStatusProxPnt2()
{
  int aTrgIdx  = myProxPrjState.GetTrgIdx();
  int aFaceID2 = mySet2->GetFaceID(aTrgIdx);

  if (myShapeList2(aFaceID2).ShapeType() == TopAbs_EDGE)
  {
    if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_INNER)
    {
      return;
    }
    else
    {
      const BVH_Array3d& aVertices2 = mySet2->GetVertices();
      int                aVtxSize   = (int)aVertices2.size();
      int                aLastIdx   = aVtxSize - 1;

      if ((aVertices2[0] - aVertices2[aLastIdx]).Modulus() < Precision::Confusion())
      {
        myPntStatus2 = ProxPnt_Status_MIDDLE;
        return;
      }

      NCollection_Array1<int> aVtxIndicesOfTrg;
      mySet2->GetVtxIndices(aTrgIdx, aVtxIndicesOfTrg);

      int aFirstNodeNum = myProxPrjState.GetNumberOfFirstNode();
      int aFirstVtxIdx  = aVtxIndicesOfTrg[aFirstNodeNum];

      if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_VERTEX)
      {
        if (aFirstVtxIdx == 0 || aFirstVtxIdx == aLastIdx)
        {
          myPntStatus2 = ProxPnt_Status_BORDER;
        }
        else
        {
          myPntStatus2 = ProxPnt_Status_MIDDLE;
        }
      }
      else if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_EDGE)
      {
        int aLastNodeNum = myProxPrjState.GetNumberOfLastNode();
        int aLastVtxIdx  = aVtxIndicesOfTrg[aLastNodeNum];

        if (aFirstVtxIdx == aLastVtxIdx && (aFirstVtxIdx == 0 || aFirstVtxIdx == aLastIdx))
        {
          myPntStatus2 = ProxPnt_Status_BORDER;
        }
        else
        {
          myPntStatus2 = ProxPnt_Status_MIDDLE;
        }
      }
    }
  }
  else if (myShapeList2(aFaceID2).ShapeType() == TopAbs_FACE)
  {
    if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_INNER)
    {
      myPntStatus2 = ProxPnt_Status_MIDDLE;
    }
    else
    {
      TopLoc_Location                 aLocation;
      const TopoDS_Face&              aF  = TopoDS::Face(myShapeList2(aFaceID2));
      occ::handle<Poly_Triangulation> aTr = BRep_Tool::Triangulation(aF, aLocation);

      NCollection_Array1<int> aVtxIndicesOfTrg;
      mySet2->GetVtxIndices(aTrgIdx, aVtxIndicesOfTrg);

      if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_VERTEX)
      {
        int aNodeNum = myProxPrjState.GetNumberOfFirstNode();
        int aNodeIdx = mySet2->GetVtxIdxInShape(aVtxIndicesOfTrg[aNodeNum]) + 1;

        if (IsNodeOnBorder(aNodeIdx, aTr))
        {
          myPntStatus2 = ProxPnt_Status_BORDER;
        }
        else
        {
          myPntStatus2 = ProxPnt_Status_MIDDLE;
        }
      }
      else if (myProxPrjState.GetPrjState() == BVH_PrjState::BVH_PrjStateInTriangle_EDGE)
      {
        int aTrgIdxInShape = mySet2->GetTrgIdxInShape(aTrgIdx) + 1;

        if (IsEdgeOnBorder(aTrgIdxInShape,
                           myProxPrjState.GetNumberOfFirstNode(),
                           myProxPrjState.GetNumberOfLastNode(),
                           aTr))
        {
          myPntStatus2 = ProxPnt_Status_BORDER;
        }
        else
        {
          myPntStatus2 = ProxPnt_Status_MIDDLE;
        }
      }
    }
  }
}

void BRepExtrema_ProximityDistTool::DefineStatusProxPnt()
{

  defineStatusProxPnt1();

  defineStatusProxPnt2();
}
