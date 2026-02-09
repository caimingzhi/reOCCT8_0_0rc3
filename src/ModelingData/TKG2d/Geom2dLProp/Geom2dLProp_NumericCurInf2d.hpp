#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Curve;
class LProp_CurAndInf;

class Geom2dLProp_NumericCurInf2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dLProp_NumericCurInf2d();

  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C, LProp_CurAndInf& Result);

  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C, LProp_CurAndInf& Result);

  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C,
                                     const double                     UMin,
                                     const double                     UMax,
                                     LProp_CurAndInf&                 Result);

  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C,
                                  const double                     UMin,
                                  const double                     UMax,
                                  LProp_CurAndInf&                 Result);

  Standard_EXPORT bool IsDone() const;

private:
  bool isDone;
};
