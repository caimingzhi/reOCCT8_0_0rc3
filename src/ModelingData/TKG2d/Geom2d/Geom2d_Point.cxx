#include <Geom2d_Point.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Point, Geom2d_Geometry)

typedef Geom2d_Point Point;

double Geom2d_Point::Distance(const occ::handle<Geom2d_Point>& Other) const
{

  gp_Pnt2d P1 = this->Pnt2d();
  gp_Pnt2d P2 = Other->Pnt2d();
  return P1.Distance(P2);
}

double Geom2d_Point::SquareDistance(const occ::handle<Geom2d_Point>& Other) const
{

  gp_Pnt2d P1 = this->Pnt2d();
  gp_Pnt2d P2 = Other->Pnt2d();
  return P1.SquareDistance(P2);
}

void Geom2d_Point::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom2d_Geometry)
}
