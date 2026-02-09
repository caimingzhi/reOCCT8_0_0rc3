#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiCurve.hpp>
#include <math_Vector.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Standard_OutOfRange;
class StdFail_NotDone;
class BRepApprox_TheMultiLineOfApprox;
class BRepApprox_TheMultiLineToolOfApprox;
class BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox;
class BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox;
class AppParCurves_MultiCurve;

class BRepApprox_MyGradientOfTheComputeLineBezierOfApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_MyGradientOfTheComputeLineBezierOfApprox(
    const BRepApprox_TheMultiLineOfApprox&                                 SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    math_Vector&                                                           Parameters,
    const int                                                              Deg,
    const double                                                           Tol3d,
    const double                                                           Tol2d,
    const int                                                              NbIterations = 200);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT AppParCurves_MultiCurve Value() const;

  Standard_EXPORT double Error(const int Index) const;

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT double MaxError2d() const;

  Standard_EXPORT double AverageError() const;

private:
  AppParCurves_MultiCurve SCU;
  math_Vector             ParError;
  double                  AvError;
  double                  MError3d;
  double                  MError2d;
  bool                    Done;
};
