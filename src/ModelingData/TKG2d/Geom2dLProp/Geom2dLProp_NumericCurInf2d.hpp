#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Curve;
class LProp_CurAndInf;

//! Computes the locals extremas of curvature and the
//! inflections of a bounded curve in 2d.
class Geom2dLProp_NumericCurInf2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dLProp_NumericCurInf2d();

  //! Computes the locals extremas of curvature.
  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C, LProp_CurAndInf& Result);

  //! Computes the inflections.
  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C, LProp_CurAndInf& Result);

  //! Computes the locals extremas of curvature.
  //! in the interval of parameters [UMin,UMax].
  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C,
                                     const double                     UMin,
                                     const double                     UMax,
                                     LProp_CurAndInf&                 Result);

  //! Computes the inflections in the interval of
  //! parameters [UMin,UMax].
  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C,
                                  const double                     UMin,
                                  const double                     UMax,
                                  LProp_CurAndInf&                 Result);

  //! True if the solutions are found.
  Standard_EXPORT bool IsDone() const;

private:
  bool isDone;
};
