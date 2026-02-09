#include <Geom_Direction.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_Vector.hpp>
#include <gp.hpp>
#include <gp_Dir.hpp>
#include <gp_Trsf.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Direction, Geom_Vector)

typedef Geom_Direction Direction;
typedef Geom_Vector    Vector;
typedef gp_Ax1         Ax1;
typedef gp_Ax2         Ax2;
typedef gp_Pnt         Pnt;
typedef gp_Trsf        Trsf;

occ::handle<Geom_Geometry> Geom_Direction::Copy() const
{

  occ::handle<Geom_Direction> D;
  D = new Direction(gpVec);
  return D;
}

Geom_Direction::Geom_Direction(const double X, const double Y, const double Z)
{

  double D = sqrt(X * X + Y * Y + Z * Z);
  Standard_ConstructionError_Raise_if(D <= gp::Resolution(),
                                      "Geom_Direction() - input vector has zero length");
  gpVec = gp_Vec(X / D, Y / D, Z / D);
}

Geom_Direction::Geom_Direction(const gp_Dir& V)
{
  gpVec = V;
}

void Geom_Direction::SetDir(const gp_Dir& V)
{
  gpVec = V;
}

gp_Dir Geom_Direction::Dir() const
{
  return gpVec;
}

double Geom_Direction::Magnitude() const
{
  return 1.0;
}

double Geom_Direction::SquareMagnitude() const
{
  return 1.0;
}

void Geom_Direction::SetCoord(const double X, const double Y, const double Z)
{

  double D = std::sqrt(X * X + Y * Y + Z * Z);
  Standard_ConstructionError_Raise_if(D <= gp::Resolution(),
                                      "Geom_Direction::SetCoord() - input vector has zero length");
  gpVec = gp_Vec(X / D, Y / D, Z / D);
}

void Geom_Direction::SetX(const double X)
{

  double D = std::sqrt(X * X + gpVec.Y() * gpVec.Y() + gpVec.Z() * gpVec.Z());
  Standard_ConstructionError_Raise_if(D <= gp::Resolution(),
                                      "Geom_Direction::SetX() - input vector has zero length");
  gpVec = gp_Vec(X / D, gpVec.Y() / D, gpVec.Z() / D);
}

void Geom_Direction::SetY(const double Y)
{

  double D = std::sqrt(gpVec.X() * gpVec.X() + Y * Y + gpVec.Z() * gpVec.Z());
  Standard_ConstructionError_Raise_if(D <= gp::Resolution(),
                                      "Geom_Direction::SetY() - input vector has zero length");
  gpVec = gp_Vec(gpVec.X() / D, Y / D, gpVec.Z() / D);
}

void Geom_Direction::SetZ(const double Z)
{

  double D = std::sqrt(gpVec.X() * gpVec.X() + gpVec.Y() * gpVec.Y() + Z * Z);
  Standard_ConstructionError_Raise_if(D <= gp::Resolution(),
                                      "Geom_Direction::SetZ() - input vector has zero length");
  gpVec = gp_Vec(gpVec.X() / D, gpVec.Y() / D, Z / D);
}

void Geom_Direction::Cross(const occ::handle<Geom_Vector>& Other)
{

  gp_Dir V(gpVec.Crossed(Other->Vec()));
  gpVec = V;
}

void Geom_Direction::CrossCross(const occ::handle<Geom_Vector>& V1,
                                const occ::handle<Geom_Vector>& V2)
{

  gp_Dir V(gpVec.CrossCrossed(V1->Vec(), V2->Vec()));
  gpVec = V;
}

occ::handle<Geom_Vector> Geom_Direction::Crossed(const occ::handle<Geom_Vector>& Other) const
{

  gp_Dir V(gpVec.Crossed(Other->Vec()));
  return new Direction(V);
}

occ::handle<Geom_Vector> Geom_Direction::CrossCrossed(const occ::handle<Geom_Vector>& V1,
                                                      const occ::handle<Geom_Vector>& V2) const
{

  gp_Dir V(gpVec.CrossCrossed(V1->Vec(), V2->Vec()));
  return new Direction(V);
}

void Geom_Direction::Transform(const gp_Trsf& T)
{

  gp_Dir V(gpVec);
  V.Transform(T);
  gpVec = V;
}
