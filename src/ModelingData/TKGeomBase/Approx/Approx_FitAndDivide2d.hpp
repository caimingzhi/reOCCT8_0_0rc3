#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <AppCont_Function.hpp>
#include <AppParCurves_Constraint.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class AppParCurves_MultiCurve;

class Approx_FitAndDivide2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_FitAndDivide2d(
    const AppCont_Function&       Line,
    const int                     degreemin   = 3,
    const int                     degreemax   = 8,
    const double                  Tolerance3d = 1.0e-5,
    const double                  Tolerance2d = 1.0e-5,
    const bool                    cutting     = false,
    const AppParCurves_Constraint FirstC      = AppParCurves_TangencyPoint,
    const AppParCurves_Constraint LastC       = AppParCurves_TangencyPoint);

  Standard_EXPORT Approx_FitAndDivide2d(
    const int                     degreemin   = 3,
    const int                     degreemax   = 8,
    const double                  Tolerance3d = 1.0e-05,
    const double                  Tolerance2d = 1.0e-05,
    const bool                    cutting     = false,
    const AppParCurves_Constraint FirstC      = AppParCurves_TangencyPoint,
    const AppParCurves_Constraint LastC       = AppParCurves_TangencyPoint);

  Standard_EXPORT void Perform(const AppCont_Function& Line);

  Standard_EXPORT void SetDegrees(const int degreemin, const int degreemax);

  Standard_EXPORT void SetTolerances(const double Tolerance3d, const double Tolerance2d);

  Standard_EXPORT void SetConstraints(const AppParCurves_Constraint FirstC,
                                      const AppParCurves_Constraint LastC);

  Standard_EXPORT void SetMaxSegments(const int theMaxSegments);

  Standard_EXPORT void SetInvOrder(const bool theInvOrder);

  Standard_EXPORT void SetHangChecking(const bool theHangChecking);

  Standard_EXPORT bool IsAllApproximated() const;

  Standard_EXPORT bool IsToleranceReached() const;

  Standard_EXPORT void Error(const int Index, double& tol3d, double& tol2d) const;

  Standard_EXPORT int NbMultiCurves() const;

  Standard_EXPORT AppParCurves_MultiCurve Value(const int Index = 1) const;

  Standard_EXPORT void Parameters(const int Index, double& firstp, double& lastp) const;

private:
  Standard_EXPORT bool Compute(const AppCont_Function& Line,
                               const double            Ufirst,
                               const double            Ulast,
                               double&                 TheTol3d,
                               double&                 TheTol2d);

  NCollection_Sequence<AppParCurves_MultiCurve> myMultiCurves;
  NCollection_Sequence<double>                  myfirstparam;
  NCollection_Sequence<double>                  mylastparam;
  AppParCurves_MultiCurve                       TheMultiCurve;
  bool                                          alldone;
  bool                                          tolreached;
  NCollection_Sequence<double>                  Tolers3d;
  NCollection_Sequence<double>                  Tolers2d;
  int                                           mydegremin;
  int                                           mydegremax;
  double                                        mytol3d;
  double                                        mytol2d;
  double                                        currenttol3d;
  double                                        currenttol2d;
  bool                                          mycut;
  AppParCurves_Constraint                       myfirstC;
  AppParCurves_Constraint                       mylastC;
  int                                           myMaxSegments;
  bool                                          myInvOrder;
  bool                                          myHangChecking;
};
