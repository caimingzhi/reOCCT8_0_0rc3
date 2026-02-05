#include <Geom_Point.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Point, Geom_Geometry)

typedef Geom_Point Point;

double Geom_Point::Distance(const occ::handle<Geom_Point>& Other) const
{

  gp_Pnt P1 = this->Pnt();
  gp_Pnt P2 = Other->Pnt();
  return P1.Distance(P2);
}

double Geom_Point::SquareDistance(const occ::handle<Geom_Point>& Other) const
{

  gp_Pnt P1 = this->Pnt();
  gp_Pnt P2 = Other->Pnt();
  return P1.SquareDistance(P2);
}
