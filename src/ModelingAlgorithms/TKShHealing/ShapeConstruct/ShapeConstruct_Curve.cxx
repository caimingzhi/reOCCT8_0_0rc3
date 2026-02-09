

#include <Approx_Curve2d.hpp>
#include <Approx_Curve3d.hpp>
#include <ElCLib.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dConvert.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomConvert.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <ShapeConstruct_Curve.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>

bool ShapeConstruct_Curve::AdjustCurve(const occ::handle<Geom_Curve>& C3D,
                                       const gp_Pnt&                  P1,
                                       const gp_Pnt&                  P2,
                                       const bool                     take1,
                                       const bool                     take2) const
{
  if (!take1 && !take2)
    return true;

  if (C3D->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> BSPL = occ::down_cast<Geom_BSplineCurve>(C3D);
    if (take1)
      BSPL->SetPole(1, P1);
    if (take2)
      BSPL->SetPole(BSPL->NbPoles(), P2);
    return true;
  }

  if (C3D->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Line> L3D = occ::down_cast<Geom_Line>(C3D);

    gp_Vec avec(P1, P2);
    gp_Dir adir(avec);
    gp_Lin alin(P1, adir);
    double theParam = ElCLib::Parameter(alin, L3D->Lin().Location());
    alin.SetLocation(ElCLib::Value(theParam, alin));
    L3D->SetLin(alin);
    return true;
  }

  return false;
}

bool ShapeConstruct_Curve::AdjustCurveSegment(const occ::handle<Geom_Curve>& C3D,
                                              const gp_Pnt&                  P1,
                                              const gp_Pnt&                  P2,
                                              const double                   U1,
                                              const double                   U2) const
{
  if (C3D->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> BSPL = occ::down_cast<Geom_BSplineCurve>(C3D);

    if (U1 >= U2)
      return false;
    double UU1 = std::max(U1, BSPL->FirstParameter());
    double UU2 = std::min(U2, BSPL->LastParameter());
    BSPL->Segment(UU1, UU2);
    BSPL->SetPole(1, P1);
    BSPL->SetPole(BSPL->NbPoles(), P2);
    return true;
  }

  if (C3D->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Line> L3D = occ::down_cast<Geom_Line>(C3D);

    gp_Vec avec(P1, P2);
    gp_Dir adir(avec);
    gp_Lin alin(P1, adir);
    double theParam = ElCLib::Parameter(alin, L3D->Lin().Location());
    alin.SetLocation(ElCLib::Value(theParam, alin));
    L3D->SetLin(alin);
    return true;
  }

  return false;
}

bool ShapeConstruct_Curve::AdjustCurve2d(const occ::handle<Geom2d_Curve>& C2D,
                                         const gp_Pnt2d&                  P1,
                                         const gp_Pnt2d&                  P2,
                                         const bool                       take1,
                                         const bool                       take2) const
{
  if (!take1 && !take2)
    return true;

  if (C2D->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
  {
    occ::handle<Geom2d_BSplineCurve> BSPL = occ::down_cast<Geom2d_BSplineCurve>(C2D);
    if (take1)
      BSPL->SetPole(1, P1);
    if (take2)
      BSPL->SetPole(BSPL->NbPoles(), P2);
    return true;
  }

  if (C2D->IsKind(STANDARD_TYPE(Geom2d_Line)))
  {
    occ::handle<Geom2d_Line> L2D = occ::down_cast<Geom2d_Line>(C2D);

    gp_Vec2d avec(P1, P2);
    gp_Dir2d adir(avec);
    gp_Lin2d alin(P1, adir);
    double   theParam = ElCLib::Parameter(alin, L2D->Lin2d().Location());
    alin.SetLocation(ElCLib::Value(theParam, alin));
    L2D->SetLin2d(alin);
    return true;
  }

  return false;
}

occ::handle<Geom_BSplineCurve> ShapeConstruct_Curve::ConvertToBSpline(
  const occ::handle<Geom_Curve>& C,
  const double                   first,
  const double                   last,
  const double                   prec) const
{
  occ::handle<Geom_BSplineCurve> bspl;

  if (C->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    bspl = occ::down_cast<Geom_BSplineCurve>(C);
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_BezierCurve)) || C->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Curve> tc = new Geom_TrimmedCurve(C, first, last);
    try
    {
      OCC_CATCH_SIGNALS
      bspl = GeomConvert::CurveToBSplineCurve(tc);
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in GeomConvert: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  if (!bspl.IsNull())
  {

    double fbsp = bspl->FirstParameter(), lbsp = bspl->LastParameter();
    bool   segment = false;
    if (first > fbsp + Precision::PConfusion())
    {
      fbsp    = first;
      segment = true;
    }
    if (last < lbsp - Precision::PConfusion())
    {
      lbsp    = last;
      segment = true;
    }
    if (!segment)
      return bspl;
    try
    {
      OCC_CATCH_SIGNALS
      bspl = occ::down_cast<Geom_BSplineCurve>(bspl->Copy());
      bspl->Segment(fbsp, lbsp);
      return bspl;
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in Segment: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  occ::handle<Geom_Curve> newc = C;
  if (!bspl.IsNull())
  {
    newc = bspl;
    bspl.Nullify();
  }
  try
  {
    OCC_CATCH_SIGNALS
    Approx_Curve3d Conv(new GeomAdaptor_Curve(newc, first, last), prec, GeomAbs_C1, 9, 1000);
    if (Conv.IsDone() || Conv.HasResult())
      bspl = Conv.Curve();
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in Approx_Curve3d: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
  }
  return bspl;
}

occ::handle<Geom2d_BSplineCurve> ShapeConstruct_Curve::ConvertToBSpline(
  const occ::handle<Geom2d_Curve>& C,
  const double                     first,
  const double                     last,
  const double                     prec) const
{
  occ::handle<Geom2d_BSplineCurve> bspl;

  if (C->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
  {
    bspl = occ::down_cast<Geom2d_BSplineCurve>(C);
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_BezierCurve)) || C->IsKind(STANDARD_TYPE(Geom2d_Line)))
  {
    occ::handle<Geom2d_Curve> tc = new Geom2d_TrimmedCurve(C, first, last);
    try
    {
      OCC_CATCH_SIGNALS
      bspl = Geom2dConvert::CurveToBSplineCurve(tc);
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout
        << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in Geom2dConvert: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  if (!bspl.IsNull())
  {

    double fbsp = bspl->FirstParameter(), lbsp = bspl->LastParameter();
    bool   segment = false;
    if (first > fbsp + Precision::PConfusion())
    {
      fbsp    = first;
      segment = true;
    }
    if (last < lbsp - Precision::PConfusion())
    {
      lbsp    = last;
      segment = true;
    }
    if (!segment)
      return bspl;
    try
    {
      OCC_CATCH_SIGNALS
      bspl = occ::down_cast<Geom2d_BSplineCurve>(bspl->Copy());
      bspl->Segment(fbsp, lbsp);
      return bspl;
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in Segment: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  occ::handle<Geom2d_Curve> newc = C;
  if (!bspl.IsNull())
  {
    newc = bspl;
    bspl.Nullify();
  }
  try
  {
    OCC_CATCH_SIGNALS
    Approx_Curve2d Conv(new Geom2dAdaptor_Curve(newc, first, last),
                        first,
                        last,
                        prec,
                        prec,
                        GeomAbs_C1,
                        9,
                        1000);
    if (Conv.IsDone() || Conv.HasResult())
      bspl = Conv.Curve();
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: ShapeConstruct_Curve::ConvertToBSpline(): Exception in Approx_Curve3d: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
  }
  return bspl;
}

bool ShapeConstruct_Curve::FixKnots(occ::handle<NCollection_HArray1<double>>& knots)
{
  bool   Fixed   = false;
  int    nbKnots = knots->Length();
  double knotVal = knots->Value(1);
  for (int i = 2; i <= nbKnots; i++)
  {
    double knotNext = knots->Value(i);
    if (knotNext - knotVal <= Epsilon(knotVal))
    {
      knotNext = knotVal + 2. * Epsilon(knotVal);
      knots->SetValue(i, knotNext);
      Fixed = true;
    }
    knotVal = knotNext;
  }
  return Fixed;
}

bool ShapeConstruct_Curve::FixKnots(NCollection_Array1<double>& knots)
{
  bool   Fixed   = false;
  int    nbKnots = knots.Length();
  double knotVal = knots.Value(1);
  for (int i = 2; i <= nbKnots; i++)
  {
    double knotNext = knots.Value(i);
    if (knotNext - knotVal <= Epsilon(knotVal))
    {
      knotNext = knotVal + 2. * Epsilon(knotVal);
      knots.SetValue(i, knotNext);
      Fixed = true;
    }
    knotVal = knotNext;
  }
  return Fixed;
}
