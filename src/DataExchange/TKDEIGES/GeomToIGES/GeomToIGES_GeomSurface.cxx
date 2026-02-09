

#include <gce_MakeLin.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BoundedSurface.hpp>
#include <Geom_CartesianPoint.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_SweptSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomLProp_SLProps.hpp>
#include <GeomToIGES_GeomCurve.hpp>
#include <GeomToIGES_GeomEntity.hpp>
#include <GeomToIGES_GeomPoint.hpp>
#include <GeomToIGES_GeomSurface.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_XYZ.hpp>
#include <IGESConvGeom_GeomBuilder.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis.hpp>
#include <Standard_ErrorHandler.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

GeomToIGES_GeomSurface::GeomToIGES_GeomSurface()

{
  myBRepMode = false;
  myAnalytic = false;
}

GeomToIGES_GeomSurface::GeomToIGES_GeomSurface(const GeomToIGES_GeomEntity& GE)
    : GeomToIGES_GeomEntity(GE)
{
  myBRepMode = false;
  myAnalytic = false;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_Surface>& start,
  const double                     Udeb,
  const double                     Ufin,
  const double                     Vdeb,
  const double                     Vfin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_BoundedSurface)))
  {
    DeclareAndCast(Geom_BoundedSurface, Bounded, start);
    res = TransferSurface(Bounded, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_ElementarySurface)))
  {
    DeclareAndCast(Geom_ElementarySurface, Elementary, start);
    res = TransferSurface(Elementary, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_SweptSurface)))
  {
    DeclareAndCast(Geom_SweptSurface, Swept, start);
    res = TransferSurface(Swept, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
  {
    DeclareAndCast(Geom_OffsetSurface, OffsetS, start);
    res = TransferSurface(OffsetS, Udeb, Ufin, Vdeb, Vfin);
  }

  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_BoundedSurface>& start,
  const double                            Udeb,
  const double                            Ufin,
  const double                            Vdeb,
  const double                            Vfin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
  {
    DeclareAndCast(Geom_BSplineSurface, BSpline, start);
    res = TransferSurface(BSpline, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_BezierSurface)))
  {
    DeclareAndCast(Geom_BezierSurface, Bezier, start);
    res = TransferSurface(Bezier, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    DeclareAndCast(Geom_RectangularTrimmedSurface, Trimmed, start);
    res = TransferSurface(Trimmed, Udeb, Ufin, Vdeb, Vfin);
  }

  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_BSplineSurface>& start,
  const double                            Udeb,
  const double                            Ufin,
  const double                            Vdeb,
  const double                            Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_BSplineSurface> BSpline = new IGESGeom_BSplineSurface;
  occ::handle<Geom_BSplineSurface>     mysurface;

  bool PeriodU = start->IsUPeriodic();
  bool PeriodV = start->IsVPeriodic();
  mysurface    = occ::down_cast<Geom_BSplineSurface>(start->Copy());

  double Umin = Udeb, Umax = Ufin, Vmin = Vdeb, Vmax = Vfin;
  double U0, U1, V0, V1;
  double uShift = 0, vShift = 0;
  mysurface->Bounds(U0, U1, V0, V1);

  if (!PeriodU)
  {
    if (Umin < U0)
      Umin = U0;
    if (U1 < Umax)
      Umax = U1;
  }
  else
  {
    if (std::abs(Umin - U0) < Precision::PConfusion())
      Umin = U0;
    if (std::abs(Umax - U1) < Precision::PConfusion())
      Umax = U1;
    uShift = ShapeAnalysis::AdjustToPeriod(Umin, U0, U1);
    Umin += uShift;
    Umax += uShift;
    if (Umax - Umin > U1 - U0)
      Umax = Umin + (U1 - U0);
  }
  if (!PeriodV)
  {
    if (Vmin < V0)
      Vmin = V0;
    if (V1 < Vmax)
      Vmax = V1;
  }
  else
  {
    if (std::abs(Vmin - V0) < Precision::PConfusion())
      Vmin = V0;
    if (std::abs(Vmax - V1) < Precision::PConfusion())
      Vmax = V1;
    vShift = ShapeAnalysis::AdjustToPeriod(Vmin, V0, V1);
    Vmin += vShift;
    Vmax += vShift;
    if (Vmax - Vmin > V1 - V0)
      Vmax = Vmin + (V1 - V0);
  }

  if (mysurface->IsUPeriodic())
  {

    if (mysurface->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
    {
      double uMaxShift = 0;
      uMaxShift        = ShapeAnalysis::AdjustToPeriod(Ufin, U0, U1);
      if (std::abs(uShift - uMaxShift) > Precision::PConfusion())
      {
        occ::handle<Geom_BSplineSurface> aBspl =
          occ::down_cast<Geom_BSplineSurface>(mysurface->Copy());
        int aLeft, aRight;
        aBspl->LocateU(Umin, Precision::PConfusion(), aLeft, aRight);
        aBspl->SetUOrigin(aLeft);
        mysurface = aBspl;
      }
    }
    mysurface->SetUNotPeriodic();
  }
  if (mysurface->IsVPeriodic())
  {

    if (mysurface->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
    {
      double vMaxShift = 0;
      vMaxShift        = ShapeAnalysis::AdjustToPeriod(Vfin, V0, V1);
      if (std::abs(vShift - vMaxShift) > Precision::PConfusion())
      {
        occ::handle<Geom_BSplineSurface> aBspl =
          occ::down_cast<Geom_BSplineSurface>(mysurface->Copy());
        int aLeft, aRight;
        aBspl->LocateV(Vmin, Precision::PConfusion(), aLeft, aRight);
        aBspl->SetVOrigin(aLeft);
        mysurface = aBspl;
      }
    }
    mysurface->SetVNotPeriodic();
  }

  int  DegU     = mysurface->UDegree();
  int  DegV     = mysurface->VDegree();
  bool CloseU   = mysurface->IsUClosed();
  bool CloseV   = mysurface->IsVClosed();
  bool RationU  = mysurface->IsURational();
  bool RationV  = mysurface->IsVRational();
  int  NbUPoles = mysurface->NbUPoles();
  int  NbVPoles = mysurface->NbVPoles();
  int  IndexU   = NbUPoles - 1;
  int  IndexV   = NbVPoles - 1;
  bool Polynom  = !(RationU || RationV);

  int                        Knotindex;
  double                     rtampon;
  int                        itampon;
  NCollection_Array1<double> KU(1, NbUPoles + DegU + 1);
  mysurface->UKnotSequence(KU);
  itampon = -DegU;
  occ::handle<NCollection_HArray1<double>> KnotsU =
    new NCollection_HArray1<double>(-DegU, IndexU + 1);
  for (Knotindex = KU.Lower(); Knotindex <= KU.Upper(); Knotindex++)
  {
    rtampon = KU.Value(Knotindex);
    KnotsU->SetValue(itampon, rtampon);
    itampon++;
  }

  NCollection_Array1<double> KV(1, NbVPoles + DegV + 1);
  mysurface->VKnotSequence(KV);
  itampon = -DegV;
  occ::handle<NCollection_HArray1<double>> KnotsV =
    new NCollection_HArray1<double>(-DegV, IndexV + 1);
  for (Knotindex = KV.Lower(); Knotindex <= KV.Upper(); Knotindex++)
  {
    rtampon = KV.Value(Knotindex);
    KnotsV->SetValue(itampon, rtampon);
    itampon++;
  }

  occ::handle<NCollection_HArray2<double>> Weights =
    new NCollection_HArray2<double>(0, IndexU, 0, IndexV);
  int WeightRow = Weights->LowerRow();
  int WeightCol = Weights->LowerCol();
  int iw, jw;

  if (RationU || RationV)
  {
    for (iw = 1; iw <= IndexU + 1; iw++)
    {
      for (jw = 1; jw <= IndexV + 1; jw++)
        Weights->SetValue(WeightRow, WeightCol++, mysurface->Weight(iw, jw));
      WeightRow++;
      WeightCol = Weights->LowerCol();
    }
  }
  else
  {
    for (iw = 1; iw <= IndexU + 1; iw++)
    {
      for (jw = 1; jw <= IndexV + 1; jw++)
        Weights->SetValue(WeightRow, WeightCol++, 1.0);
      WeightRow++;
      WeightCol = Weights->LowerCol();
    }
  }

  occ::handle<NCollection_HArray2<gp_XYZ>> Poles =
    new NCollection_HArray2<gp_XYZ>(0, IndexU, 0, IndexV);
  int    UIndex = Poles->LowerRow();
  int    VIndex = Poles->LowerCol();
  int    ipole, jpole;
  double Xd, Yd, Zd;

  for (ipole = 1; ipole <= IndexU + 1; ipole++)
  {
    for (jpole = 1; jpole <= IndexV + 1; jpole++)
    {
      gp_Pnt tempPnt = mysurface->Pole(ipole, jpole);
      tempPnt.Coord(Xd, Yd, Zd);
      gp_XYZ PXYZ = gp_XYZ(Xd / GetUnit(), Yd / GetUnit(), Zd / GetUnit());
      Poles->SetValue(UIndex, VIndex++, PXYZ);
    }
    UIndex++;
    VIndex = Poles->LowerCol();
  }

  BSpline->Init(IndexU,
                IndexV,
                DegU,
                DegV,
                CloseU,
                CloseV,
                Polynom,
                PeriodU,
                PeriodV,
                KnotsU,
                KnotsV,
                Weights,
                Poles,
                Umin,
                Umax,
                Vmin,
                Vmax);
  res = BSpline;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_BezierSurface>& start,
  const double,
  const double,
  const double,
  const double)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<Geom_BSplineSurface> Bspline = GeomConvert::SurfaceToBSplineSurface(start);
  double                           U1, U2, V1, V2;
  Bspline->Bounds(U1, U2, V1, V2);
  res = TransferSurface(Bspline, U1, U2, V1, V2);
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_RectangularTrimmedSurface>& start,
  const double                                       Udeb,
  const double                                       Ufin,
  const double                                       Vdeb,
  const double                                       Vfin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<Geom_Surface> st = start->BasisSurface();
  if (st->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {

    return res;
  }

  res = TransferSurface(st, Udeb, Ufin, Vdeb, Vfin);
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_ElementarySurface>& start,
  const double                               Udeb,
  const double                               Ufin,
  const double                               Vdeb,
  const double                               Vfin)
{
  occ::handle<IGESData_IGESEntity> res;

  if (start.IsNull())
  {
    return res;
  }
  if (start->IsKind(STANDARD_TYPE(Geom_Plane)))
  {
    DeclareAndCast(Geom_Plane, Plane, start);
    if (myBRepMode)
      res = TransferPlaneSurface(Plane, Udeb, Ufin, Vdeb, Vfin);
    else
      res = TransferSurface(Plane, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
  {
    DeclareAndCast(Geom_CylindricalSurface, Cylindrical, start);
    if (myBRepMode && myAnalytic)
      res = TransferCylindricalSurface(Cylindrical, Udeb, Ufin, Vdeb, Vfin);
    else
      res = TransferSurface(Cylindrical, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
  {
    DeclareAndCast(Geom_ConicalSurface, Conical, start);
    if (myBRepMode && myAnalytic)
      res = TransferConicalSurface(Conical, Udeb, Ufin, Vdeb, Vfin);
    else
      res = TransferSurface(Conical, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
  {
    DeclareAndCast(Geom_SphericalSurface, Spherical, start);
    if (myBRepMode && myAnalytic)
      res = TransferSphericalSurface(Spherical, Udeb, Ufin, Vdeb, Vfin);
    else
      res = TransferSurface(Spherical, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
  {
    DeclareAndCast(Geom_ToroidalSurface, Toroidal, start);
    if (myBRepMode && myAnalytic)
      res = TransferToroidalSurface(Toroidal, Udeb, Ufin, Vdeb, Vfin);
    else
      res = TransferSurface(Toroidal, Udeb, Ufin, Vdeb, Vfin);
  }

  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_Plane>& start,
  const double                   Udeb,
  const double                   Ufin,
  const double                   Vdeb,
  const double                   Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }
  if (Interface_Static::IVal("write.iges.plane.mode") == 0)
  {
    occ::handle<IGESGeom_Plane> aPlane = new IGESGeom_Plane;
    double                      A, B, C, D;
    start->Coefficients(A, B, C, D);
    D               = -D;
    gp_XYZ anAttach = start->Location().XYZ().Divided(GetUnit());
    aPlane->Init(A, B, C, D / GetUnit(), nullptr, anAttach, 0);
    res = aPlane;
    return res;
  }
  else
  {
    occ::handle<IGESGeom_BSplineSurface> BSpline = new IGESGeom_BSplineSurface;
    gp_Pnt                               P1, P2, P3, P4;
    start->D0(Udeb, Vdeb, P1);
    start->D0(Udeb, Vfin, P2);
    start->D0(Ufin, Vdeb, P3);
    start->D0(Ufin, Vfin, P4);
    occ::handle<NCollection_HArray2<gp_XYZ>> Poles = new NCollection_HArray2<gp_XYZ>(0, 1, 0, 1);
    double                                   X, Y, Z;
    P1.Coord(X, Y, Z);
    Poles->SetValue(0, 0, gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()));
    P2.Coord(X, Y, Z);
    Poles->SetValue(0, 1, gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()));
    P3.Coord(X, Y, Z);
    Poles->SetValue(1, 0, gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()));
    P4.Coord(X, Y, Z);
    Poles->SetValue(1, 1, gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()));

    occ::handle<NCollection_HArray1<double>> KnotsU = new NCollection_HArray1<double>(-1, 2);
    KnotsU->SetValue(-1, Udeb);
    KnotsU->SetValue(0, Udeb);
    KnotsU->SetValue(1, Ufin);
    KnotsU->SetValue(2, Ufin);

    occ::handle<NCollection_HArray1<double>> KnotsV = new NCollection_HArray1<double>(-1, 2);
    KnotsV->SetValue(-1, Vdeb);
    KnotsV->SetValue(0, Vdeb);
    KnotsV->SetValue(1, Vfin);
    KnotsV->SetValue(2, Vfin);

    occ::handle<NCollection_HArray2<double>> Weights =
      new NCollection_HArray2<double>(0, 1, 0, 1, 1.);

    BSpline->Init(1,
                  1,
                  1,
                  1,
                  false,
                  false,
                  true,
                  false,
                  false,
                  KnotsU,
                  KnotsV,
                  Weights,
                  Poles,
                  Udeb,
                  Ufin,
                  Vdeb,
                  Vfin);
    res = BSpline;
    return res;
  }
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_CylindricalSurface>& start,
  const double                                Udeb,
  const double                                Ufin,
  const double                                Vdeb,
  const double                                Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_SurfaceOfRevolution> Surf = new IGESGeom_SurfaceOfRevolution;
  double                                    U1   = Udeb;
  double                                    U2   = Ufin;
  double                                    V1   = Vdeb;
  double                                    V2   = Vfin;
  if (Precision::IsNegativeInfinite(Vdeb))
    V1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Vfin))
    V2 = Precision::Infinite();

  occ::handle<Geom_Line> Ligne =
    new Geom_Line(gp_Pnt(start->Cylinder().Radius(), 0.0, 0.0), gp_Dir(gp_Dir::D::Z));
  GeomToIGES_GeomCurve             GC(*this);
  occ::handle<IGESData_IGESEntity> Generatrix = GC.TransferCurve(Ligne, V1, V2);
  gp_Pnt                           gen1       = Ligne->Value(V1);
  gp_Pnt                           gen2       = Ligne->Value(V2);
  TheLength                                   = gen1.Distance(gen2);

  occ::handle<IGESGeom_Line> Axis = new IGESGeom_Line;

  Axis->Init(gp_XYZ(0, 0, 1.), gp_XYZ(0, 0, 0));
  Surf->Init(Axis, Generatrix, 2 * M_PI - U2, 2 * M_PI - U1);

  IGESConvGeom_GeomBuilder Build;
  double                   xloc, yloc, zloc;
  start->Cylinder().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = start->Cylinder().Position();
  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);
  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Surf->InitTransf(TMat);
  }
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_ConicalSurface>& start,
  const double                            Udeb,
  const double                            Ufin,
  const double                            Vdeb,
  const double                            Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }
  occ::handle<IGESGeom_SurfaceOfRevolution> Surf = new IGESGeom_SurfaceOfRevolution;
  double                                    U1   = Udeb;
  double                                    U2   = Ufin;
  double                                    V1   = Vdeb;
  double                                    V2   = Vfin;
  if (Precision::IsNegativeInfinite(Vdeb))
    V1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Vfin))
    V2 = Precision::Infinite();

  occ::handle<Geom_Line> Ligne =
    new Geom_Line(gp_Pnt(start->Cone().RefRadius(), 0.0, 0.0),
                  gp_Dir(sin(start->Cone().SemiAngle()), 0., cos(start->Cone().SemiAngle())));
  GeomToIGES_GeomCurve             GC(*this);
  occ::handle<IGESData_IGESEntity> Generatrix = GC.TransferCurve(Ligne, V1, V2);
  gp_Pnt                           gen1       = Ligne->Value(V1);
  gp_Pnt                           gen2       = Ligne->Value(V2);
  TheLength                                   = gen1.Distance(gen2);

  occ::handle<IGESGeom_Line> Axis = new IGESGeom_Line;

  Axis->Init(gp_XYZ(0, 0, 1.), gp_XYZ(0, 0, 0));
  Surf->Init(Axis, Generatrix, 2 * M_PI - U2, 2 * M_PI - U1);

  IGESConvGeom_GeomBuilder Build;
  double                   xloc, yloc, zloc;
  start->Cone().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = start->Cone().Position();
  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);
  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Surf->InitTransf(TMat);
  }
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_SphericalSurface>& start,
  const double                              Udeb,
  const double                              Ufin,
  const double                              Vdeb,
  const double                              Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_SurfaceOfRevolution> Surf = new IGESGeom_SurfaceOfRevolution;

  double U1 = Udeb;
  double U2 = Ufin;
  double V1 = Vdeb;
  double V2 = Vfin;

  gp_Ax2                           Axe(gp::Origin(), -gp::DY(), gp::DX());
  occ::handle<Geom_Circle>         Cercle = new Geom_Circle(Axe, start->Sphere().Radius());
  GeomToIGES_GeomCurve             GC(*this);
  occ::handle<IGESData_IGESEntity> Gen = GC.TransferCurve(Cercle, V1, V2);

  occ::handle<IGESGeom_Line> Axis = new IGESGeom_Line;

  Axis->Init(gp_XYZ(0, 0, 1.), gp_XYZ(0, 0, 0));

  if (Gen->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
  {

    Surf->Init(Axis, Gen, 2 * M_PI - U2, 2 * M_PI - U1);
    IGESConvGeom_GeomBuilder Build;
    double                   xloc, yloc, zloc;
    start->Sphere().Location().Coord(xloc, yloc, zloc);
    gp_Pnt Loc;
    Loc.SetCoord(xloc, yloc, zloc);
    gp_Ax3 Pos = start->Sphere().Position();
    Pos.SetLocation(Loc);
    Build.SetPosition(Pos);
    if (!Build.IsIdentity())
    {
      occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
      TMat                                            = Build.MakeTransformation(GetUnit());
      Surf->InitTransf(TMat);
    }
  }
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_ToroidalSurface>& start,
  const double                             Udeb,
  const double                             Ufin,
  const double                             Vdeb,
  const double                             Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_SurfaceOfRevolution> Surf = new IGESGeom_SurfaceOfRevolution;
  double                                    U1   = Udeb;
  double                                    U2   = Ufin;
  double                                    V1   = Vdeb;
  double                                    V2   = Vfin;

  gp_Ax2 Axe = gp_Ax2(gp_Pnt((start->Torus().MajorRadius()), 0., 0.), -gp::DY(), gp::DX());
  occ::handle<Geom_Circle>         Cercle = new Geom_Circle(Axe, start->Torus().MinorRadius());
  GeomToIGES_GeomCurve             GC(*this);
  occ::handle<IGESData_IGESEntity> Gen = GC.TransferCurve(Cercle, V1, V2);

  occ::handle<IGESGeom_Line> Axis = new IGESGeom_Line;

  Axis->Init(gp_XYZ(0, 0, 1.), gp_XYZ(0, 0, 0));

  Surf->Init(Axis, Gen, 2 * M_PI - U2, 2 * M_PI - U1);
  IGESConvGeom_GeomBuilder Build;

  gp_Ax3 Pos = start->Torus().Position();

  Build.SetPosition(Pos);
  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Surf->InitTransf(TMat);
  }

  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_SweptSurface>& start,
  const double                          Udeb,
  const double                          Ufin,
  const double                          Vdeb,
  const double                          Vfin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))
  {
    DeclareAndCast(Geom_SurfaceOfLinearExtrusion, Extrusion, start);
    res = TransferSurface(Extrusion, Udeb, Ufin, Vdeb, Vfin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
  {
    DeclareAndCast(Geom_SurfaceOfRevolution, Revolution, start);
    res = TransferSurface(Revolution, Udeb, Ufin, Vdeb, Vfin);
  }

  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_SurfaceOfLinearExtrusion>& start,
  const double                                      Udeb,
  const double                                      Ufin,
  const double                                      Vdeb,
  const double                                      Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_TabulatedCylinder> Surf = new IGESGeom_TabulatedCylinder;
  double                                  U1   = Udeb;
  double                                  U2   = Ufin;
  double                                  V1   = Vdeb;
  double                                  V2   = Vfin;
  if (Precision::IsNegativeInfinite(Vdeb))
    V1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Vfin))
    V2 = Precision::Infinite();

  double UF, UL, VF, VL;
  start->Bounds(UF, UL, VF, VL);
  U1 = UF;
  U2 = UL;

  occ::handle<Geom_Curve> TheCurve = start->BasisCurve();

  gp_Pnt TheEnd = start->Value(U1, V2);
  double Xe, Ye, Ze;
  TheEnd.Coord(Xe, Ye, Ze);
  gp_XYZ End = gp_XYZ(Xe / GetUnit(), Ye / GetUnit(), Ze / GetUnit());

  GeomToIGES_GeomCurve GC(*this);

  occ::handle<Geom_Curve> CopyCurve;
  if (std::abs(V1) > Precision::Confusion())
  {
    CopyCurve =
      occ::down_cast<Geom_Curve>(TheCurve->Translated(start->Value(U1, 0.), start->Value(U1, V1)));
  }
  else
  {
    CopyCurve = TheCurve;
  }

  occ::handle<IGESData_IGESEntity> Directrix = GC.TransferCurve(CopyCurve, U1, U2);

  Surf->Init(Directrix, End);
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_SurfaceOfRevolution>& start,
  const double                                 Udeb,
  const double                                 Ufin,
  const double                                 Vdeb,
  const double                                 Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_SurfaceOfRevolution> Surf = new IGESGeom_SurfaceOfRevolution;
  double                                    U1   = Udeb;
  double                                    U2   = Ufin;
  double                                    V1   = Vdeb;
  double                                    V2   = Vfin;
  if (Precision::IsNegativeInfinite(Vdeb))
    V1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Vfin))
    V2 = Precision::Infinite();

  occ::handle<Geom_Curve>          Curve = start->BasisCurve();
  GeomToIGES_GeomCurve             GC(*this);
  occ::handle<IGESData_IGESEntity> Generatrix = GC.TransferCurve(Curve, V1, V2);

  while (Curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> aTrCurve = occ::down_cast<Geom_TrimmedCurve>(Curve);
    Curve                                   = aTrCurve->BasisCurve();
  }

  if (Curve->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    DeclareAndCast(Geom_Line, Line, Curve);
    gp_Pnt gen1 = Line->Value(V1);
    gp_Pnt gen2 = Line->Value(V2);
    TheLength   = gen1.Distance(gen2);
  }

  occ::handle<IGESGeom_Line> Axis = new IGESGeom_Line;
  gp_Ax1                     Axe  = start->Axis();
  double                     X1, Y1, Z1, X2, Y2, Z2;
  Axe.Location().Coord(X1, Y1, Z1);
  Axe.Direction().Coord(X2, Y2, Z2);

  Axis->Init(gp_XYZ(X1 / GetUnit(), Y1 / GetUnit(), Z1 / GetUnit()),
             gp_XYZ((X1 - X2) / GetUnit(), (Y1 - Y2) / GetUnit(), (Z1 - Z2) / GetUnit()));

  Surf->Init(Axis, Generatrix, 2 * M_PI - U2, 2 * M_PI - U1);
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSurface(
  const occ::handle<Geom_OffsetSurface>& start,
  const double                           Udeb,
  const double                           Ufin,
  const double                           Vdeb,
  const double                           Vfin)
{

  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_OffsetSurface> Surf    = new IGESGeom_OffsetSurface;
  occ::handle<Geom_Surface>           TheSurf = start->BasisSurface();
  double                              U1, U2, V1, V2, Um, Vm;
  start->Bounds(U1, U2, V1, V2);
  Um                                        = (U1 + U2) / 2.;
  Vm                                        = (V1 + V2) / 2.;
  occ::handle<IGESData_IGESEntity> Surface  = TransferSurface(TheSurf, Udeb, Ufin, Vdeb, Vfin);
  double                           Distance = start->Offset() / GetUnit();
  GeomLProp_SLProps Prop = GeomLProp_SLProps(TheSurf, Um, Vm, 1, Precision::Confusion());
  gp_Dir            Dir  = Prop.Normal();
  double            Xd, Yd, Zd;
  Dir.Coord(Xd, Yd, Zd);
  gp_XYZ Indicator = gp_XYZ(Xd / GetUnit(), Yd / GetUnit(), Zd / GetUnit());

  Surf->Init(Indicator, Distance, Surface);
  res = Surf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferPlaneSurface(
  const occ::handle<Geom_Plane>& start,
  const double,
  const double,
  const double,
  const double)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESSolid_PlaneSurface> Plsurf = new IGESSolid_PlaneSurface;
  GeomToIGES_GeomPoint                GP(*this);

  gp_Pln aPln = start->Pln();

  occ::handle<Geom_CartesianPoint> mypoint   = new Geom_CartesianPoint(aPln.Location());
  occ::handle<IGESGeom_Point>      aLocation = GP.TransferPoint(mypoint);

  occ::handle<IGESGeom_Direction> aNormal = new IGESGeom_Direction;
  aNormal->Init(aPln.Axis().Direction().XYZ());

  occ::handle<IGESGeom_Direction> aRefDir = new IGESGeom_Direction;
  aRefDir->Init(aPln.XAxis().Direction().XYZ());

  Plsurf->Init(aLocation, aNormal, aRefDir);
  res = Plsurf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferCylindricalSurface(
  const occ::handle<Geom_CylindricalSurface>& start,
  const double,
  const double,
  const double,
  const double)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESSolid_CylindricalSurface> CylSurf = new IGESSolid_CylindricalSurface;
  GeomToIGES_GeomPoint                      GP(*this);

  gp_Cylinder aCyl = start->Cylinder();

  occ::handle<Geom_CartesianPoint> mypoint   = new Geom_CartesianPoint(aCyl.Location());
  occ::handle<IGESGeom_Point>      aLocation = GP.TransferPoint(mypoint);

  occ::handle<IGESGeom_Direction> anAxis = new IGESGeom_Direction;
  anAxis->Init(aCyl.Axis().Direction().XYZ());

  occ::handle<IGESGeom_Direction> aRefDir = new IGESGeom_Direction;
  aRefDir->Init(aCyl.XAxis().Direction().XYZ());

  double aRadius = aCyl.Radius() / GetUnit();

  CylSurf->Init(aLocation, anAxis, aRadius, aRefDir);
  res = CylSurf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferConicalSurface(
  const occ::handle<Geom_ConicalSurface>& start,
  const double,
  const double,
  const double,
  const double)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESSolid_ConicalSurface> ConSurf = new IGESSolid_ConicalSurface;
  GeomToIGES_GeomPoint                  GP(*this);

  gp_Cone Con     = start->Cone();
  double  aRadius = Con.RefRadius() / GetUnit();
  double  angle   = Con.SemiAngle();
  gp_Ax1  Axe     = Con.Axis();
  gp_Ax1  XAxe    = Con.XAxis();
  gp_Dir  XDir    = XAxe.Direction();

  occ::handle<Geom_CartesianPoint> mypoint = new Geom_CartesianPoint(Con.Location());
  if (angle < 0.)
  {
    gp_Pnt pnt = mypoint->Pnt();
    mypoint->SetPnt(Con.Apex().XYZ() * 2 - pnt.XYZ());
    angle = -angle;
    XDir.Reverse();
  }
  occ::handle<IGESGeom_Point> aLocation = GP.TransferPoint(mypoint);

  occ::handle<IGESGeom_Direction> anAxis = new IGESGeom_Direction;
  anAxis->Init(Axe.Direction().XYZ());

  occ::handle<IGESGeom_Direction> aRefDir = new IGESGeom_Direction;
  aRefDir->Init(XDir.XYZ());

  ConSurf->Init(aLocation, anAxis, aRadius, angle * 180. / M_PI, aRefDir);
  res = ConSurf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferSphericalSurface(
  const occ::handle<Geom_SphericalSurface>& start,
  const double,
  const double,
  const double,
  const double)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESSolid_SphericalSurface> SphSurf = new IGESSolid_SphericalSurface;
  GeomToIGES_GeomPoint                    GP(*this);

  gp_Sphere aSph = start->Sphere();

  occ::handle<Geom_CartesianPoint> mypoint   = new Geom_CartesianPoint(aSph.Location());
  occ::handle<IGESGeom_Point>      aLocation = GP.TransferPoint(mypoint);

  occ::handle<IGESGeom_Direction> anAxis = new IGESGeom_Direction;
  anAxis->Init(aSph.Position().Axis().Direction().XYZ());

  occ::handle<IGESGeom_Direction> aRefDir = new IGESGeom_Direction;
  aRefDir->Init(aSph.XAxis().Direction().XYZ());

  double aRadius = aSph.Radius() / GetUnit();

  SphSurf->Init(aLocation, aRadius, anAxis, aRefDir);
  res = SphSurf;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomSurface::TransferToroidalSurface(
  const occ::handle<Geom_ToroidalSurface>& start,
  const double,
  const double,
  const double,
  const double)
{

  occ::handle<IGESData_IGESEntity> res;
  TheLength = 1;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESSolid_ToroidalSurface> TorSurf = new IGESSolid_ToroidalSurface;
  GeomToIGES_GeomPoint                   GP(*this);

  gp_Torus aTor = start->Torus();

  occ::handle<Geom_CartesianPoint> mypoint   = new Geom_CartesianPoint(aTor.Location());
  occ::handle<IGESGeom_Point>      aLocation = GP.TransferPoint(mypoint);

  occ::handle<IGESGeom_Direction> anAxis = new IGESGeom_Direction;
  anAxis->Init(aTor.Axis().Direction().XYZ());

  occ::handle<IGESGeom_Direction> aRefDir = new IGESGeom_Direction;
  aRefDir->Init(aTor.XAxis().Direction().XYZ());

  double aMajor = aTor.MajorRadius() / GetUnit();
  double aMinor = aTor.MinorRadius() / GetUnit();

  TorSurf->Init(aLocation, anAxis, aMajor, aMinor, aRefDir);
  res = TorSurf;
  return res;
}

double GeomToIGES_GeomSurface::Length() const
{
  return TheLength;
}

bool GeomToIGES_GeomSurface::GetBRepMode() const
{
  return myBRepMode;
}

void GeomToIGES_GeomSurface::SetBRepMode(const bool flag)
{
  myBRepMode = flag;
}

bool GeomToIGES_GeomSurface::GetAnalyticMode() const
{
  return myAnalytic;
}

void GeomToIGES_GeomSurface::SetAnalyticMode(const bool flag)
{
  myAnalytic = flag;
}
