

#include <BRepBndLib.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <Bnd_OBB.hpp>
#include <BRepGProp.hpp>
#include <TopExp_Explorer.hpp>
#include <GProp_PrincipalProps.hpp>
#include <gp_Ax3.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Geom_Plane.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>

#include <Geom_OffsetCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BezierSurface.hpp>

static bool IsLinear(const Adaptor3d_Curve& theC)
{
  const GeomAbs_CurveType aCT = theC.GetType();
  if (aCT == GeomAbs_OffsetCurve)
  {
    return IsLinear(GeomAdaptor_Curve(theC.OffsetCurve()->BasisCurve()));
  }

  if ((aCT == GeomAbs_BSplineCurve) || (aCT == GeomAbs_BezierCurve))
  {

    return ((theC.Degree() == 1) && (theC.Continuity() != GeomAbs_C0));
  }

  if (aCT == GeomAbs_Line)
  {
    return true;
  }

  return false;
}

static bool IsPlanar(const Adaptor3d_Surface& theS)
{
  const GeomAbs_SurfaceType aST = theS.GetType();
  if (aST == GeomAbs_OffsetSurface)
  {
    return IsPlanar(*theS.BasisSurface());
  }

  if (aST == GeomAbs_SurfaceOfExtrusion)
  {
    return IsLinear(*theS.BasisCurve());
  }

  if ((aST == GeomAbs_BSplineSurface) || (aST == GeomAbs_BezierSurface))
  {
    if ((theS.UDegree() != 1) || (theS.VDegree() != 1))
      return false;

    return ((theS.UContinuity() != GeomAbs_C0) && (theS.VContinuity() != GeomAbs_C0));
  }

  if (aST == GeomAbs_Plane)
  {
    return true;
  }

  return false;
}

static int PointsForOBB(const TopoDS_Shape&         theS,
                        const bool                  theIsTriangulationUsed,
                        NCollection_Array1<gp_Pnt>* thePts        = nullptr,
                        NCollection_Array1<double>* theArrOfToler = nullptr)
{
  int             aRetVal = 0;
  TopExp_Explorer anExpF, anExpE;

  for (anExpF.Init(theS, TopAbs_VERTEX); anExpF.More(); anExpF.Next())
  {
    const TopoDS_Vertex& aVert = TopoDS::Vertex(anExpF.Current());
    if (thePts)
    {
      const gp_Pnt aP    = BRep_Tool::Pnt(aVert);
      (*thePts)(aRetVal) = aP;
    }

    if (theArrOfToler)
    {
      (*theArrOfToler)(aRetVal) = BRep_Tool::Tolerance(aVert);
    }

    ++aRetVal;
  }

  if (aRetVal == 0)
    return 0;

  TopLoc_Location aLoc;
  for (anExpF.Init(theS, TopAbs_FACE); anExpF.More(); anExpF.Next())
  {
    const TopoDS_Face&        aF = TopoDS::Face(anExpF.Current());
    const BRepAdaptor_Surface anAS(aF, false);

    if (!IsPlanar(anAS.Surface()))
    {
      if (!theIsTriangulationUsed)

        return 0;
    }
    else
    {

      for (anExpE.Init(aF, TopAbs_EDGE); anExpE.More(); anExpE.Next())
      {
        const TopoDS_Edge& anE = TopoDS::Edge(anExpE.Current());
        if (BRep_Tool::IsGeometric(anE))
        {
          const BRepAdaptor_Curve anAC(anE);
          if (!IsLinear(anAC))
          {
            if (!theIsTriangulationUsed)

              return 0;

            break;
          }
        }
      }

      if (!anExpE.More())

        continue;
    }

    const occ::handle<Poly_Triangulation>& aTrng = BRep_Tool::Triangulation(aF, aLoc);
    if (aTrng.IsNull())
    {

      return 0;
    }

    const int     aCNode = aTrng->NbNodes();
    const gp_Trsf aTrsf  = aLoc;
    for (int i = 1; i <= aCNode; i++)
    {
      if (thePts != nullptr)
      {
        const gp_Pnt aP =
          aTrsf.Form() == gp_Identity ? aTrng->Node(i) : aTrng->Node(i).Transformed(aTrsf);
        (*thePts)(aRetVal) = aP;
      }

      if (theArrOfToler != nullptr)
      {
        (*theArrOfToler)(aRetVal) = aTrng->Deflection();
      }

      ++aRetVal;
    }
  }

  for (anExpE.Init(theS, TopAbs_EDGE, TopAbs_FACE); anExpE.More(); anExpE.Next())
  {
    const TopoDS_Edge& anE = TopoDS::Edge(anExpE.Current());
    if (BRep_Tool::IsGeometric(anE))
    {
      const BRepAdaptor_Curve anAC(anE);
      if (IsLinear(anAC))
      {

        continue;
      }
    }

    if (!theIsTriangulationUsed)

      return 0;

    const occ::handle<Poly_Polygon3D>& aPolygon = BRep_Tool::Polygon3D(anE, aLoc);
    if (aPolygon.IsNull())
      return 0;

    const int                         aCNode    = aPolygon->NbNodes();
    const NCollection_Array1<gp_Pnt>& aNodesArr = aPolygon->Nodes();
    for (int i = 1; i <= aCNode; i++)
    {
      if (thePts)
      {
        const gp_Pnt aP    = aLoc.IsIdentity() ? aNodesArr[i] : aNodesArr[i].Transformed(aLoc);
        (*thePts)(aRetVal) = aP;
      }

      if (theArrOfToler)
      {
        (*theArrOfToler)(aRetVal) = aPolygon->Deflection();
      }

      ++aRetVal;
    }
  }

  return aRetVal;
}

static int IsWCS(const gp_Dir& theDir)
{
  constexpr double aToler = Precision::Angular() * Precision::Angular();

  const double aX = theDir.X(), aY = theDir.Y(), aZ = theDir.Z();

  const double aVx = aY * aY + aZ * aZ, aVy = aX * aX + aZ * aZ, aVz = aX * aX + aY * aY;

  if (aVz < aToler)
    return 3;

  if (aVy < aToler)
    return 2;

  if (aVx < aToler)
    return 1;

  return 0;
}

static bool CheckPoints(const TopoDS_Shape& theS,
                        const bool          theIsTriangulationUsed,
                        const bool          theIsOptimal,
                        const bool          theIsShapeToleranceUsed,
                        Bnd_OBB&            theOBB)
{
  const int aNbPnts = PointsForOBB(theS, theIsTriangulationUsed);

  if (aNbPnts < 1)
    return false;

  NCollection_Array1<gp_Pnt> anArrPnts(0, theOBB.IsVoid() ? aNbPnts - 1 : aNbPnts + 7);
  NCollection_Array1<double> anArrOfTolerances;
  if (theIsShapeToleranceUsed)
  {
    anArrOfTolerances.Resize(anArrPnts.Lower(), anArrPnts.Upper(), false);
    anArrOfTolerances.Init(0.0);
  }

  NCollection_Array1<double>* aPtrArrTol = theIsShapeToleranceUsed ? &anArrOfTolerances : nullptr;

  PointsForOBB(theS, theIsTriangulationUsed, &anArrPnts, aPtrArrTol);

  if (!theOBB.IsVoid())
  {

    theOBB.GetVertex(&anArrPnts(aNbPnts));
  }

  theOBB.ReBuild(anArrPnts, aPtrArrTol, theIsOptimal);

  return (!theOBB.IsVoid());
}

static void ComputeProperties(const TopoDS_Shape& theS, GProp_GProps& theGCommon)
{
  TopExp_Explorer anExp;
  for (anExp.Init(theS, TopAbs_SOLID); anExp.More(); anExp.Next())
  {
    GProp_GProps aG;
    BRepGProp::VolumeProperties(anExp.Current(), aG, true);
    theGCommon.Add(aG);
  }

  for (anExp.Init(theS, TopAbs_FACE, TopAbs_SOLID); anExp.More(); anExp.Next())
  {
    GProp_GProps aG;
    BRepGProp::SurfaceProperties(anExp.Current(), aG, true);
    theGCommon.Add(aG);
  }

  for (anExp.Init(theS, TopAbs_EDGE, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    GProp_GProps aG;
    BRepGProp::LinearProperties(anExp.Current(), aG, true);
    theGCommon.Add(aG);
  }

  for (anExp.Init(theS, TopAbs_VERTEX, TopAbs_EDGE); anExp.More(); anExp.Next())
  {
    GProp_GProps aG(BRep_Tool::Pnt(TopoDS::Vertex(anExp.Current())));
    theGCommon.Add(aG);
  }
}

static void ComputePCA(const TopoDS_Shape& theS,
                       Bnd_OBB&            theOBB,
                       const bool          theIsTriangulationUsed,
                       const bool          theIsOptimal,
                       const bool          theIsShapeToleranceUsed)
{

  GProp_GProps aGCommon;
  ComputeProperties(theS, aGCommon);

  gp_Trsf aTrsf;

  const int anIdx1 = IsWCS(aGCommon.PrincipalProperties().FirstAxisOfInertia());
  const int anIdx2 = IsWCS(aGCommon.PrincipalProperties().SecondAxisOfInertia());

  if ((anIdx1 == 0) || (anIdx2 == 0))
  {

    gp_Ax3 aLocCoordSys(aGCommon.CentreOfMass(),
                        aGCommon.PrincipalProperties().ThirdAxisOfInertia(),
                        aGCommon.PrincipalProperties().FirstAxisOfInertia());
    aTrsf.SetTransformation(aLocCoordSys);
  }

  const TopoDS_Shape aST =
    (aTrsf.Form() == gp_Identity) ? theS : theS.Moved(TopLoc_Location(aTrsf));

  Bnd_Box aShapeBox;
  if (theIsOptimal)
  {
    BRepBndLib::AddOptimal(aST, aShapeBox, theIsTriangulationUsed, theIsShapeToleranceUsed);
  }
  else
  {
    BRepBndLib::Add(aST, aShapeBox);
  }
  if (aShapeBox.IsVoid())
  {
    return;
  }

  gp_Pnt aPMin = aShapeBox.CornerMin();
  gp_Pnt aPMax = aShapeBox.CornerMax();

  gp_XYZ aXDir(1, 0, 0);
  gp_XYZ aYDir(0, 1, 0);
  gp_XYZ aZDir(0, 0, 1);

  gp_XYZ aCenter = (aPMin.XYZ() + aPMax.XYZ()) / 2.;

  gp_XYZ anOBBHSize = (aPMax.XYZ() - aPMin.XYZ()) / 2.;

  if (aTrsf.Form() != gp_Identity)
  {
    aTrsf.Invert();
    aTrsf.Transforms(aCenter);

    const double* aMat = &aTrsf.HVectorialPart().Value(1, 1);

    aXDir = gp_XYZ(aMat[0], aMat[3], aMat[6]);
    aYDir = gp_XYZ(aMat[1], aMat[4], aMat[7]);
    aZDir = gp_XYZ(aMat[2], aMat[5], aMat[8]);
  }

  if (theOBB.IsVoid())
  {

    theOBB.SetCenter(aCenter);

    theOBB.SetXComponent(aXDir, anOBBHSize.X());
    theOBB.SetYComponent(aYDir, anOBBHSize.Y());
    theOBB.SetZComponent(aZDir, anOBBHSize.Z());
    theOBB.SetAABox(aTrsf.Form() == gp_Identity);
  }
  else
  {

    NCollection_Array1<gp_Pnt> aListOfPnts(0, 15);
    theOBB.GetVertex(&aListOfPnts(0));

    const double aX = anOBBHSize.X();
    const double aY = anOBBHSize.Y();
    const double aZ = anOBBHSize.Z();

    const gp_XYZ aXext = aX * aXDir, aYext = aY * aYDir, aZext = aZ * aZDir;

    int aPntIdx            = 8;
    aListOfPnts(aPntIdx++) = aCenter - aXext - aYext - aZext;
    aListOfPnts(aPntIdx++) = aCenter + aXext - aYext - aZext;
    aListOfPnts(aPntIdx++) = aCenter - aXext + aYext - aZext;
    aListOfPnts(aPntIdx++) = aCenter + aXext + aYext - aZext;
    aListOfPnts(aPntIdx++) = aCenter - aXext - aYext + aZext;
    aListOfPnts(aPntIdx++) = aCenter + aXext - aYext + aZext;
    aListOfPnts(aPntIdx++) = aCenter - aXext + aYext + aZext;
    aListOfPnts(aPntIdx++) = aCenter + aXext + aYext + aZext;

    theOBB.ReBuild(aListOfPnts);
  }
}

void BRepBndLib::AddOBB(const TopoDS_Shape& theS,
                        Bnd_OBB&            theOBB,
                        const bool          theIsTriangulationUsed,
                        const bool          theIsOptimal,
                        const bool          theIsShapeToleranceUsed)
{
  if (CheckPoints(theS, theIsTriangulationUsed, theIsOptimal, theIsShapeToleranceUsed, theOBB))
    return;

  ComputePCA(theS, theOBB, theIsTriangulationUsed, theIsOptimal, theIsShapeToleranceUsed);
}
