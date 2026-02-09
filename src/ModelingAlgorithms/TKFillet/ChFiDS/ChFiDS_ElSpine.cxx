#include <Adaptor3d_Curve.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <ChFiDS_SurfData.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ChFiDS_ElSpine, Adaptor3d_Curve)

ChFiDS_ElSpine::ChFiDS_ElSpine()
    : pfirst(0.0),
      plast(0.0),
      period(0.0),
      periodic(false),
      pfirstsav(Precision::Infinite()),
      plastsav(Precision::Infinite())
{
}

occ::handle<Adaptor3d_Curve> ChFiDS_ElSpine::ShallowCopy() const
{
  occ::handle<ChFiDS_ElSpine> aCopy = new ChFiDS_ElSpine();

  const occ::handle<Adaptor3d_Curve> aCurve     = curve.ShallowCopy();
  const GeomAdaptor_Curve&           aGeomCurve = *(occ::down_cast<GeomAdaptor_Curve>(aCurve));
  aCopy->curve                                  = aGeomCurve;

  aCopy->ptfirst              = ptfirst;
  aCopy->ptlast               = ptlast;
  aCopy->tgfirst              = tgfirst;
  aCopy->tglast               = tglast;
  aCopy->VerticesWithTangents = VerticesWithTangents;
  aCopy->previous             = previous;
  aCopy->next                 = next;
  aCopy->pfirst               = pfirst;
  aCopy->plast                = plast;
  aCopy->period               = period;
  aCopy->periodic             = periodic;
  aCopy->pfirstsav            = pfirstsav;
  aCopy->plastsav             = plastsav;

  return aCopy;
}

double ChFiDS_ElSpine::FirstParameter() const
{
  return pfirst;
}

double ChFiDS_ElSpine::LastParameter() const
{
  return plast;
}

double ChFiDS_ElSpine::GetSavedFirstParameter() const
{
  return pfirstsav;
}

double ChFiDS_ElSpine::GetSavedLastParameter() const
{
  return plastsav;
}

GeomAbs_Shape ChFiDS_ElSpine::Continuity() const
{
  return curve.Continuity();
}

int ChFiDS_ElSpine::NbIntervals(const GeomAbs_Shape S) const
{
  return curve.NbIntervals(S);
}

void ChFiDS_ElSpine::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  curve.Intervals(T, S);
}

occ::handle<Adaptor3d_Curve> ChFiDS_ElSpine::Trim(const double First,
                                                  const double Last,
                                                  const double Tol) const
{
  return curve.Trim(First, Last, Tol);
}

double ChFiDS_ElSpine::Resolution(const double R3d) const
{
  return curve.Resolution(R3d);
}

GeomAbs_CurveType ChFiDS_ElSpine::GetType() const
{
  return curve.GetType();
}

bool ChFiDS_ElSpine::IsPeriodic() const
{
  return periodic;
}

void ChFiDS_ElSpine::SetPeriodic(const bool I)
{
  periodic = I;
  period   = plast - pfirst;
}

double ChFiDS_ElSpine::Period() const
{
  if (!periodic)
    throw Standard_Failure("ElSpine non periodique");
  return period;
}

gp_Pnt ChFiDS_ElSpine::Value(const double AbsC) const
{
  return curve.Value(AbsC);
}

void ChFiDS_ElSpine::D0(const double AbsC, gp_Pnt& P) const
{
  curve.D0(AbsC, P);
}

void ChFiDS_ElSpine::D1(const double AbsC, gp_Pnt& P, gp_Vec& V1) const
{
  curve.D1(AbsC, P, V1);
}

void ChFiDS_ElSpine::D2(const double AbsC, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  curve.D2(AbsC, P, V1, V2);
}

void ChFiDS_ElSpine::D3(const double AbsC, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{
  curve.D3(AbsC, P, V1, V2, V3);
}

void ChFiDS_ElSpine::FirstParameter(const double P)
{
  pfirst = P;
}

void ChFiDS_ElSpine::LastParameter(const double P)
{
  plast = P;
}

void ChFiDS_ElSpine::SaveFirstParameter()
{
  pfirstsav = pfirst;
}

void ChFiDS_ElSpine::SaveLastParameter()
{
  plastsav = plast;
}

void ChFiDS_ElSpine::SetOrigin(const double O)
{
  if (!periodic)
    throw Standard_Failure("Elspine non periodique");
  occ::handle<Geom_BSplineCurve> bs = occ::down_cast<Geom_BSplineCurve>(curve.Curve());
  if (!bs.IsNull())
  {
    bs->SetOrigin(O, Precision::PConfusion());
    curve.Load(bs);
  }
}

void ChFiDS_ElSpine::SetFirstPointAndTgt(const gp_Pnt& P, const gp_Vec& T)
{
  ptfirst = P;
  tgfirst = T;
}

void ChFiDS_ElSpine::SetLastPointAndTgt(const gp_Pnt& P, const gp_Vec& T)
{
  ptlast = P;
  tglast = T;
}

void ChFiDS_ElSpine::AddVertexWithTangent(const gp_Ax1& anAx1)
{
  VerticesWithTangents.Append(anAx1);
}

void ChFiDS_ElSpine::FirstPointAndTgt(gp_Pnt& P, gp_Vec& T) const
{
  P = ptfirst;
  T = tgfirst;
}

void ChFiDS_ElSpine::LastPointAndTgt(gp_Pnt& P, gp_Vec& T) const
{
  P = ptlast;
  T = tglast;
}

int ChFiDS_ElSpine::NbVertices() const
{
  return VerticesWithTangents.Length();
}

const gp_Ax1& ChFiDS_ElSpine::VertexWithTangent(const int Index) const
{
  return VerticesWithTangents(Index);
}

void ChFiDS_ElSpine::SetCurve(const occ::handle<Geom_Curve>& C)
{
  curve.Load(C);
}

const occ::handle<ChFiDS_SurfData>& ChFiDS_ElSpine::Previous() const
{
  return previous;
}

occ::handle<ChFiDS_SurfData>& ChFiDS_ElSpine::ChangePrevious()
{
  return previous;
}

const occ::handle<ChFiDS_SurfData>& ChFiDS_ElSpine::Next() const
{
  return next;
}

occ::handle<ChFiDS_SurfData>& ChFiDS_ElSpine::ChangeNext()
{
  return next;
}

gp_Lin ChFiDS_ElSpine::Line() const
{
  return curve.Line();
}

gp_Circ ChFiDS_ElSpine::Circle() const
{
  return curve.Circle();
}

gp_Elips ChFiDS_ElSpine::Ellipse() const
{
  return curve.Ellipse();
}

gp_Hypr ChFiDS_ElSpine::Hyperbola() const
{
  return curve.Hyperbola();
}

gp_Parab ChFiDS_ElSpine::Parabola() const
{
  return curve.Parabola();
}

occ::handle<Geom_BezierCurve> ChFiDS_ElSpine::Bezier() const
{
  return curve.Bezier();
}

occ::handle<Geom_BSplineCurve> ChFiDS_ElSpine::BSpline() const
{
  return curve.BSpline();
}
