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
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute;
class AppDef_ResConstraintOfMyGradientbisOfBSplineCompute;
class AppDef_ParFunctionOfMyGradientbisOfBSplineCompute;
class AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute;
class AppParCurves_MultiCurve;

class AppDef_MyGradientbisOfBSplineCompute
{
public:
  DEFINE_STANDARD_ALLOC

  //! Tries to minimize the sum (square(||Qui - Bi*Pi||))
  //! where Pui describe the approximating Bezier curves'Poles
  //! and Qi the MultiLine points with a parameter ui.
  //! In this algorithm, the parameters ui are the unknowns.
  //! The tolerance required on this sum is given by Tol.
  //! The desired degree of the resulting curve is Deg.
  Standard_EXPORT AppDef_MyGradientbisOfBSplineCompute(
    const AppDef_MultiLine&                                                SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    math_Vector&                                                           Parameters,
    const int                                                              Deg,
    const double                                                           Tol3d,
    const double                                                           Tol2d,
    const int                                                              NbIterations = 200);

  //! returns True if all has been correctly done.
  Standard_EXPORT bool IsDone() const;

  //! returns all the Bezier curves approximating the
  //! MultiLine SSP after minimization of the parameter.
  Standard_EXPORT AppParCurves_MultiCurve Value() const;

  //! returns the difference between the old and the new
  //! approximation.
  //! An exception is raised if NotDone.
  //! An exception is raised if Index<1 or Index>NbParameters.
  Standard_EXPORT double Error(const int Index) const;

  //! returns the maximum difference between the old and the
  //! new approximation.
  Standard_EXPORT double MaxError3d() const;

  //! returns the maximum difference between the old and the
  //! new approximation.
  Standard_EXPORT double MaxError2d() const;

  //! returns the average error between the old and the
  //! new approximation.
  Standard_EXPORT double AverageError() const;

private:
  AppParCurves_MultiCurve SCU;
  math_Vector             ParError;
  double                  AvError;
  double                  MError3d;
  double                  MError2d;
  bool                    Done;
};

