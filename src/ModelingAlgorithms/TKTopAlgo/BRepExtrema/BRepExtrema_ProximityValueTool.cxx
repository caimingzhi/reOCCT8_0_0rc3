#include <BRepExtrema_ProximityValueTool.hpp>
#include <BRepExtrema_ProximityDistTool.hpp>

#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepGProp.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <GCPnts_QuasiUniformAbscissa.hpp>
#include <GProp_GProps.hpp>
#include <Poly_Connect.hpp>
#include <TopoDS.hpp>

BRepExtrema_ProximityValueTool::BRepExtrema_ProximityValueTool()
    : myIsRefinementRequired1(false),
      myIsRefinementRequired2(false),
      myDistance(std::numeric_limits<double>::max()),
      myIsDone(false),
      myNbSamples1(0),
      myNbSamples2(0)
{

  myIsInitS1 = myIsInitS2 = false;
}

BRepExtrema_ProximityValueTool::BRepExtrema_ProximityValueTool(
  const occ::handle<BRepExtrema_TriangleSet>& theSet1,
  const occ::handle<BRepExtrema_TriangleSet>& theSet2,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList2)
    : myIsRefinementRequired1(false),
      myIsRefinementRequired2(false),
      myDistance(std::numeric_limits<double>::max()),
      myIsDone(false),
      myNbSamples1(0),
      myNbSamples2(0)
{
  LoadShapeLists(theShapeList1, theShapeList2);
  LoadTriangleSets(theSet1, theSet2);
}

void BRepExtrema_ProximityValueTool::LoadTriangleSets(
  const occ::handle<BRepExtrema_TriangleSet>& theSet1,
  const occ::handle<BRepExtrema_TriangleSet>& theSet2)
{
  mySet1 = theSet1;
  mySet2 = theSet2;

  MarkDirty();
}

static double calcEdgeRefinementStep(const TopoDS_Edge& theEdge, const int theNbNodes)
{
  if (theNbNodes < 2)
    return 0;

  BRepAdaptor_Curve aBAC(theEdge);
  double            aLen = GCPnts_AbscissaPoint::Length(aBAC);
  return aLen / (double)(theNbNodes - 1);
}

static double calcFaceRefinementStep(const TopoDS_Face& theFace, const int theNbTrg)
{
  if (theNbTrg < 1)
    return 0;

  GProp_GProps props;
  BRepGProp::SurfaceProperties(theFace, props);
  double aArea = props.Mass();
  return 2 * (aArea / (double)theNbTrg);
}

bool BRepExtrema_ProximityValueTool::getInfoForRefinement(const TopoDS_Shape& theShape,
                                                          TopAbs_ShapeEnum&   theShapeType,
                                                          int&                theNbNodes,
                                                          double&             theStep)
{
  if (theShape.ShapeType() == TopAbs_FACE)
  {
    theShapeType   = TopAbs_FACE;
    TopoDS_Face aF = TopoDS::Face(theShape);

    TopLoc_Location                 aLocation;
    occ::handle<Poly_Triangulation> aTriangulation = BRep_Tool::Triangulation(aF, aLocation);

    if (aTriangulation.IsNull())
    {
      return false;
    }

    theNbNodes = aTriangulation->NbNodes();
    int aNbTrg = aTriangulation->NbTriangles();
    theStep    = calcFaceRefinementStep(aF, aNbTrg);
  }
  else if (theShape.ShapeType() == TopAbs_EDGE)
  {
    theShapeType   = TopAbs_EDGE;
    TopoDS_Edge aE = TopoDS::Edge(theShape);

    TopLoc_Location             aLocation;
    occ::handle<Poly_Polygon3D> aPolygon = BRep_Tool::Polygon3D(aE, aLocation);

    if (aPolygon.IsNull())
    {
      return false;
    }

    theNbNodes = aPolygon->NbNodes();
    theStep    = calcEdgeRefinementStep(aE, theNbNodes);
  }
  else
  {
    return false;
  }

  if (theStep < Precision::Confusion())
  {
    return false;
  }

  return true;
}

void BRepExtrema_ProximityValueTool::LoadShapeLists(
  const NCollection_Vector<TopoDS_Shape>& theShapeList1,
  const NCollection_Vector<TopoDS_Shape>& theShapeList2)
{
  myShapeList1 = theShapeList1;
  myShapeList2 = theShapeList2;

  myShape1   = theShapeList1(0);
  myIsInitS1 = getInfoForRefinement(myShape1, myShapeType1, myNbNodes1, myStep1);

  myShape2   = theShapeList2(0);
  myIsInitS2 = getInfoForRefinement(myShape2, myShapeType2, myNbNodes2, myStep2);

  MarkDirty();
}

void BRepExtrema_ProximityValueTool::SetNbSamplePoints(const int theSamples1, const int theSamples2)
{
  myNbSamples1 = theSamples1;
  myNbSamples2 = theSamples2;

  MarkDirty();
}

double BRepExtrema_ProximityValueTool::computeProximityDist(
  const occ::handle<BRepExtrema_TriangleSet>& theSet1,
  const int                                   theNbSamples1,
  const BVH_Array3d&                          theAddVertices1,
  const NCollection_Vector<ProxPnt_Status>&   theAddStatus1,
  const occ::handle<BRepExtrema_TriangleSet>& theSet2,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
  const NCollection_Vector<TopoDS_Shape>&     theShapeList2,
  BVH_Vec3d&                                  thePoint1,
  BVH_Vec3d&                                  thePoint2,
  ProxPnt_Status&                             thePointStatus1,
  ProxPnt_Status&                             thePointStatus2) const
{
  BRepExtrema_ProximityDistTool aProxDistTool(theSet1,
                                              theNbSamples1,
                                              theAddVertices1,
                                              theAddStatus1,
                                              theSet2,
                                              theShapeList1,
                                              theShapeList2);
  aProxDistTool.Perform();

  if (!aProxDistTool.IsDone())
    return -1.;

  aProxDistTool.ProximityPoints(thePoint1, thePoint2);
  aProxDistTool.ProximityPointsStatus(thePointStatus1, thePointStatus2);

  return aProxDistTool.ProximityDistance();
}

bool BRepExtrema_ProximityValueTool::getEdgeAdditionalVertices(
  const TopoDS_Edge&                  theEdge,
  const double                        theStep,
  BVH_Array3d&                        theAddVertices,
  NCollection_Vector<ProxPnt_Status>& theAddStatuses)
{
  BRepAdaptor_Curve aBAC(theEdge);

  if (!aBAC.Is3DCurve() || theStep < Precision::Confusion())
  {
    return false;
  }

  double aLen            = GCPnts_AbscissaPoint::Length(aBAC);
  int    aNbSamplePoints = (int)(aLen / theStep) + 1;

  GCPnts_QuasiUniformAbscissa aGCPnts(aBAC, std::max(3, aNbSamplePoints));

  if (!aGCPnts.IsDone())
    return false;

  int aNbNodes = aGCPnts.NbPoints();
  for (int aVertIdx = 2; aVertIdx < aNbNodes; ++aVertIdx)
  {
    double aPar = aGCPnts.Parameter(aVertIdx);
    gp_Pnt aP   = aBAC.Value(aPar);

    theAddVertices.push_back(BVH_Vec3d(aP.X(), aP.Y(), aP.Z()));
    theAddStatuses.Append(ProxPnt_Status::ProxPnt_Status_MIDDLE);
  }

  return true;
}

void BRepExtrema_ProximityValueTool::doRecurTrgSplit(
  const gp_Pnt (&theTrg)[3],
  const ProxPnt_Status (&theEdgesStatus)[3],
  const double                        theTol,
  const double                        theStep,
  BVH_Array3d&                        theAddVertices,
  NCollection_Vector<ProxPnt_Status>& theAddStatuses)
{
  gp_XYZ aTrgSide1 = theTrg[1].Coord() - theTrg[0].Coord();
  gp_XYZ aTrgSide2 = theTrg[2].Coord() - theTrg[0].Coord();
  double aTrgArea  = 0.5 * aTrgSide1.CrossMagnitude(aTrgSide2);

  if (aTrgArea - theStep < Precision::SquareConfusion())
    return;

  double aD[3]{theTrg[0].Distance(theTrg[1]),
               theTrg[1].Distance(theTrg[2]),
               theTrg[2].Distance(theTrg[0])};
  int    aBisectedEdgeIdx = aD[0] > aD[1] ? (aD[0] > aD[2] ? 0 : 2) : (aD[1] > aD[2] ? 1 : 2);
  gp_Pnt aCenterOfMaxSide(theTrg[aBisectedEdgeIdx].Coord());
  aCenterOfMaxSide.BaryCenter(0.5, theTrg[(aBisectedEdgeIdx + 1) % 3], 0.5);

  Bnd_Box aBox;
  aBox.Add(aCenterOfMaxSide);
  aBox.Enlarge(theTol);
  myInspector.SetCurrent(aCenterOfMaxSide.Coord());
  myCells.Inspect(aBox.CornerMin().XYZ(), aBox.CornerMax().XYZ(), myInspector);

  if (myInspector.IsNeedAdd())
  {
    BVH_Vec3d aBisectingPnt(aCenterOfMaxSide.X(), aCenterOfMaxSide.Y(), aCenterOfMaxSide.Z());
    theAddVertices.push_back(aBisectingPnt);
    theAddStatuses.Append(theEdgesStatus[aBisectedEdgeIdx]);
    myInspector.Add(aCenterOfMaxSide.Coord());
    myCells.Add(static_cast<BRepExtrema_VertexInspector::Target>(theAddVertices.size()),
                aBox.CornerMin().XYZ(),
                aBox.CornerMax().XYZ());
  }

  gp_Pnt         aTrg1[3]         = {theTrg[0], theTrg[1], theTrg[2]};
  gp_Pnt         aTrg2[3]         = {theTrg[0], theTrg[1], theTrg[2]};
  ProxPnt_Status aEdgesStatus1[3] = {theEdgesStatus[0], theEdgesStatus[1], theEdgesStatus[2]};
  ProxPnt_Status aEdgesStatus2[3] = {theEdgesStatus[0], theEdgesStatus[1], theEdgesStatus[2]};
  switch (aBisectedEdgeIdx)
  {
    case 0:
      aTrg1[0] = aTrg2[1] = aCenterOfMaxSide;
      aEdgesStatus1[2] = aEdgesStatus2[1] = ProxPnt_Status::ProxPnt_Status_MIDDLE;
      break;
    case 1:
      aTrg1[1] = aTrg2[2] = aCenterOfMaxSide;
      aEdgesStatus1[0] = aEdgesStatus2[2] = ProxPnt_Status::ProxPnt_Status_MIDDLE;
      break;
    case 2:
      aTrg1[2] = aTrg2[0] = aCenterOfMaxSide;
      aEdgesStatus1[1] = aEdgesStatus2[0] = ProxPnt_Status::ProxPnt_Status_MIDDLE;
      break;
  }

  doRecurTrgSplit(aTrg1, aEdgesStatus1, theTol, theStep, theAddVertices, theAddStatuses);
  doRecurTrgSplit(aTrg2, aEdgesStatus2, theTol, theStep, theAddVertices, theAddStatuses);
}

static double getModelRange(const TopLoc_Location&                 theLocation,
                            const occ::handle<Poly_Triangulation>& theTr)
{
  Bnd_Box aBox;
  theTr->MinMax(aBox, theLocation.Transformation());
  double aXm = 0.0, aYm = 0.0, aZm = 0.0, aXM = 0.0, aYM = 0.0, aZM = 0.0;
  aBox.Get(aXm, aYm, aZm, aXM, aYM, aZM);
  double aRange = aXM - aXm;
  aRange        = std::max(aRange, aYM - aYm);
  aRange        = std::max(aRange, aZM - aZm);

  return aRange;
}

static void getNodesOfTrg(const int                              theTriIdx,
                          const TopLoc_Location&                 theLocation,
                          const occ::handle<Poly_Triangulation>& theTr,
                          gp_Pnt (&theTrg)[3])
{
  int aVtxIdx1;
  int aVtxIdx2;
  int aVtxIdx3;

  theTr->Triangle(theTriIdx).Get(aVtxIdx1, aVtxIdx2, aVtxIdx3);

  gp_Pnt aVtx1 = theTr->Node(aVtxIdx1);
  aVtx1.Transform(theLocation);
  theTrg[0] = aVtx1;

  gp_Pnt aVtx2 = theTr->Node(aVtxIdx2);
  aVtx2.Transform(theLocation);
  theTrg[1] = aVtx2;

  gp_Pnt aVtx3 = theTr->Node(aVtxIdx3);
  aVtx3.Transform(theLocation);
  theTrg[2] = aVtx3;
}

static void getEdgesStatus(const int                              theTriIdx,
                           const occ::handle<Poly_Triangulation>& theTr,
                           ProxPnt_Status (&theEdgesStatus1)[3])
{
  for (int j = 0; j < 3; j++)
  {
    int k = (j + 1) % 3;

    if (BRepExtrema_ProximityDistTool::IsEdgeOnBorder(theTriIdx, j, k, theTr))
    {
      theEdgesStatus1[j] = ProxPnt_Status::ProxPnt_Status_BORDER;
    }
    else
    {
      theEdgesStatus1[j] = ProxPnt_Status::ProxPnt_Status_MIDDLE;
    }
  }
}

bool BRepExtrema_ProximityValueTool::getFaceAdditionalVertices(
  const TopoDS_Face&                  theFace,
  const double                        theStep,
  BVH_Array3d&                        theAddVertices,
  NCollection_Vector<ProxPnt_Status>& theAddStatuses)
{
  constexpr double aTol = Precision::Confusion();

  TopLoc_Location                 aLocation;
  occ::handle<Poly_Triangulation> aTr = BRep_Tool::Triangulation(theFace, aLocation);

  if (aTr.IsNull())
  {
    return false;
  }

  myCells.Reset(std::max(aTol, getModelRange(aLocation, aTr) / IntegerLast()));

  for (int aTriIdx = 1; aTriIdx <= aTr->NbTriangles(); ++aTriIdx)
  {
    gp_Pnt         aTrg[3];
    ProxPnt_Status aEdgesStatus[3];
    getNodesOfTrg(aTriIdx, aLocation, aTr, aTrg);
    getEdgesStatus(aTriIdx, aTr, aEdgesStatus);
    doRecurTrgSplit(aTrg, aEdgesStatus, aTol, theStep, theAddVertices, theAddStatuses);
  }

  return true;
}

bool BRepExtrema_ProximityValueTool::getShapesAdditionalVertices()
{

  double aStep1 = myStep1;
  double aStep2 = myStep2;

  if ((myShapeType1 == TopAbs_EDGE) && (myShapeType2 == TopAbs_EDGE))
  {
    if (myNbSamples1 > myNbNodes1)
    {
      aStep1                  = calcEdgeRefinementStep(TopoDS::Edge(myShape1), myNbSamples1);
      myIsRefinementRequired1 = true;
    }

    if (myNbSamples2 > myNbNodes2)
    {
      aStep2                  = calcEdgeRefinementStep(TopoDS::Edge(myShape2), myNbSamples2);
      myIsRefinementRequired2 = true;
    }

    if (aStep1 / aStep2 > 2.)
    {
      myIsRefinementRequired1 = true;
      aStep1                  = aStep2;
    }
    else if (aStep2 / aStep1 > 2.)
    {
      myIsRefinementRequired2 = true;
      aStep2                  = aStep1;
    }

    if (myIsRefinementRequired1)
    {
      if (!getEdgeAdditionalVertices(TopoDS::Edge(myShape1), aStep1, myAddVertices1, myAddStatus1))
      {
        return false;
      }
    }

    if (myIsRefinementRequired2)
    {
      if (!getEdgeAdditionalVertices(TopoDS::Edge(myShape2), aStep2, myAddVertices2, myAddStatus2))
      {
        return false;
      }
    }
  }
  else if ((myShapeType1 == TopAbs_FACE) && (myShapeType2 == TopAbs_FACE))
  {
    if (aStep1 / aStep2 > 2)
    {
      myIsRefinementRequired1 = true;
      aStep1                  = myStep2;
    }
    else if (aStep2 / aStep1 > 2.)
    {
      myIsRefinementRequired2 = true;
      aStep2                  = myStep1;
    }

    if (myIsRefinementRequired1)
    {
      return getFaceAdditionalVertices(TopoDS::Face(myShape1),
                                       aStep1,
                                       myAddVertices1,
                                       myAddStatus1);
    }

    if (myIsRefinementRequired2)
    {
      return getFaceAdditionalVertices(TopoDS::Face(myShape2),
                                       aStep2,
                                       myAddVertices2,
                                       myAddStatus2);
    }
  }

  return true;
}

void BRepExtrema_ProximityValueTool::Perform(double& theTolerance)
{
  if (!myIsInitS1 || !myIsInitS2 || (myShapeType1 != myShapeType2))
    return;

  if (!getShapesAdditionalVertices())
    return;

  BVH_Vec3d      aP1_1, aP1_2;
  ProxPnt_Status aPointStatus1_1 = ProxPnt_Status::ProxPnt_Status_UNKNOWN;
  ProxPnt_Status aPointStatus1_2 = ProxPnt_Status::ProxPnt_Status_UNKNOWN;

  double aProximityDist1 = computeProximityDist(mySet1,
                                                myNbSamples1,
                                                myAddVertices1,
                                                myAddStatus1,
                                                mySet2,
                                                myShapeList1,
                                                myShapeList2,
                                                aP1_1,
                                                aP1_2,
                                                aPointStatus1_1,
                                                aPointStatus1_2);

  if (aProximityDist1 < 0.)
    return;

  BVH_Vec3d      aP2_1, aP2_2;
  ProxPnt_Status aPointStatus2_1 = ProxPnt_Status::ProxPnt_Status_UNKNOWN;
  ProxPnt_Status aPointStatus2_2 = ProxPnt_Status::ProxPnt_Status_UNKNOWN;

  double aProximityDist2 = computeProximityDist(mySet2,
                                                myNbSamples2,
                                                myAddVertices2,
                                                myAddStatus2,
                                                mySet1,
                                                myShapeList2,
                                                myShapeList1,
                                                aP2_2,
                                                aP2_1,
                                                aPointStatus2_2,
                                                aPointStatus2_1);

  if (aProximityDist2 < 0.)
    return;

  if (aProximityDist1 < aProximityDist2)
  {
    myDistance = aProximityDist1;
    myPnt1.SetCoord(aP1_1.x(), aP1_1.y(), aP1_1.z());
    myPnt2.SetCoord(aP1_2.x(), aP1_2.y(), aP1_2.z());
    myPntStatus1 = aPointStatus1_1;
    myPntStatus2 = aPointStatus1_2;
  }
  else
  {
    myDistance = aProximityDist2;
    myPnt1.SetCoord(aP2_1.x(), aP2_1.y(), aP2_1.z());
    myPnt2.SetCoord(aP2_2.x(), aP2_2.y(), aP2_2.z());
    myPntStatus1 = aPointStatus2_1;
    myPntStatus2 = aPointStatus2_2;
  }

  myIsDone     = true;
  theTolerance = myDistance;
}

NCollection_CellFilter_Action BRepExtrema_VertexInspector::Inspect(const int theTarget)
{
  myIsNeedAdd = true;

  const gp_XYZ& aPnt = myPoints.Value(theTarget - 1);
  double        aDx, aDy, aDz;
  aDx = myCurrent.X() - aPnt.X();
  aDy = myCurrent.Y() - aPnt.Y();
  aDz = myCurrent.Z() - aPnt.Z();

  if ((aDx * aDx <= myTol) && (aDy * aDy <= myTol) && (aDz * aDz <= myTol))
    myIsNeedAdd = false;

  return CellFilter_Keep;
}
