#include <Geom_CartesianPoint.hpp>
#include <Geom_Geometry.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_CartesianPoint, Geom_Point)

typedef Geom_CartesianPoint CartesianPoint;
typedef gp_Ax1              Ax1;
typedef gp_Ax2              Ax2;
typedef gp_Vec              Vec;
typedef gp_Trsf             Trsf;

Geom_CartesianPoint::Geom_CartesianPoint(const gp_Pnt& P)
    : gpPnt(P)
{
}

Geom_CartesianPoint::Geom_CartesianPoint(const double X, const double Y, const double Z)
    : gpPnt(X, Y, Z)
{
}

occ::handle<Geom_Geometry> Geom_CartesianPoint::Copy() const
{

  occ::handle<Geom_CartesianPoint> P;
  P = new CartesianPoint(gpPnt);
  return P;
}

void Geom_CartesianPoint::SetCoord(const double X, const double Y, const double Z)
{

  gpPnt.SetCoord(X, Y, Z);
}

void Geom_CartesianPoint::SetPnt(const gp_Pnt& P)
{
  gpPnt = P;
}

void Geom_CartesianPoint::SetX(const double X)
{
  gpPnt.SetX(X);
}

void Geom_CartesianPoint::SetY(const double Y)
{
  gpPnt.SetY(Y);
}

void Geom_CartesianPoint::SetZ(const double Z)
{
  gpPnt.SetZ(Z);
}

void Geom_CartesianPoint::Coord(double& X, double& Y, double& Z) const
{

  gpPnt.Coord(X, Y, Z);
}

gp_Pnt Geom_CartesianPoint::Pnt() const
{
  return gpPnt;
}

double Geom_CartesianPoint::X() const
{
  return gpPnt.X();
}

double Geom_CartesianPoint::Y() const
{
  return gpPnt.Y();
}

double Geom_CartesianPoint::Z() const
{
  return gpPnt.Z();
}

void Geom_CartesianPoint::Transform(const Trsf& T)
{
  gpPnt.Transform(T);
}
