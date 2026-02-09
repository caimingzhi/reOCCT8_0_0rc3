

#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <IntSurf_InteriorPoint.hpp>

IntSurf_InteriorPoint::IntSurf_InteriorPoint()
    : paramu(0.0),
      paramv(0.0)
{
}

IntSurf_InteriorPoint::IntSurf_InteriorPoint(const gp_Pnt&   P,
                                             const double    U,
                                             const double    V,
                                             const gp_Vec&   Direc,
                                             const gp_Vec2d& Direc2d)
    : point(P),
      paramu(U),
      paramv(V),
      direc(Direc),
      direc2d(Direc2d)

{
}

void IntSurf_InteriorPoint::SetValue(const gp_Pnt&   P,
                                     const double    U,
                                     const double    V,
                                     const gp_Vec&   Direc,
                                     const gp_Vec2d& Direc2d)
{

  point   = P;
  paramu  = U;
  paramv  = V;
  direc   = Direc;
  direc2d = Direc2d;
}
