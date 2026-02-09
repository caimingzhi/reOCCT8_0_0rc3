#include <BRepPrim_Wedge.hpp>
#include <gp_Ax2.hpp>

BRepPrim_Wedge::BRepPrim_Wedge(const gp_Ax2& Axes,
                               const double  dx,
                               const double  dy,
                               const double  dz)
    : BRepPrim_GWedge(BRepPrim_Builder(), Axes, dx, dy, dz)
{
}

BRepPrim_Wedge::BRepPrim_Wedge(const gp_Ax2& Axes,
                               const double  dx,
                               const double  dy,
                               const double  dz,
                               const double  ltx)
    : BRepPrim_GWedge(BRepPrim_Builder(), Axes, dx, dy, dz, ltx)
{
}

BRepPrim_Wedge::BRepPrim_Wedge(const gp_Ax2& Axes,
                               const double  xmin,
                               const double  ymin,
                               const double  zmin,
                               const double  z2min,
                               const double  x2min,
                               const double  xmax,
                               const double  ymax,
                               const double  zmax,
                               const double  z2max,
                               const double  x2max)
    : BRepPrim_GWedge(BRepPrim_Builder(),
                      Axes,
                      xmin,
                      ymin,
                      zmin,
                      z2min,
                      x2min,
                      xmax,
                      ymax,
                      zmax,
                      z2max,
                      x2max)
{
}
