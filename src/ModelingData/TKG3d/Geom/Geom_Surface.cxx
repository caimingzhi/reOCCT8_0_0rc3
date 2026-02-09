#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Geom_UndefinedDerivative.hpp>
#include <Geom_UndefinedValue.hpp>
#include <gp_GTrsf2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Surface, Geom_Geometry)

typedef Geom_Surface Surface;

occ::handle<Geom_Surface> Geom_Surface::UReversed() const
{
  occ::handle<Geom_Surface> S = occ::down_cast<Geom_Surface>(Copy());
  S->UReverse();
  return S;
}

occ::handle<Geom_Surface> Geom_Surface::VReversed() const
{
  occ::handle<Geom_Surface> S = occ::down_cast<Geom_Surface>(Copy());
  S->VReverse();
  return S;
}

void Geom_Surface::TransformParameters(double&, double&, const gp_Trsf&) const {}

gp_GTrsf2d Geom_Surface::ParametricTransformation(const gp_Trsf&) const
{
  gp_GTrsf2d dummy;
  return dummy;
}

double Geom_Surface::UPeriod() const
{
  Standard_NoSuchObject_Raise_if(!IsUPeriodic(), "Geom_Surface::UPeriod");

  double U1, U2, V1, V2;
  Bounds(U1, U2, V1, V2);
  return (U2 - U1);
}

double Geom_Surface::VPeriod() const
{
  Standard_NoSuchObject_Raise_if(!IsVPeriodic(), "Geom_Surface::VPeriod");

  double U1, U2, V1, V2;
  Bounds(U1, U2, V1, V2);
  return (V2 - V1);
}

gp_Pnt Geom_Surface::Value(const double U, const double V) const
{
  gp_Pnt P;
  D0(U, V, P);
  return P;
}

void Geom_Surface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Geometry)
}
