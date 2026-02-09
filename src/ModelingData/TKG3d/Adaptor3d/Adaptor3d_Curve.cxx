#include <Adaptor3d_Curve.hpp>

#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_NotImplemented.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Adaptor3d_Curve, Standard_Transient)

Adaptor3d_Curve::~Adaptor3d_Curve() = default;

occ::handle<Adaptor3d_Curve> Adaptor3d_Curve::ShallowCopy() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::ShallowCopy");
}

double Adaptor3d_Curve::FirstParameter() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::FirstParameter");
}

double Adaptor3d_Curve::LastParameter() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::LastParameter");
}

GeomAbs_Shape Adaptor3d_Curve::Continuity() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Continuity");
}

int Adaptor3d_Curve::NbIntervals(const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::NbIntervals");
}

void Adaptor3d_Curve::Intervals(NCollection_Array1<double>&, const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Intervals");
}

occ::handle<Adaptor3d_Curve> Adaptor3d_Curve::Trim(const double, const double, const double) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Trim");
}

bool Adaptor3d_Curve::IsClosed() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::IsClosed");
}

bool Adaptor3d_Curve::IsPeriodic() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::IsPeriodic");
}

double Adaptor3d_Curve::Period() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Period");
}

gp_Pnt Adaptor3d_Curve::Value(const double) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Value");
}

void Adaptor3d_Curve::D0(const double, gp_Pnt&) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::D0");
}

void Adaptor3d_Curve::D1(const double, gp_Pnt&, gp_Vec&) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::D1");
}

void Adaptor3d_Curve::D2(const double, gp_Pnt&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::D2");
}

void Adaptor3d_Curve::D3(const double, gp_Pnt&, gp_Vec&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::D3");
}

gp_Vec Adaptor3d_Curve::DN(const double, const int) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::DN");
}

double Adaptor3d_Curve::Resolution(const double) const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Resolution");
}

GeomAbs_CurveType Adaptor3d_Curve::GetType() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::GetType");
}

gp_Lin Adaptor3d_Curve::Line() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Line");
}

gp_Circ Adaptor3d_Curve::Circle() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Circle");
}

gp_Elips Adaptor3d_Curve::Ellipse() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Ellipse");
}

gp_Hypr Adaptor3d_Curve::Hyperbola() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Hyperbola");
}

gp_Parab Adaptor3d_Curve::Parabola() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Parabola");
}

int Adaptor3d_Curve::Degree() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Degree");
}

bool Adaptor3d_Curve::IsRational() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::IsRational");
}

int Adaptor3d_Curve::NbPoles() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::NbPoles");
}

int Adaptor3d_Curve::NbKnots() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::NbKnots");
}

occ::handle<Geom_BezierCurve> Adaptor3d_Curve::Bezier() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::Bezier");
}

occ::handle<Geom_BSplineCurve> Adaptor3d_Curve::BSpline() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::BSpline");
}

occ::handle<Geom_OffsetCurve> Adaptor3d_Curve::OffsetCurve() const
{
  throw Standard_NotImplemented("Adaptor3d_Curve::OffsetCurve");
}
