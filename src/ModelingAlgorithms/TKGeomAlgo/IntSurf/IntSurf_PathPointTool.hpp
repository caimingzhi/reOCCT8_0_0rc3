#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
#include <Standard_Integer.hpp>
class Standard_OutOfRange;
class StdFail_UndefinedDerivative;
class IntSurf_PathPoint;

class IntSurf_PathPointTool
{
public:
  DEFINE_STANDARD_ALLOC

  static gp_Pnt Value3d(const IntSurf_PathPoint& PStart);

  static void Value2d(const IntSurf_PathPoint& PStart, double& U, double& V);

  static bool IsPassingPnt(const IntSurf_PathPoint& PStart);

  static bool IsTangent(const IntSurf_PathPoint& PStart);

  static gp_Vec Direction3d(const IntSurf_PathPoint& PStart);

  static gp_Dir2d Direction2d(const IntSurf_PathPoint& PStart);

  static int Multiplicity(const IntSurf_PathPoint& PStart);

  static void Parameters(const IntSurf_PathPoint& PStart, const int Mult, double& U, double& V);
};

#include <IntSurf_PathPoint.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir2d.hpp>

inline gp_Pnt IntSurf_PathPointTool::Value3d(const IntSurf_PathPoint& PStart)
{
  return PStart.Value();
}

inline void IntSurf_PathPointTool::Value2d(const IntSurf_PathPoint& PStart, double& U, double& V)
{
  PStart.Value2d(U, V);
}

inline bool IntSurf_PathPointTool::IsPassingPnt(const IntSurf_PathPoint& PStart)
{

  return PStart.IsPassingPnt();
}

inline bool IntSurf_PathPointTool::IsTangent(const IntSurf_PathPoint& PStart)
{
  return PStart.IsTangent();
}

inline gp_Vec IntSurf_PathPointTool::Direction3d(const IntSurf_PathPoint& PStart)
{
  return PStart.Direction3d();
}

inline gp_Dir2d IntSurf_PathPointTool::Direction2d(const IntSurf_PathPoint& PStart)
{
  return PStart.Direction2d();
}

inline int IntSurf_PathPointTool::Multiplicity(const IntSurf_PathPoint& PStart)
{
  return PStart.Multiplicity();
}

inline void IntSurf_PathPointTool::Parameters(const IntSurf_PathPoint& PStart,
                                              const int                Mult,
                                              double&                  U,
                                              double&                  V)
{
  PStart.Parameters(Mult, U, V);
}
