

#include <ElCLib.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_Transformation.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Hypr.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf.hpp>
#include <gp_XYZ.hpp>
#include <IGESConvGeom.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <IGESGeom_CopiousData.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <IGESToBRep_BasicCurve.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeConstruct_Curve.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

static bool checkBSplineCurve(IGESToBRep_BasicCurve*                    theCurve,
                              const occ::handle<IGESGeom_BSplineCurve>& theBSplineCurve,
                              NCollection_Array1<double>&               CKnots,
                              const NCollection_Array1<double>&         CWeights)
{

  if (!theBSplineCurve->IsPolynomial())
  {
    double aMinValue = CWeights.Value(CWeights.Lower());
    double aMaxValue = CWeights.Value(CWeights.Lower());
    for (int i = CWeights.Lower() + 1; i <= CWeights.Upper(); i++)
    {
      if (CWeights.Value(i) < aMinValue)
        aMinValue = CWeights.Value(i);
      if (CWeights.Value(i) > aMaxValue)
        aMaxValue = CWeights.Value(i);
    }
    if (aMaxValue - aMinValue > 1000)
    {
      Message_Msg msg1374("IGES_1374");
      theCurve->SendWarning(theBSplineCurve, msg1374);
    }
  }

  bool aResult = true;

  for (int i = CKnots.Lower(); i < CKnots.Upper(); i++)
    if (CKnots.Value(i + 1) < CKnots.Value(i))
    {
      Message_Msg msg1373("IGES_1373");
      theCurve->SendFail(theBSplineCurve, msg1373);
      aResult = false;
    }

  if (aResult)
    ShapeConstruct_Curve::FixKnots(CKnots);

  return aResult;
}

IGESToBRep_BasicCurve::IGESToBRep_BasicCurve()

{
  SetModeTransfer(false);
}

IGESToBRep_BasicCurve::IGESToBRep_BasicCurve(const IGESToBRep_CurveAndSurface& CS)
    : IGESToBRep_CurveAndSurface(CS)
{
}

IGESToBRep_BasicCurve::IGESToBRep_BasicCurve(const double eps,
                                             const double epsCoeff,
                                             const double epsGeom,
                                             const bool   mode,
                                             const bool   modeapprox,
                                             const bool   optimized)
    : IGESToBRep_CurveAndSurface(eps, epsCoeff, epsGeom, mode, modeapprox, optimized)
{
}

occ::handle<Geom_Curve> IGESToBRep_BasicCurve::TransferBasicCurve(
  const occ::handle<IGESData_IGESEntity>& start)
{
  occ::handle<Geom_Curve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }
  try
  {
    OCC_CATCH_SIGNALS

    if (start->IsKind(STANDARD_TYPE(IGESGeom_BSplineCurve)))
    {
      DeclareAndCast(IGESGeom_BSplineCurve, st126, start);
      res = TransferBSplineCurve(st126);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_Line)))
    {
      DeclareAndCast(IGESGeom_Line, st110, start);
      res = TransferLine(st110);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
    {
      DeclareAndCast(IGESGeom_CircularArc, st100, start);
      res = TransferCircularArc(st100);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_ConicArc)))
    {
      DeclareAndCast(IGESGeom_ConicArc, st104, start);
      res = TransferConicArc(st104);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_CopiousData)))
    {
      DeclareAndCast(IGESGeom_CopiousData, st106, start);
      res = TransferCopiousData(st106);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_SplineCurve)))
    {
      DeclareAndCast(IGESGeom_SplineCurve, st112, start);
      res = TransferSplineCurve(st112);
    }
    else
    {

      return res;
    }
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "\n** Exception in IGESToBRep_BasicCurve::TransferBasicCurve : ";
    anException.Print(std::cout);
#endif
    (void)anException;
  }
  if (res.IsNull())
  {
  }
  else
    res->Scale(gp_Pnt(0, 0, 0), GetUnitFactor());
  return res;
}

occ::handle<Geom2d_Curve> IGESToBRep_BasicCurve::Transfer2dBasicCurve(
  const occ::handle<IGESData_IGESEntity>& start)
{
  occ::handle<Geom2d_Curve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }
  try
  {
    OCC_CATCH_SIGNALS

    if (start->IsKind(STANDARD_TYPE(IGESGeom_BSplineCurve)))
    {
      DeclareAndCast(IGESGeom_BSplineCurve, st126, start);
      res = Transfer2dBSplineCurve(st126);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_Line)))
    {
      DeclareAndCast(IGESGeom_Line, st110, start);
      res = Transfer2dLine(st110);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
    {
      DeclareAndCast(IGESGeom_CircularArc, st100, start);
      res = Transfer2dCircularArc(st100);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_ConicArc)))
    {
      DeclareAndCast(IGESGeom_ConicArc, st104, start);
      res = Transfer2dConicArc(st104);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_CopiousData)))
    {
      DeclareAndCast(IGESGeom_CopiousData, st106, start);
      res = Transfer2dCopiousData(st106);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_SplineCurve)))
    {
      DeclareAndCast(IGESGeom_SplineCurve, st112, start);
      res = Transfer2dSplineCurve(st112);
    }
    else
    {

      return res;
    }
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "\n** Exception in IGESToBRep_BasicCurve::Transfer2dBasicCurve : ";
    anException.Print(std::cout);
#endif
    (void)anException;
  }
  return res;
}

occ::handle<Geom_Curve> IGESToBRep_BasicCurve::TransferConicArc(
  const occ::handle<IGESGeom_ConicArc>& st)
{
  occ::handle<Geom_Curve> res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  if (!st->ComputedFormNumber())
  {
    Message_Msg msg1155("IGES_1155");
    SendFail(st, msg1155);

    return res;
  }

  double a, b, c, d, e, f, ZT;
  st->Equation(a, b, c, d, e, f);

  ZT = st->ZPlane();

  gp_Pnt center, startPoint, endPoint;
  gp_Dir mainAxis, normAxis;
  double minorRadius, majorRadius;

  if (!GetModeTransfer() && st->HasTransf())
  {

    st->TransformedDefinition(center, mainAxis, minorRadius, majorRadius);
    normAxis = st->TransformedAxis();

    startPoint = st->TransformedStartPoint();
    endPoint   = st->TransformedEndPoint();
  }
  else
  {
    st->Definition(center, mainAxis, minorRadius, majorRadius);
    normAxis = st->Axis();

    startPoint.SetCoord(st->StartPoint().X(), st->StartPoint().Y(), ZT);
    endPoint.SetCoord(st->EndPoint().X(), st->EndPoint().Y(), ZT);
  }
  gp_Ax2 frame(center, normAxis, mainAxis);
  double t1 = 0.0, t2 = 0.0;
  if (st->IsFromEllipse())
  {

    constexpr double eps2 = Precision::PConfusion() * Precision::PConfusion();
    if ((std::abs(a - c) <= eps2) && (std::abs(b) < eps2))
    {

      res = new Geom_Circle(frame, minorRadius);

      if (!st->IsClosed())
      {

        gp_Circ circ(frame, minorRadius);

        t1 = ElCLib::Parameter(circ, startPoint);
        t2 = ElCLib::Parameter(circ, endPoint);
        if (t1 > t2 && (t1 - t2) > Precision::Confusion())
          t2 += 2. * M_PI;
        if (std::abs(t1 - t2) <= Precision::Confusion())
        {
          Message_Msg msg1160("IGES_1160");
          SendWarning(st, msg1160);
        }
        else
          res = new Geom_TrimmedCurve(res, t1, t2);
      }
      return res;
    }
    else
    {
    }
  }
  else if (st->IsFromParabola())
  {

    double focal = minorRadius;

    focal = focal / 2.;
    gp_Parab parab(frame, focal);

    res = new Geom_Parabola(frame, focal);

    t1 = ElCLib::Parameter(parab, startPoint);
    t2 = ElCLib::Parameter(parab, endPoint);
    if (std::abs(t1 - t2) <= Precision::Confusion())
    {
      Message_Msg msg1160("IGES_1160");
      SendWarning(st, msg1160);
    }
    else

      res = new Geom_TrimmedCurve(res, t1, t2);

    return res;
  }

  if (st->IsFromEllipse())
  {
    res = new Geom_Ellipse(frame, majorRadius, minorRadius);

    if (!st->IsClosed())
    {
      gp_Elips elips(frame, majorRadius, minorRadius);

      t1 = ElCLib::Parameter(elips, startPoint);
      t2 = ElCLib::Parameter(elips, endPoint);
      if (t2 < t1 && (t1 - t2) > Precision::Confusion())
        t2 += 2. * M_PI;
      if (std::abs(t1 - t2) <= Precision::Confusion())
      {
        Message_Msg msg1160("IGES_1160");
        SendWarning(st, msg1160);
      }
      else
        res = new Geom_TrimmedCurve(res, t1, t2);
    }
  }
  else
  {

    gp_Hypr hpr(frame, majorRadius, minorRadius);

    t1 = ElCLib::Parameter(hpr, startPoint);
    t2 = ElCLib::Parameter(hpr, endPoint);

    res = new Geom_Hyperbola(frame, majorRadius, minorRadius);

    if (std::abs(t1 - t2) <= Precision::PConfusion())
    {
      Message_Msg msg1160("IGES_1160");
      SendWarning(st, msg1160);
    }
    else if (t1 > t2)
      res = new Geom_TrimmedCurve(res, t2, t1);
    else
      res = new Geom_TrimmedCurve(res, t1, t2);
  }

  return res;
}

occ::handle<Geom2d_Curve> IGESToBRep_BasicCurve::Transfer2dConicArc(
  const occ::handle<IGESGeom_ConicArc>& st)
{
  occ::handle<Geom2d_Curve> res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  if (!st->ComputedFormNumber())
  {
    Message_Msg msg1155("IGES_1155");
    SendFail(st, msg1155);
    return res;
  }

  double a, b, c, d, e, f;

  st->Equation(a, b, c, d, e, f);

  gp_Pnt   center3d;
  gp_Dir   mainAxis3d;
  gp_Pnt2d startPoint, endPoint;
  double   minorRadius, majorRadius;

  SetEpsilon(1.E-03);
  if (!st->TransformedAxis().IsParallel(st->Axis(), GetEpsilon()))
  {
    SetModeTransfer(true);

    SendWarning(st, "The Trsf is not compatible with a transfer2d, it will not applied.");
  }

  if (!GetModeTransfer() && st->HasTransf())
  {

    st->TransformedDefinition(center3d, mainAxis3d, minorRadius, majorRadius);
    startPoint.SetCoord(st->TransformedStartPoint().X(), st->TransformedStartPoint().Y());
    endPoint.SetCoord(st->TransformedEndPoint().X(), st->TransformedEndPoint().Y());
  }
  else
  {
    st->Definition(center3d, mainAxis3d, minorRadius, majorRadius);
    startPoint = st->StartPoint();
    endPoint   = st->EndPoint();
  }

  gp_Pnt2d center(center3d.X(), center3d.Y());
  gp_Dir2d mainAxis(mainAxis3d.X(), mainAxis3d.Y());
  gp_Ax2d  frame(center, mainAxis);
  double   t1 = 0.0, t2 = 0.0;
  if (st->IsFromEllipse())
  {

    constexpr double eps2 = Precision::PConfusion() * Precision::PConfusion();
    if ((std::abs(a - c) <= eps2) && (std::abs(b) < eps2))
    {

      res = new Geom2d_Circle(frame, minorRadius);

      if (st->TransformedAxis().IsOpposite(st->Axis(), GetEpsilon()))
        res->Reverse();

      if (!st->IsClosed())
      {

        gp_Circ2d circ = occ::down_cast<Geom2d_Circle>(res)->Circ2d();

        t1 = ElCLib::Parameter(circ, startPoint);
        t2 = ElCLib::Parameter(circ, endPoint);

        if (t2 < t1 && (t1 - t2) > Precision::PConfusion())
          t2 += 2. * M_PI;
        if (std::abs(t1 - t2) <= Precision::PConfusion())
        {
          Message_Msg msg1160("IGES_1160");
          SendWarning(st, msg1160);
        }
        else
          res = new Geom2d_TrimmedCurve(res, t1, t2);
      }
      return res;
    }
    else
    {
    }
  }
  else if (st->IsFromParabola())
  {

    double focal = minorRadius;

    focal = focal / 2.;
    res   = new Geom2d_Parabola(frame, focal);

    if (st->TransformedAxis().IsOpposite(st->Axis(), GetEpsilon()))
      res->Reverse();

    gp_Parab2d parab = occ::down_cast<Geom2d_Parabola>(res)->Parab2d();

    t1 = ElCLib::Parameter(parab, startPoint);
    t2 = ElCLib::Parameter(parab, endPoint);
    if (std::abs(t1 - t2) <= Precision::PConfusion())
    {
      Message_Msg msg1160("IGES_1160");
      SendWarning(st, msg1160);
    }
    else if (t1 > t2)
      res = new Geom2d_TrimmedCurve(res, t2, t1);
    else
      res = new Geom2d_TrimmedCurve(res, t1, t2);
    return res;
  }

  if (st->IsFromEllipse())
  {

    res = new Geom2d_Ellipse(frame, majorRadius, minorRadius);

    if (st->TransformedAxis().IsOpposite(st->Axis(), GetEpsilon()))
      res->Reverse();

    if (!st->IsClosed())
    {

      gp_Elips2d elips = occ::down_cast<Geom2d_Ellipse>(res)->Elips2d();

      t1 = ElCLib::Parameter(elips, startPoint);
      t2 = ElCLib::Parameter(elips, endPoint);
      if (t2 < t1 && (t1 - t2) > Precision::PConfusion())
        t2 += 2. * M_PI;
      if (std::abs(t1 - t2) <= Precision::PConfusion())
      {
        Message_Msg msg1160("IGES_1160");
        SendWarning(st, msg1160);
      }
      else
        res = new Geom2d_TrimmedCurve(res, t1, t2);
    }
  }
  else
  {

    res = new Geom2d_Hyperbola(frame, majorRadius, minorRadius);

    if (st->TransformedAxis().IsOpposite(st->Axis(), GetEpsilon()))
      res->Reverse();

    gp_Hypr2d hpr = occ::down_cast<Geom2d_Hyperbola>(res)->Hypr2d();

    t1 = ElCLib::Parameter(hpr, startPoint);
    t2 = ElCLib::Parameter(hpr, endPoint);

    if (std::abs(t1 - t2) <= Precision::PConfusion())
    {
      Message_Msg msg1160("IGES_1160");
      SendWarning(st, msg1160);
    }
    else if (t1 > t2)
      res = new Geom2d_TrimmedCurve(res, t2, t1);
    else
      res = new Geom2d_TrimmedCurve(res, t1, t2);
  }

  return res;
}

occ::handle<Geom_Curve> IGESToBRep_BasicCurve::TransferCircularArc(
  const occ::handle<IGESGeom_CircularArc>& st)
{
  occ::handle<Geom_Curve> res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  gp_Dir tNormAxis, tMainAxis;
  gp_Ax2 frame;
  gp_Pnt startPoint, endPoint;

  if (!GetModeTransfer() && st->HasTransf())
  {

    tNormAxis = st->TransformedAxis();

    gp_GTrsf loc = st->Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    gp_XYZ mainAxis(1., 0., 0.);
    loc.Transforms(mainAxis);
    tMainAxis = gp_Dir(mainAxis);

    startPoint = st->TransformedStartPoint();
    endPoint   = st->TransformedEndPoint();

    frame = gp_Ax2(st->TransformedCenter(), tNormAxis, tMainAxis);
  }
  else
  {
    tNormAxis = st->Axis();
    tMainAxis.SetCoord(1., 0., 0.);

    double ZT = st->ZPlane();
    startPoint.SetCoord(st->StartPoint().X(), st->StartPoint().Y(), ZT);
    endPoint.SetCoord(st->EndPoint().X(), st->EndPoint().Y(), ZT);
    gp_Pnt centerPoint(st->Center().X(), st->Center().Y(), ZT);

    frame = gp_Ax2(centerPoint, tNormAxis, tMainAxis);
  }

  res = new Geom_Circle(frame, st->Radius());

  gp_Circ circ(frame, st->Radius());

  double t1 = 0.0, t2 = 0.0;

  t1 = ElCLib::Parameter(circ, startPoint);
  t2 = ElCLib::Parameter(circ, endPoint);

  if (st->IsClosed() && t1 >= GetEpsGeom())
    t2 = t1 + 2. * M_PI;
  if (!st->IsClosed() && fabs(t1 - t2) <= Precision::PConfusion())
  {

    t2 = t1 + startPoint.Distance(endPoint) / st->Radius();
  }
  if (!st->IsClosed() || t1 >= GetEpsGeom())
  {
    if (t2 < t1)
      t2 += 2. * M_PI;
    res = new Geom_TrimmedCurve(res, t1, t2);
  }

  return res;
}

occ::handle<Geom2d_Curve> IGESToBRep_BasicCurve::Transfer2dCircularArc(
  const occ::handle<IGESGeom_CircularArc>& st)
{
  occ::handle<Geom2d_Curve> res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  gp_XYZ center(st->Center().X(), st->Center().Y(), 0.);
  gp_XYZ mainAxis(1., 0., 0.);

  SetEpsilon(1.E-03);
  if (!st->TransformedAxis().IsParallel(st->Axis(), GetEpsilon()))
  {
    SetModeTransfer(true);
    Message_Msg msg1165("IGES_1165");

    SendWarning(st, msg1165);
  }

  if (!GetModeTransfer() && st->HasTransf())
  {
    gp_GTrsf loc = st->Location();
    loc.Transforms(center);
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(mainAxis);
  }
  gp_Pnt2d tCenter(center.X(), center.Y());
  gp_Dir2d tMainAxis(mainAxis.X(), mainAxis.Y());
  gp_Ax2d  frame(tCenter, tMainAxis);

  res = new Geom2d_Circle(frame, st->Radius());

  gp_Pnt2d startPoint, endPoint;
  if (!GetModeTransfer() && st->HasTransf())
  {
    startPoint.SetCoord(st->TransformedStartPoint().X(), st->TransformedStartPoint().Y());
    endPoint.SetCoord(st->TransformedEndPoint().X(), st->TransformedEndPoint().Y());

    if (st->TransformedAxis().IsOpposite(st->Axis(), GetEpsilon()))
      res->Reverse();
  }
  else
  {
    startPoint = st->StartPoint();
    endPoint   = st->EndPoint();
  }

  gp_Circ2d circ = occ::down_cast<Geom2d_Circle>(res)->Circ2d();

  double t1 = 0.0, t2 = 0.0;

  t1 = ElCLib::Parameter(circ, startPoint);
  t2 = ElCLib::Parameter(circ, endPoint);

  if (st->IsClosed() && t1 >= GetEpsGeom())
    t2 = t1 + 2. * M_PI;
  if (!st->IsClosed() && fabs(t1 - t2) <= Precision::PConfusion())
  {

    t2 = t1 + startPoint.Distance(endPoint) / st->Radius();
  }
  if (!st->IsClosed() || t1 >= GetEpsGeom())
  {
    if (t2 < t1)
      t2 += 2. * M_PI;
    res = new Geom2d_TrimmedCurve(res, t1, t2);
  }
  return res;
}

occ::handle<Geom_BSplineCurve> IGESToBRep_BasicCurve::TransferSplineCurve(
  const occ::handle<IGESGeom_SplineCurve>& st)
{
  occ::handle<Geom_BSplineCurve> resconv;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return resconv;
  }

  double epscoef = GetEpsCoeff();
  double epsgeom = GetEpsGeom();

  int result = IGESConvGeom::SplineCurveFromIGES(st, epscoef, epsgeom, resconv);

  switch (result)
  {
    case 5:
    {
      Message_Msg msg246("XSTEP_246");
      SendFail(st, msg246);

      return resconv;
    }
    case 4:
    {
      Message_Msg msg1170("IGES_1170");
      SendFail(st, msg1170);

      return resconv;
    }
    case 3:
    {
      Message_Msg msg1175("IGES_1175");
      SendFail(st, msg1175);

      return resconv;
    }
    case 2:
    {
      Message_Msg msg1180("IGES_1180");
      SendFail(st, msg1180);

      return resconv;
    }
    default:
      break;
  }

  IGESConvGeom::IncreaseCurveContinuity(resconv,
                                        std::min(Precision::Confusion(), epsgeom),
                                        GetContinuity());
  return resconv;
}

occ::handle<Geom2d_BSplineCurve> IGESToBRep_BasicCurve::Transfer2dSplineCurve(
  const occ::handle<IGESGeom_SplineCurve>& st)
{
  occ::handle<Geom2d_BSplineCurve> res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  double epsGeom = GetEpsGeom();
  SetEpsGeom(Precision::PConfusion());
  occ::handle<Geom_BSplineCurve> res3d = TransferSplineCurve(st);
  SetEpsGeom(epsGeom);
  if (res3d.IsNull())
    return res;

  int nbPoles = res3d->NbPoles();
  int nbKnots = res3d->NbKnots();

  NCollection_Array1<gp_Pnt2d> bspoles2d(1, nbPoles);
  NCollection_Array1<double>   knots(1, nbKnots);
  NCollection_Array1<int>      multi(1, nbKnots);

  res3d->Knots(knots);
  res3d->Multiplicities(multi);

  for (int i = bspoles2d.Lower(); i <= bspoles2d.Upper(); i++)
    bspoles2d.SetValue(i, gp_Pnt2d(res3d->Pole(i).X(), res3d->Pole(i).Y()));

  res = new Geom2d_BSplineCurve(bspoles2d, knots, multi, res3d->Degree());
  return res;
}

occ::handle<Geom_Curve> IGESToBRep_BasicCurve::TransferBSplineCurve(
  const occ::handle<IGESGeom_BSplineCurve>& start)

{
  occ::handle<Geom_BSplineCurve> BSplineRes;
  occ::handle<Geom_Curve>        res;

  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  int Degree = start->Degree();

  if (Degree <= 0 || Degree > Geom_BSplineCurve::MaxDegree())
  {
    Message_Msg msg1190("IGES_1190");
    SendFail(start, msg1190);

    return res;
  }

  int NbPoles    = start->NbPoles();
  int newNbPoles = NbPoles;

  if (NbPoles < 2)
  {
    Message_Msg msg1195("IGES_1195");
    SendFail(start, msg1195);

    return res;
  }

  NCollection_Array1<gp_Pnt> Pole(1, NbPoles);
  int                        PoleIndex = Pole.Lower();
  int                        i;

  if (!GetModeTransfer() && start->HasTransf())
    for (i = 0; i <= start->UpperIndex(); i++)
      Pole.SetValue(PoleIndex++, start->TransformedPole(i));
  else
    for (i = 0; i <= start->UpperIndex(); i++)
      Pole.SetValue(PoleIndex++, start->Pole(i));

  int                        NbKnots = start->NbKnots();
  NCollection_Array1<double> TempKnot(1, NbKnots);
  NCollection_Array1<int>    TempMult(1, NbKnots);
  TempMult.Init(1);
  int KnotIndex = TempKnot.Lower();

  TempKnot.SetValue(KnotIndex, start->Knot(-Degree));

  for (i = 1 - Degree; i < NbKnots - Degree; i++)
  {

    double Knot1 = start->Knot(i);
    double Knot2 = start->Knot(i - 1);

    if (std::abs(Knot1 - Knot2) <= Epsilon(Knot1))
      TempMult.SetValue(KnotIndex, TempMult.Value(KnotIndex) + 1);
    else
      TempKnot.SetValue(++KnotIndex, Knot1);
  }

  NCollection_Array1<double> Knot(1, KnotIndex);
  NCollection_Array1<int>    Mult(1, KnotIndex);

  int SumOfMult = 0;

  NCollection_Sequence<int> SeqIndex;
  int                       DelIndex;
  int                       OldSumOfMult = 0;
  for (i = 1; i <= KnotIndex; i++)
  {
    int aMult   = TempMult.Value(i);
    int maxMult = (i == 1 || i == KnotIndex ? Degree + 1 : Degree);
    if (aMult > maxMult)
    {
      Message_Msg msg1200("IGES_1200");
      const char* vide("");
      msg1200.Arg(vide);
      msg1200.Arg(vide);
      msg1200.Arg(vide);
      SendWarning(start, msg1200);
      for (DelIndex = OldSumOfMult + 1; aMult > maxMult; DelIndex++, aMult--)
      {
        newNbPoles--;
        SeqIndex.Append(DelIndex);
      }
    }
    OldSumOfMult += TempMult.Value(i);
    Knot.SetValue(i, TempKnot.Value(i));
    Mult.SetValue(i, aMult);
    SumOfMult += aMult;
  }

  NCollection_Array1<gp_Pnt> Poles(1, newNbPoles);
  NCollection_Sequence<int>  PoleInd;

  if (newNbPoles < NbPoles)
  {
    for (i = 1; i <= NbPoles; i++)
      PoleInd.Append(i);
    int Offset = 0;
    for (int itab = 1; itab <= SeqIndex.Length(); itab++)
    {
      DelIndex = SeqIndex.Value(itab) - Offset;
      PoleInd.Remove(DelIndex);
      Offset++;
    }
    int nbseq = PoleInd.Length();
    if (nbseq == newNbPoles)
    {
      int indj = 1;
      for (i = 1; i <= newNbPoles; i++)
      {
        Poles.SetValue(i, Pole.Value(PoleInd.Value(indj++)));
      }
    }
  }

  else
  {
    for (i = 1; i <= newNbPoles; i++)
    {
      Poles.SetValue(i, Pole.Value(i));
    }
  }

  if (!(SumOfMult == newNbPoles + Degree + 1))
  {
    Message_Msg msg1210("IGES_1210");
    const char* vide("");
    msg1210.Arg(vide);
    msg1210.Arg(vide);
    SendWarning(start, msg1210);
  }

  NCollection_Array1<double> Weight(1, newNbPoles);

  if (start->IsPolynomial())
  {
  }
  else
  {
    NCollection_Array1<double> PoleWeight(1, NbPoles);
    bool                       polynomial      = true;
    double                     WeightReference = start->Weight(0);
    int                        WeightIndex     = PoleWeight.Lower();

    for (i = 0; i <= start->UpperIndex(); i++)
    {
      polynomial =
        std::abs(start->Weight(i) - WeightReference) <= Epsilon(WeightReference) && polynomial;

      double weight = start->Weight(i);
      if (weight < Precision::PConfusion())
      {
        Message_Msg msg1215("IGES_1215");
        SendFail(start, msg1215);

        return res;
      }
      PoleWeight.SetValue(WeightIndex++, weight);
    }
    if (polynomial)
    {
      Message_Msg msg1220("IGES_1220");
      msg1220.Arg("curve");
      SendWarning(start, msg1220);
    }

    if (newNbPoles < NbPoles)
    {
      int indj = 1;
      for (i = 1; i <= newNbPoles; i++)
      {
        Weight.SetValue(i, PoleWeight.Value(PoleInd.Value(indj++)));
      }
    }
    else
    {
      for (i = 1; i <= newNbPoles; i++)
      {
        Weight.SetValue(i, PoleWeight.Value(i));
      }
    }
  }

  if (Poles.Size() < 2 || !checkBSplineCurve(this, start, Knot, Weight))
  {
    return BSplineRes;
  }

  {
    try
    {
      OCC_CATCH_SIGNALS
      if (start->IsPolynomial())
        BSplineRes = new Geom_BSplineCurve(Poles, Knot, Mult, Degree);
      else
        BSplineRes = new Geom_BSplineCurve(Poles, Weight, Knot, Mult, Degree);
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "\n** Exception in IGESToBRep_BasicCurve::TransferBSplineCurve during creation "
                   "of Geom_BSplineCurve : ";
      anException.Print(std::cout);
#endif
      (void)anException;
      return BSplineRes;
    }
  }

  double First = BSplineRes->FirstParameter();
  double Last  = BSplineRes->LastParameter();
  double Udeb  = start->UMin();
  double Ufin  = start->UMax();

  occ::handle<Geom_BSplineCurve> BSplineRes2 = BSplineRes;
  if (((Udeb - First) > -Precision::PConfusion() && (Last - Ufin) > -Precision::PConfusion())
      && Udeb <= Ufin)
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (std::abs(Ufin - Udeb) > Precision::PConfusion())
        BSplineRes->Segment(Udeb, Ufin);
      res = BSplineRes;
    }
    catch (Standard_Failure const&)
    {
      occ::handle<Geom_TrimmedCurve> gtc = new Geom_TrimmedCurve(BSplineRes2, Udeb, Ufin);
      res                                = gtc;
    }
  }
  else
    res = BSplineRes;

  return res;
}

occ::handle<Geom2d_Curve> IGESToBRep_BasicCurve::Transfer2dBSplineCurve(
  const occ::handle<IGESGeom_BSplineCurve>& start)
{
  occ::handle<Geom2d_Curve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  occ::handle<Geom2d_BSplineCurve> BSplineC;
  occ::handle<Geom_BSplineCurve>   Bspline;
  bool                             IsTrimmed = false;
  double                           Deb = 0., Fin = 0.;

  occ::handle<Geom_Curve> res3d = TransferBSplineCurve(start);

  if (res3d.IsNull())
  {
    return res;
  }

  if (res3d->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    DeclareAndCast(Geom_TrimmedCurve, TrimC, res3d);
    occ::handle<Geom_Curve> BasicCurve = TrimC->BasisCurve();
    Deb                                = TrimC->FirstParameter();
    Fin                                = TrimC->LastParameter();
    IsTrimmed                          = true;
    if (BasicCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
    {
      DeclareAndCast(Geom_BSplineCurve, BSpline, BasicCurve);
      Bspline = BSpline;
    }
    else
    {
      return res;
    }
  }
  else if (res3d->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    DeclareAndCast(Geom_BSplineCurve, BSpline, res3d);
    Bspline = BSpline;
  }

  int                          NbPoles = Bspline->NbPoles();
  NCollection_Array1<gp_Pnt2d> Pole(1, NbPoles);

  for (int i = 1; i <= NbPoles; i++)
  {
    gp_Pnt2d aPole2d(Bspline->Pole(i).X(), Bspline->Pole(i).Y());
    Pole.SetValue(i, aPole2d);
  }

  int NbKnots = Bspline->NbKnots();

  NCollection_Array1<double> Knot(1, NbKnots);
  Bspline->Knots(Knot);

  NCollection_Array1<int> Mult(1, NbKnots);
  Bspline->Multiplicities(Mult);

  int Degree = Bspline->Degree();

  if (Bspline->IsRational())
  {
    NCollection_Array1<double> Weight(1, NbPoles);
    Bspline->Weights(Weight);
    BSplineC = new Geom2d_BSplineCurve(Pole, Weight, Knot, Mult, Degree);
  }
  else
    BSplineC = new Geom2d_BSplineCurve(Pole, Knot, Mult, Degree);

  res = BSplineC;

  if (IsTrimmed)
  {
    occ::handle<Geom2d_TrimmedCurve> TC = new Geom2d_TrimmedCurve(BSplineC, Deb, Fin, true);
    res                                 = TC;
  }

  return res;
}

occ::handle<Geom_Curve> IGESToBRep_BasicCurve::TransferLine(const occ::handle<IGESGeom_Line>& start)
{
  occ::handle<Geom_Curve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  gp_Pnt Ps, Pe;

  if (!GetModeTransfer() && start->HasTransf())
  {
    Ps = start->TransformedStartPoint();
    Pe = start->TransformedEndPoint();
  }
  else
  {
    Ps = start->StartPoint();
    Pe = start->EndPoint();
  }

  if (!Ps.IsEqual(Pe, Precision::Confusion()))
  {
    gp_Lin                 line(Ps, gp_Dir(gp_Vec(Ps, Pe)));
    double                 t1    = ElCLib::Parameter(line, Ps);
    double                 t2    = ElCLib::Parameter(line, Pe);
    occ::handle<Geom_Line> Gline = new Geom_Line(line);
    if (Precision::IsNegativeInfinite(t1))
      t1 = -Precision::Infinite();
    if (Precision::IsPositiveInfinite(t2))
      t2 = Precision::Infinite();
    res = new Geom_TrimmedCurve(Gline, t1, t2);
  }
  else
  {
    Message_Msg msg1225("IGES_1225");
    SendFail(start, msg1225);
  }

  return res;
}

occ::handle<Geom2d_Curve> IGESToBRep_BasicCurve::Transfer2dLine(
  const occ::handle<IGESGeom_Line>& start)
{
  occ::handle<Geom2d_Curve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  gp_Pnt2d beg, end;

  if (!GetModeTransfer() && start->HasTransf())
  {
    beg.SetCoord(start->TransformedStartPoint().X(), start->TransformedStartPoint().Y());
    end.SetCoord(start->TransformedEndPoint().X(), start->TransformedEndPoint().Y());
  }
  else
  {
    beg.SetCoord(start->StartPoint().X(), start->StartPoint().Y());
    end.SetCoord(start->EndPoint().X(), start->EndPoint().Y());
  }

  if (!beg.IsEqual(end, Precision::PConfusion()))
  {
    gp_Lin2d                 line2d(beg, gp_Dir2d(gp_Vec2d(beg, end)));
    double                   t1      = ElCLib::Parameter(line2d, beg);
    double                   t2      = ElCLib::Parameter(line2d, end);
    occ::handle<Geom2d_Line> Gline2d = new Geom2d_Line(line2d);
    if (Precision::IsNegativeInfinite(t1))
      t1 = -Precision::Infinite();
    if (Precision::IsPositiveInfinite(t2))
      t2 = Precision::Infinite();
    res = new Geom2d_TrimmedCurve(Gline2d, t1, t2);
  }

  else
  {
    Message_Msg msg1225("IGES_1225");
    SendFail(start, msg1225);
  }
  return res;
}

occ::handle<Geom_Transformation> IGESToBRep_BasicCurve::TransferTransformation(
  const occ::handle<IGESGeom_TransformationMatrix>& start)

{
  occ::handle<Geom_Transformation> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }
  gp_Trsf resultat;
  SetEpsilon(1.E-05);
  if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(), start->Value(), resultat))
    res = new Geom_Transformation(resultat);
  else
  {
    Message_Msg msg1036("IGES_1036");
    SendFail(start, msg1036);
  }
  return res;
}

occ::handle<Geom_BSplineCurve> IGESToBRep_BasicCurve::TransferCopiousData(
  const occ::handle<IGESGeom_CopiousData>& start)

{
  occ::handle<Geom_BSplineCurve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  int FormNb = start->FormNumber();
  if (FormNb != 11 && FormNb != 12 && FormNb != 63)
  {
    Message_Msg msg1240("IGES_1240");
    SendWarning(start, msg1240);
  }

  int NbPoints = start->NbPoints();
  if (NbPoints < 2)
  {
    Message_Msg msg1195("IGES_1195");
    SendFail(start, msg1195);
    return res;
  }

  NCollection_Array1<gp_Pnt> TempPole(1, NbPoints);
  int                        TempIndex = TempPole.Lower();

  if (!GetModeTransfer() && start->HasTransf())
  {
    TempPole.SetValue(TempIndex, start->TransformedPoint(1));
  }
  else
  {
    TempPole.SetValue(TempIndex, start->Point(1));
  }

  TempIndex++;
  int i;
  for (i = 2; i <= NbPoints; i++)
  {
    gp_Pnt aPole;
    if (!GetModeTransfer() && start->HasTransf())
      aPole = start->TransformedPoint(i);
    else
      aPole = start->Point(i);

    if (!aPole.IsEqual(TempPole(TempIndex - 1), gp::Resolution()))
      TempPole.SetValue(TempIndex++, aPole);
  }

  NbPoints = TempIndex - TempPole.Lower();

  if (NbPoints == 1)
  {
    Message_Msg msg1235("IGES_1235");
    SendFail(start, msg1235);

    return res;
  }
  NCollection_Array1<gp_Pnt> Pole(1, NbPoints);

  TempIndex = TempPole.Lower();
  for (i = Pole.Lower(); i <= Pole.Upper(); i++)
    Pole.SetValue(i, TempPole.Value(TempIndex++));

  NCollection_Array1<double> Knot(1, NbPoints);

  Knot.SetValue(Knot.Lower(), 0.0);

  for (i = Knot.Lower() + 1; i <= Knot.Upper(); i++)
  {
    gp_Pnt Pole1    = Pole.Value(i);
    gp_Pnt Pole2    = Pole.Value(i - 1);
    double KnotDist = Pole1.Distance(Pole2);
    Knot.SetValue(i, Knot.Value(i - 1) + KnotDist);
  }

  int Degree = 1;

  NCollection_Array1<int> Mult(1, NbPoints);
  Mult.Init(Degree);
  Mult.SetValue(Mult.Lower(), Degree + 1);
  Mult.SetValue(Mult.Upper(), Degree + 1);

  res = new Geom_BSplineCurve(Pole, Knot, Mult, Degree);

  IGESConvGeom::IncreaseCurveContinuity(res,
                                        std::max(GetEpsGeom() / 10., Precision::Confusion()),
                                        GetContinuity());
  return res;
}

occ::handle<Geom2d_BSplineCurve> IGESToBRep_BasicCurve::Transfer2dCopiousData(
  const occ::handle<IGESGeom_CopiousData>& start)
{
  occ::handle<Geom2d_BSplineCurve> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  int FormNb = start->FormNumber();
  if (FormNb != 11 && FormNb != 12 && FormNb != 63)
  {
    Message_Msg msg1240("IGES_1240");
    SendWarning(start, msg1240);
  }

  int NbPoints = start->NbPoints();
  if (NbPoints < 2)
  {
    Message_Msg msg1195("IGES_1195");
    SendFail(start, msg1195);
    return res;
  }

  NCollection_Array1<gp_Pnt2d> TempPole(1, NbPoints);
  int                          TempIndex = TempPole.Lower();

  if (!GetModeTransfer() && start->HasTransf())
    TempPole.SetValue(TempIndex,
                      gp_Pnt2d(start->TransformedPoint(1).X(), start->TransformedPoint(1).Y()));
  else
    TempPole.SetValue(TempIndex, gp_Pnt2d(start->Point(1).X(), start->Point(1).Y()));

  TempIndex++;
  int i;
  for (i = 2; i <= NbPoints; i++)
  {
    gp_Pnt2d aPole;
    if (!GetModeTransfer() && start->HasTransf())
      aPole = gp_Pnt2d(start->TransformedPoint(i).X(), start->TransformedPoint(i).Y());
    else
      aPole = gp_Pnt2d(start->Point(i).X(), start->Point(i).Y());

    if (!aPole.IsEqual(TempPole(TempIndex - 1), gp::Resolution()))
      TempPole.SetValue(TempIndex++, aPole);
  }

  NbPoints = TempIndex - TempPole.Lower();

  if (NbPoints == 1)
  {
    Message_Msg msg1235("IGES_1235");
    SendFail(start, msg1235);

    return res;
  }
  NCollection_Array1<gp_Pnt2d> Pole(1, NbPoints);

  TempIndex = TempPole.Lower();
  for (i = Pole.Lower(); i <= Pole.Upper(); i++)
    Pole.SetValue(i, TempPole.Value(TempIndex++));

  NCollection_Array1<double> Knot(1, NbPoints);

  Knot.SetValue(Knot.Lower(), 0.0);

  for (i = Knot.Lower() + 1; i <= Knot.Upper(); i++)
  {
    gp_Pnt2d Pole1    = Pole.Value(i);
    gp_Pnt2d Pole2    = Pole.Value(i - 1);
    double   KnotDist = Pole1.Distance(Pole2);
    Knot.SetValue(i, Knot.Value(i - 1) + KnotDist);
  }

  const int Degree = 1;

  NCollection_Array1<int> Mult(1, NbPoints);
  Mult.Init(Degree);
  Mult.SetValue(Mult.Lower(), Degree + 1);
  Mult.SetValue(Mult.Upper(), Degree + 1);

  res = new Geom2d_BSplineCurve(Pole, Knot, Mult, Degree);

  double epsGeom        = GetEpsGeom();
  double anUVResolution = GetUVResolution();

  IGESConvGeom::IncreaseCurveContinuity(res,
                                        std::max(Precision::Confusion(), epsGeom * anUVResolution),
                                        GetContinuity());
  return res;
}
