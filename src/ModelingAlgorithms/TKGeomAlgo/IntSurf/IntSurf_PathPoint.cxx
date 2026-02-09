

#include <gp_Dir2d.hpp>
#include <gp_Pnt.hpp>
#include <IntSurf_PathPoint.hpp>
#include <StdFail_UndefinedDerivative.hpp>

IntSurf_PathPoint::IntSurf_PathPoint()
    : ispass(true),
      istgt(true)
{
}

IntSurf_PathPoint::IntSurf_PathPoint(const gp_Pnt& P, const double U, const double V)
    : pt(P),
      ispass(true),
      istgt(true)
{
  sequv = new NCollection_HSequence<gp_XY>();
  sequv->Append(gp_XY(U, V));
}

void IntSurf_PathPoint::SetValue(const gp_Pnt& P, const double U, const double V)
{
  pt    = P;
  sequv = new NCollection_HSequence<gp_XY>();
  sequv->Append(gp_XY(U, V));
}
