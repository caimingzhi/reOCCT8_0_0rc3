#include <Geom_Vector.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Vector, Geom_Geometry)

typedef Geom_Vector Vector;
typedef gp_Ax1      Ax1;
typedef gp_Ax2      Ax2;
typedef gp_Pnt      Pnt;
typedef gp_Trsf     Trsf;

void Geom_Vector::Reverse()
{
  gpVec.Reverse();
}

double Geom_Vector::X() const
{
  return gpVec.X();
}

double Geom_Vector::Y() const
{
  return gpVec.Y();
}

double Geom_Vector::Z() const
{
  return gpVec.Z();
}

const gp_Vec& Geom_Vector::Vec() const
{
  return gpVec;
}

occ::handle<Geom_Vector> Geom_Vector::Reversed() const
{
  occ::handle<Geom_Vector> V = occ::down_cast<Geom_Vector>(Copy());
  V->Reverse();
  return V;
}

double Geom_Vector::Angle(const occ::handle<Geom_Vector>& Other) const
{

  return gpVec.Angle(Other->Vec());
}

double Geom_Vector::AngleWithRef(const occ::handle<Geom_Vector>& Other,
                                 const occ::handle<Geom_Vector>& VRef) const
{

  return gpVec.AngleWithRef(Other->Vec(), VRef->Vec());
}

void Geom_Vector::Coord(double& X, double& Y, double& Z) const
{

  gpVec.Coord(X, Y, Z);
}

double Geom_Vector::Dot(const occ::handle<Geom_Vector>& Other) const
{

  return gpVec.Dot(Other->Vec());
}

double Geom_Vector::DotCross(const occ::handle<Geom_Vector>& V1,
                             const occ::handle<Geom_Vector>& V2) const
{

  return gpVec.DotCross(V1->Vec(), V2->Vec());
}
