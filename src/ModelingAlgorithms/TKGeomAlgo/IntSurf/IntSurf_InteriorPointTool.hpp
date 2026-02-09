#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
class IntSurf_InteriorPoint;

class IntSurf_InteriorPointTool
{
public:
  DEFINE_STANDARD_ALLOC

  static gp_Pnt Value3d(const IntSurf_InteriorPoint& PStart);

  static void Value2d(const IntSurf_InteriorPoint& PStart, double& U, double& V);

  static gp_Vec Direction3d(const IntSurf_InteriorPoint& PStart);

  static gp_Dir2d Direction2d(const IntSurf_InteriorPoint& PStart);
};

#include <IntSurf_InteriorPoint.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>

inline gp_Pnt IntSurf_InteriorPointTool::Value3d(const IntSurf_InteriorPoint& PStart)
{

  return PStart.Value();
}

inline void IntSurf_InteriorPointTool::Value2d(const IntSurf_InteriorPoint& PStart,
                                               double&                      U,
                                               double&                      V)
{
  PStart.Parameters(U, V);
}

inline gp_Vec IntSurf_InteriorPointTool::Direction3d(const IntSurf_InteriorPoint& PStart)
{

  return PStart.Direction();
}

inline gp_Dir2d IntSurf_InteriorPointTool::Direction2d(const IntSurf_InteriorPoint& PStart)
{

  return PStart.Direction2d();
}
