#include <Geom_Curve.hpp>
#include <Geom_UndefinedDerivative.hpp>
#include <Geom_UndefinedValue.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Curve, Geom_Geometry)

typedef Geom_Curve Curve;

occ::handle<Geom_Curve> Geom_Curve::Reversed() const
{
  occ::handle<Geom_Curve> C = occ::down_cast<Geom_Curve>(Copy());
  C->Reverse();
  return C;
}

double Geom_Curve::Period() const
{
  Standard_NoSuchObject_Raise_if(!IsPeriodic(), "Geom_Curve::Period");

  return (LastParameter() - FirstParameter());
}

gp_Pnt Geom_Curve::Value(const double U) const
{
  gp_Pnt P;
  D0(U, P);
  return P;
}

double Geom_Curve::TransformedParameter(const double U, const gp_Trsf&) const
{
  return U;
}

double Geom_Curve::ParametricTransformation(const gp_Trsf&) const
{
  return 1.;
}

void Geom_Curve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Geometry)
}
