#include <Geom2d_Curve.hpp>
#include <Geom2d_UndefinedDerivative.hpp>
#include <Geom2d_UndefinedValue.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Curve, Geom2d_Geometry)

typedef Geom2d_Curve Curve;

occ::handle<Geom2d_Curve> Geom2d_Curve::Reversed() const
{
  occ::handle<Geom2d_Curve> C = occ::down_cast<Geom2d_Curve>(Copy());
  C->Reverse();
  return C;
}

double Geom2d_Curve::TransformedParameter(const double U, const gp_Trsf2d&) const
{
  return U;
}

double Geom2d_Curve::ParametricTransformation(const gp_Trsf2d&) const
{
  return 1.;
}

double Geom2d_Curve::Period() const
{
  Standard_NoSuchObject_Raise_if(!IsPeriodic(), "Geom2d_Curve::Period");

  return (LastParameter() - FirstParameter());
}

gp_Pnt2d Geom2d_Curve::Value(const double U) const
{
  gp_Pnt2d P;
  D0(U, P);
  return P;
}

void Geom2d_Curve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom2d_Geometry)
}
