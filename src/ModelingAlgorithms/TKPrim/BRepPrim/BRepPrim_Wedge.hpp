#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_GWedge.hpp>
class gp_Ax2;

class BRepPrim_Wedge : public BRepPrim_GWedge
{
public:
  DEFINE_STANDARD_ALLOC

  BRepPrim_Wedge() = default;

  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  dx,
                                 const double  dy,
                                 const double  dz);

  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  dx,
                                 const double  dy,
                                 const double  dz,
                                 const double  ltx);

  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  xmin,
                                 const double  ymin,
                                 const double  zmin,
                                 const double  z2min,
                                 const double  x2min,
                                 const double  xmax,
                                 const double  ymax,
                                 const double  zmax,
                                 const double  z2max,
                                 const double  x2max);
};
