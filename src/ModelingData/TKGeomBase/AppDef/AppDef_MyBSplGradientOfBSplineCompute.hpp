#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiBSpCurve.hpp>
#include <math_Vector.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Standard_OutOfRange;
class StdFail_NotDone;
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute;
class AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute;
class AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute;
class AppParCurves_MultiBSpCurve;

class AppDef_MyBSplGradientOfBSplineCompute
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_MyBSplGradientOfBSplineCompute(
    const AppDef_MultiLine&                                                SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    math_Vector&                                                           Parameters,
    const NCollection_Array1<double>&                                      Knots,
    const NCollection_Array1<int>&                                         Mults,
    const int                                                              Deg,
    const double                                                           Tol3d,
    const double                                                           Tol2d,
    const int                                                              NbIterations = 1);

  Standard_EXPORT AppDef_MyBSplGradientOfBSplineCompute(
    const AppDef_MultiLine&                                                SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    math_Vector&                                                           Parameters,
    const NCollection_Array1<double>&                                      Knots,
    const NCollection_Array1<int>&                                         Mults,
    const int                                                              Deg,
    const double                                                           Tol3d,
    const double                                                           Tol2d,
    const int                                                              NbIterations,
    const double                                                           lambda1,
    const double                                                           lambda2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT AppParCurves_MultiBSpCurve Value() const;

  Standard_EXPORT double Error(const int Index) const;

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT double MaxError2d() const;

  Standard_EXPORT double AverageError() const;

protected:
  Standard_EXPORT void Perform(
    const AppDef_MultiLine&                                                SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    math_Vector&                                                           Parameters,
    const NCollection_Array1<double>&                                      Knots,
    const NCollection_Array1<int>&                                         Mults,
    const int                                                              Deg,
    const double                                                           Tol3d,
    const double                                                           Tol2d,
    const int                                                              NbIterations = 200);

private:
  AppParCurves_MultiBSpCurve SCU;
  math_Vector                ParError;
  double                     AvError;
  double                     MError3d;
  double                     MError2d;
  double                     mylambda1;
  double                     mylambda2;
  bool                       myIsLambdaDefined;
  bool                       Done;
};
