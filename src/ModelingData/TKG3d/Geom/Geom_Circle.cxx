#include <ElCLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Geometry.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Circle, Geom_Conic)

typedef Geom_Circle Circle;
typedef gp_Ax2      Ax2;
typedef gp_Pnt      Pnt;
typedef gp_Trsf     Trsf;
typedef gp_Vec      Vec;
typedef gp_XYZ      XYZ;

occ::handle<Geom_Geometry> Geom_Circle::Copy() const
{

  occ::handle<Geom_Circle> C;
  C = new Circle(pos, radius);
  return C;
}

Geom_Circle::Geom_Circle(const gp_Circ& C)
    : radius(C.Radius())
{

  pos = C.Position();
}

Geom_Circle::Geom_Circle(const Ax2& A2, const double R)
    : radius(R)
{

  if (R < 0.0)
    throw Standard_ConstructionError();
  pos = A2;
}

bool Geom_Circle::IsClosed() const
{
  return true;
}

bool Geom_Circle::IsPeriodic() const
{
  return true;
}

double Geom_Circle::ReversedParameter(const double U) const
{
  return (2. * M_PI - U);
}

double Geom_Circle::Eccentricity() const
{
  return 0.0;
}

double Geom_Circle::FirstParameter() const
{
  return 0.0;
}

double Geom_Circle::LastParameter() const
{
  return 2.0 * M_PI;
}

gp_Circ Geom_Circle::Circ() const
{
  return gp_Circ(pos, radius);
}

void Geom_Circle::SetCirc(const gp_Circ& C)
{

  radius = C.Radius();
  pos    = C.Position();
}

void Geom_Circle::SetRadius(const double R)
{

  if (R < 0.0)
    throw Standard_ConstructionError();
  radius = R;
}

double Geom_Circle::Radius() const
{
  return radius;
}

void Geom_Circle::D0(const double U, Pnt& P) const
{

  P = ElCLib::CircleValue(U, pos, radius);
}

void Geom_Circle::D1(const double U, Pnt& P, Vec& V1) const
{

  ElCLib::CircleD1(U, pos, radius, P, V1);
}

void Geom_Circle::D2(const double U, Pnt& P, Vec& V1, Vec& V2) const
{

  ElCLib::CircleD2(U, pos, radius, P, V1, V2);
}

void Geom_Circle::D3(const double U, Pnt& P, Vec& V1, Vec& V2, Vec& V3) const
{

  ElCLib::CircleD3(U, pos, radius, P, V1, V2, V3);
}

Vec Geom_Circle::DN(const double U, const int N) const
{

  Standard_RangeError_Raise_if(N < 1, " ");
  return ElCLib::CircleDN(U, pos, radius, N);
}

void Geom_Circle::Transform(const Trsf& T)
{

  radius = radius * std::abs(T.ScaleFactor());
  pos.Transform(T);
}

void Geom_Circle::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Conic)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, radius)
}
