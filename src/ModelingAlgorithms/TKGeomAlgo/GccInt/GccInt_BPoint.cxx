#include <GccInt_BPoint.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BPoint, GccInt_Bisec)

GccInt_BPoint::GccInt_BPoint(const gp_Pnt2d& Point)
{
  pnt = gp_Pnt2d(Point);
}

GccInt_IType GccInt_BPoint::ArcType() const
{
  return GccInt_Pnt;
}

gp_Pnt2d GccInt_BPoint::Point() const
{
  return pnt;
}
