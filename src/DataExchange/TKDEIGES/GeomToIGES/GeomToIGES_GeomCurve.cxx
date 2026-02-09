

#include <BSplCLib.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_ApproxCurve.hpp>
#include <GeomToIGES_GeomCurve.hpp>
#include <GeomToIGES_GeomEntity.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESConvGeom_GeomBuilder.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Precision.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

GeomToIGES_GeomCurve::GeomToIGES_GeomCurve()

  = default;

GeomToIGES_GeomCurve::GeomToIGES_GeomCurve(const GeomToIGES_GeomEntity& GE)
    : GeomToIGES_GeomEntity(GE)
{
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Curve>& start,
  const double                   Udeb,
  const double                   Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_BoundedCurve)))
  {
    DeclareAndCast(Geom_BoundedCurve, Bounded, start);
    res = TransferCurve(Bounded, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Conic)))
  {
    DeclareAndCast(Geom_Conic, Conic, start);
    res = TransferCurve(Conic, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {
    DeclareAndCast(Geom_OffsetCurve, OffsetC, start);
    res = TransferCurve(OffsetC, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    DeclareAndCast(Geom_Line, Line, start);
    res = TransferCurve(Line, Udeb, Ufin);
  }
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_BoundedCurve>& start,
  const double                          Udeb,
  const double                          Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    DeclareAndCast(Geom_BSplineCurve, Bspline, start);
    res = TransferCurve(Bspline, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {
    DeclareAndCast(Geom_BezierCurve, Bezier, start);
    res = TransferCurve(Bezier, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    DeclareAndCast(Geom_TrimmedCurve, Trimmed, start);
    res = TransferCurve(Trimmed, Udeb, Ufin);
  }

  return res;
}

static gp_XYZ GetAnyNormal(gp_XYZ orig)
{
  gp_XYZ Norm;
  if (std::abs(orig.Z()) < Precision::Confusion())
    Norm.SetCoord(0, 0, 1);
  else
  {
    Norm.SetCoord(orig.Z(), 0, -orig.X());
    double nrm = Norm.Modulus();
    if (nrm < Precision::Confusion())
      Norm.SetCoord(0, 0, 1);
    else
      Norm = Norm / nrm;
  }
  return Norm;
}

static bool ArePolesPlanar(const NCollection_Array1<gp_Pnt>& Poles, gp_XYZ& Normal)
{
  if (Poles.Length() < 3)
  {
    Normal = GetAnyNormal(Poles(1).XYZ() - Poles(2).XYZ());
    return true;
  }

  Normal = Poles(Poles.Length()).XYZ() ^ Poles(1).XYZ();
  int i;
  for (i = 1; i < Poles.Length(); i++)
    Normal += Poles(i).XYZ() ^ Poles(i + 1).XYZ();

  constexpr double tol = Precision::Confusion();
  double           nrm = Normal.Modulus();
  if (nrm < tol)
  {
    Normal.SetCoord(0, 0, 1);
    return false;
  }
  Normal = Normal / nrm;

  double scl = Poles(1).XYZ() * Normal;
  for (i = 2; i <= Poles.Length(); i++)
    if (std::abs(Poles(i).XYZ() * Normal - scl) > tol)
      return false;
  return true;
}

static bool IsPlanar(const occ::handle<Geom_Curve>& curve, gp_XYZ& Normal)
{
  Normal.SetCoord(0, 0, 0);
  if (curve->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    DeclareAndCast(Geom_Line, Line, curve);
    Normal = GetAnyNormal(Line->Position().Direction().XYZ());
    return true;
  }
  if (curve->IsKind(STANDARD_TYPE(Geom_Conic)))
  {
    DeclareAndCast(Geom_Conic, Conic, curve);
    Normal = Conic->Axis().Direction().XYZ();
    return true;
  }
  if (curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    DeclareAndCast(Geom_TrimmedCurve, Trimmed, curve);
    return IsPlanar(Trimmed->BasisCurve(), Normal);
  }
  if (curve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {
    DeclareAndCast(Geom_OffsetCurve, OffsetC, curve);
    return IsPlanar(OffsetC->BasisCurve(), Normal);
  }
  if (curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    DeclareAndCast(Geom_BSplineCurve, BSpline, curve);
    NCollection_Array1<gp_Pnt> Poles(1, BSpline->NbPoles());
    BSpline->Poles(Poles);
    return ArePolesPlanar(Poles, Normal);
  }
  if (curve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {
    DeclareAndCast(Geom_BezierCurve, Bezier, curve);
    NCollection_Array1<gp_Pnt> Poles(1, Bezier->NbPoles());
    Bezier->Poles(Poles);
    return ArePolesPlanar(Poles, Normal);
  }
  return false;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_BSplineCurve>& start,
  const double                          Udeb,
  const double                          Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<Geom_BSplineCurve> mycurve;
  bool                           IPlan = false;
  gp_XYZ                         Norm  = gp_XYZ(0., 0., 1.);

  bool IPerio = start->IsPeriodic();

  if (IPerio)
  {
    mycurve = occ::down_cast<Geom_BSplineCurve>(start->Copy());
    mycurve->SetNotPeriodic();
  }
  else
  {
    mycurve = start;
  }

  double Umin = Udeb;
  double Umax = Ufin;
  if (Precision::IsNegativeInfinite(Udeb))
    Umin = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Ufin))
    Umax = Precision::Infinite();

  double First = mycurve->FirstParameter();
  double Last  = mycurve->LastParameter();

  if (Umin - First < Precision::PConfusion())
    Umin = First;
  if (Last - Umax < Precision::PConfusion())
    Umax = Last;
  if (Umin - First > Precision::PConfusion() || Last - Umax > Precision::PConfusion())
  {
    try
    {
      OCC_CATCH_SIGNALS
      occ::handle<Geom_BSplineCurve> bspl = occ::down_cast<Geom_BSplineCurve>(mycurve->Copy());
      if (!bspl.IsNull())
      {
        if (std::abs(Umax - Umin) > Precision::PConfusion())
          bspl->Segment(Umin, Umax);
        mycurve = bspl;
      }
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: GeomToIGES_GeomCurve: can't trim bspline" << std::endl;
      std::cout << "Warning: Exception in Segment(): ";
      anException.Print(std::cout);
#endif
      (void)anException;
    }
  }

  bool IClos = mycurve->IsClosed();

  bool IPolyn = !(mycurve->IsRational());

  int Deg     = mycurve->Degree();
  int Nbpoles = mycurve->NbPoles();

  int Index = Nbpoles - 1;

  int                        Knotindex;
  double                     rtampon;
  NCollection_Array1<double> K(1, Nbpoles + Deg + 1);
  mycurve->KnotSequence(K);
  int                                      itampon = -Deg;
  occ::handle<NCollection_HArray1<double>> Knots = new NCollection_HArray1<double>(-Deg, Index + 1);
  for (Knotindex = K.Lower(); Knotindex <= K.Upper(); Knotindex++)
  {
    rtampon = K.Value(Knotindex);
    Knots->SetValue(itampon, rtampon);
    itampon++;
  }

  NCollection_Array1<double> W(1, Nbpoles);
  mycurve->Weights(W);
  itampon                                          = 0;
  occ::handle<NCollection_HArray1<double>> Weights = new NCollection_HArray1<double>(0, Index);
  for (Knotindex = W.Lower(); Knotindex <= W.Upper(); Knotindex++)
  {
    rtampon = W.Value(Knotindex);
    Weights->SetValue(itampon, rtampon);
    itampon++;
  }

  NCollection_Array1<gp_Pnt> P(1, Nbpoles);
  mycurve->Poles(P);
  int Poleindex;
  itampon = 0;
  double                                   Xpt, Ypt, Zpt;
  occ::handle<NCollection_HArray1<gp_XYZ>> Poles = new NCollection_HArray1<gp_XYZ>(0, Index);
  for (Poleindex = P.Lower(); Poleindex <= P.Upper(); Poleindex++)
  {
    gp_Pnt ptampon = P.Value(Poleindex);
    ptampon.Coord(Xpt, Ypt, Zpt);
    gp_XYZ xyztampon = gp_XYZ(Xpt / GetUnit(), Ypt / GetUnit(), Zpt / GetUnit());
    Poles->SetValue(itampon, xyztampon);
    itampon++;
  }

  occ::handle<IGESGeom_BSplineCurve> BSplineC = new IGESGeom_BSplineCurve;

  IPlan = IsPlanar(start, Norm);
  if (Norm.Z() < 0)
    Norm.Reverse();
  BSplineC->Init(Index, Deg, IPlan, IClos, IPolyn, IPerio, Knots, Weights, Poles, Umin, Umax, Norm);

  res = BSplineC;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_BezierCurve>& start,
  const double                         Udeb,
  const double                         Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<Geom_TrimmedCurve> mycurve3d = new Geom_TrimmedCurve(start, Udeb, Ufin);
  occ::handle<Geom_BSplineCurve> Bspline =
    GeomConvert::CurveToBSplineCurve(mycurve3d, Convert_RationalC1);
  double First = Bspline->FirstParameter();
  double Last  = Bspline->LastParameter();
  res          = TransferCurve(Bspline, First, Last);
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_TrimmedCurve>& start,
  const double                          Udeb,
  const double                          Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<Geom_Curve> st = start->BasisCurve();
  if (st->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    DeclareAndCast(Geom_TrimmedCurve, Trimmed, st);
    occ::handle<Geom_Curve> st1 = Trimmed->BasisCurve();
    res                         = TransferCurve(st1, Udeb, Ufin);
  }

  res = TransferCurve(st, Udeb, Ufin);
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Conic>& start,
  const double                   Udeb,
  const double                   Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_Circle)))
  {
    DeclareAndCast(Geom_Circle, Circle, start);
    res = TransferCurve(Circle, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Ellipse)))
  {
    DeclareAndCast(Geom_Ellipse, Ellipse, start);
    res = TransferCurve(Ellipse, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Hyperbola)))
  {
    DeclareAndCast(Geom_Hyperbola, Hyperbola, start);
    res = TransferCurve(Hyperbola, Udeb, Ufin);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Parabola)))
  {
    DeclareAndCast(Geom_Parabola, Parabola, start);
    res = TransferCurve(Parabola, Udeb, Ufin);
  }

  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Circle>& start,
  const double                    Udeb,
  const double                    Ufin)
{

  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }
  occ::handle<IGESGeom_CircularArc> Circle = new IGESGeom_CircularArc();
  IGESConvGeom_GeomBuilder          Build;

  double U1 = Udeb;
  double U2 = Ufin;
  if (std::abs(Udeb) <= gp::Resolution())
    U1 = 0.0;

  double xloc, yloc, zloc;
  start->Circ().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = gp_Ax3(start->Circ().Position());

  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);

  double Xc, Yc, Zc;
  double Xs, Ys, Zs;
  double Xe, Ye, Ze;

  gp_Pnt pfirst, plast;
  start->D0(U1, pfirst);
  if (std::abs(Ufin - Udeb - 2 * M_PI) <= Precision::PConfusion())
    plast = pfirst;
  else
    start->D0(U2, plast);

  Build.EvalXYZ(((start->Circ()).Location()).XYZ(), Xc, Yc, Zc);
  Build.EvalXYZ(pfirst.XYZ(), Xs, Ys, Zs);
  Build.EvalXYZ(plast.XYZ(), Xe, Ye, Ze);
  Circle->Init(Zc / GetUnit(),
               gp_XY(Xc / GetUnit(), Yc / GetUnit()),
               gp_XY(Xs / GetUnit(), Ys / GetUnit()),
               gp_XY(Xe / GetUnit(), Ye / GetUnit()));

  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Circle->InitTransf(TMat);
  }

  res = Circle;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Ellipse>& start,
  const double                     Udeb,
  const double                     Ufin)
{

  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  if (std::abs(Ufin - Udeb - 2 * M_PI) <= Precision::PConfusion())
  {

    occ::handle<Geom_Ellipse> copystart = occ::down_cast<Geom_Ellipse>(start->Copy());
    gp_Ax2                    pos       = copystart->Position();
    copystart->SetPosition(pos.Rotated(pos.Axis(), gp_Ax3(pos).Direct() ? Udeb : 2 * M_PI - Udeb));
    occ::handle<Geom_BSplineCurve> Bspline;

    const occ::handle<Geom_Curve>& aCopy = copystart;
    GeomConvert_ApproxCurve        approx(aCopy, Precision::Approximation(), GeomAbs_C1, 100, 6);
    if (approx.HasResult())
      Bspline = approx.Curve();
    if (Bspline.IsNull())
      GeomConvert::CurveToBSplineCurve(copystart, Convert_QuasiAngular);
    NCollection_Array1<double> Knots(1, Bspline->NbKnots());
    Bspline->Knots(Knots);
    BSplCLib::Reparametrize(Udeb, Udeb + 2 * M_PI, Knots);
    Bspline->SetKnots(Knots);
    return TransferCurve(Bspline, Udeb, Ufin);
  }

  occ::handle<IGESGeom_ConicArc> Conic = new IGESGeom_ConicArc;
  IGESConvGeom_GeomBuilder       Build;
  double                         U1 = Udeb;
  double                         U2 = Ufin;
  if (std::abs(Udeb) <= gp::Resolution())
    U1 = 0.0;

  double xloc, yloc, zloc;
  start->Elips().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = gp_Ax3(start->Elips().Position());
  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);

  double Xs, Ys, Zs;
  double Xe, Ye, Ze;
  Build.EvalXYZ((start->Value(U1)).XYZ(), Xs, Ys, Zs);
  Build.EvalXYZ((start->Value(U2)).XYZ(), Xe, Ye, Ze);
  gp_Elips2d E2d = gp_Elips2d(gp_Ax22d(gp::Origin2d(), gp::DX2d(), gp::DY2d()),
                              (start->MajorRadius() / GetUnit()),
                              (start->MinorRadius() / GetUnit()));
  double     A, B, C, D, E, F;
  E2d.Coefficients(A, C, B, D, E, F);

  Conic->Init(A,
              2 * B,
              C,
              2 * D,
              2 * E,
              F,
              0.,
              gp_XY(Xs / GetUnit(), Ys / GetUnit()),
              gp_XY(Xe / GetUnit(), Ye / GetUnit()));

  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Conic->InitTransf(TMat);
  }
  res = Conic;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Hyperbola>& start,
  const double                       Udeb,
  const double                       Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_ConicArc> Conic = new IGESGeom_ConicArc;
  IGESConvGeom_GeomBuilder       Build;
  double                         U1 = Udeb;
  double                         U2 = Ufin;
  if (Precision::IsNegativeInfinite(Udeb))
    U1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Ufin))
    U2 = Precision::Infinite();

  double xloc, yloc, zloc;
  start->Hypr().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = gp_Ax3(start->Hypr().Position());
  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);

  double Xs, Ys, Zs;
  double Xe, Ye, Ze;
  Build.EvalXYZ((start->Value(U1)).XYZ(), Xs, Ys, Zs);
  Build.EvalXYZ((start->Value(U2)).XYZ(), Xe, Ye, Ze);
  gp_Hypr2d H2d = gp_Hypr2d(gp_Ax22d(gp::Origin2d(), gp::DX2d(), gp::DY2d()),
                            (start->MajorRadius() / GetUnit()),
                            (start->MinorRadius() / GetUnit()));
  double    A, B, C, D, E, F;
  H2d.Coefficients(A, C, B, D, E, F);

  Conic->Init(A,
              B,
              C,
              D,
              E,
              F,
              0.,
              gp_XY(Xs / GetUnit(), Ys / GetUnit()),
              gp_XY(Xe / GetUnit(), Ye / GetUnit()));

  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Conic->InitTransf(TMat);
  }
  res = Conic;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Parabola>& start,
  const double                      Udeb,
  const double                      Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_ConicArc> Conic = new IGESGeom_ConicArc;
  IGESConvGeom_GeomBuilder       Build;
  double                         U1 = Udeb;
  double                         U2 = Ufin;
  if (Precision::IsNegativeInfinite(Udeb))
    U1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Ufin))
    U2 = Precision::Infinite();

  double xloc, yloc, zloc;
  start->Parab().Location().Coord(xloc, yloc, zloc);
  gp_Pnt Loc;
  Loc.SetCoord(xloc, yloc, zloc);
  gp_Ax3 Pos = gp_Ax3(start->Parab().Position());
  Pos.SetLocation(Loc);
  Build.SetPosition(Pos);

  double Xs, Ys, Zs;
  double Xe, Ye, Ze;
  Build.EvalXYZ((start->Value(U1)).XYZ(), Xs, Ys, Zs);
  Build.EvalXYZ((start->Value(U2)).XYZ(), Xe, Ye, Ze);
  gp_Parab2d P2d =
    gp_Parab2d(gp_Ax22d(gp::Origin2d(), gp::DX2d(), gp::DY2d()), (start->Focal() * 2.));
  double A, B, C, D, E, F;
  P2d.Coefficients(A, C, B, D, E, F);

  Conic->Init(A,
              B,
              C,
              D,
              E,
              F,
              0.,
              gp_XY(Xs / GetUnit(), Ys / GetUnit()),
              gp_XY(Xe / GetUnit(), Ye / GetUnit()));

  if (!Build.IsIdentity())
  {
    occ::handle<IGESGeom_TransformationMatrix> TMat = new IGESGeom_TransformationMatrix;
    TMat                                            = Build.MakeTransformation(GetUnit());
    Conic->InitTransf(TMat);
  }
  res = Conic;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_Line>& start,
  const double                  Udeb,
  const double                  Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_Line> Line = new IGESGeom_Line;
  double                     U1   = Udeb;
  double                     U2   = Ufin;
  if (Precision::IsNegativeInfinite(Udeb))
    U1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Ufin))
    U2 = Precision::Infinite();

  double X1, Y1, Z1, X2, Y2, Z2;
  start->Value(U1).Coord(X1, Y1, Z1);
  start->Value(U2).Coord(X2, Y2, Z2);

  Line->Init((gp_XYZ(X1 / GetUnit(), Y1 / GetUnit(), Z1 / GetUnit())),
             (gp_XYZ(X2 / GetUnit(), Y2 / GetUnit(), Z2 / GetUnit())));
  res = Line;
  return res;
}

occ::handle<IGESData_IGESEntity> GeomToIGES_GeomCurve::TransferCurve(
  const occ::handle<Geom_OffsetCurve>& start,
  const double                         Udeb,
  const double                         Ufin)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
  {
    return res;
  }

  occ::handle<IGESGeom_OffsetCurve> OffsetC = new IGESGeom_OffsetCurve;
  double                            U1      = Udeb;
  double                            U2      = Ufin;
  if (Precision::IsNegativeInfinite(Udeb))
    U1 = -Precision::Infinite();
  if (Precision::IsPositiveInfinite(Ufin))
    U2 = Precision::Infinite();

  if (Interface_Static::IVal("write.iges.offset.mode") == 0)
  {
    res = TransferCurve(GeomConvert::CurveToBSplineCurve(start), U1, U2);
    return res;
  }

  occ::handle<Geom_Curve> Curve = start->BasisCurve();
  double                  Deb   = Curve->FirstParameter();
  double                  Fin   = Curve->LastParameter();

  gp_XYZ Normal;
  if (!IsPlanar(Curve, Normal))
  {

    try
    {
      OCC_CATCH_SIGNALS
      res = TransferCurve(GeomConvert::CurveToBSplineCurve(start), U1, U2);
      return res;
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "writing non-planar offset curve." << std::endl;
      std::cout << "Warning: GeomConvert::CurveToBSplineCurve raised an exception: ";
      anException.Print(std::cout);
#endif
      (void)anException;
    }
  }

  occ::handle<IGESData_IGESEntity> BaseCurve = TransferCurve(Curve, Deb, Fin);
  occ::handle<IGESData_IGESEntity> voident;

  OffsetC->Init(BaseCurve,
                1,
                voident,
                0,
                0,
                (start->Offset() / GetUnit()),
                0.,
                (start->Offset() / GetUnit()),
                0.,

                start->Direction().XYZ().Reversed(),
                U1,
                U2);

  res = OffsetC;
  return res;
}
