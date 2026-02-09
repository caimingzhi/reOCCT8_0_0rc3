#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiBSpCurve.hpp>
#include <Approx_ParametrizationType.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <Standard_Real.hpp>
#include <AppParCurves_Constraint.hpp>
#include <math_Vector.hpp>
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_MyBSplGradientOfBSplineCompute;
class AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute;
class AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute;
class AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute;
class AppDef_MyGradientbisOfBSplineCompute;
class AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute;
class AppDef_ResConstraintOfMyGradientbisOfBSplineCompute;
class AppDef_ParFunctionOfMyGradientbisOfBSplineCompute;
class AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute;
class AppParCurves_MultiBSpCurve;
class AppParCurves_MultiCurve;

class AppDef_BSplineCompute
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_BSplineCompute(
    const AppDef_MultiLine&          Line,
    const int                        degreemin       = 4,
    const int                        degreemax       = 8,
    const double                     Tolerance3d     = 1.0e-3,
    const double                     Tolerance2d     = 1.0e-6,
    const int                        NbIterations    = 5,
    const bool                       cutting         = true,
    const Approx_ParametrizationType parametrization = Approx_ChordLength,
    const bool                       Squares         = false);

  Standard_EXPORT AppDef_BSplineCompute(const AppDef_MultiLine& Line,
                                        const math_Vector&      Parameters,
                                        const int               degreemin    = 4,
                                        const int               degreemax    = 8,
                                        const double            Tolerance3d  = 1.0e-03,
                                        const double            Tolerance2d  = 1.0e-06,
                                        const int               NbIterations = 5,
                                        const bool              cutting      = true,
                                        const bool              Squares      = false);

  Standard_EXPORT AppDef_BSplineCompute(const math_Vector& Parameters,
                                        const int          degreemin    = 4,
                                        const int          degreemax    = 8,
                                        const double       Tolerance3d  = 1.0e-03,
                                        const double       Tolerance2d  = 1.0e-06,
                                        const int          NbIterations = 5,
                                        const bool         cutting      = true,
                                        const bool         Squares      = false);

  Standard_EXPORT AppDef_BSplineCompute(
    const int                        degreemin       = 4,
    const int                        degreemax       = 8,
    const double                     Tolerance3d     = 1.0e-03,
    const double                     Tolerance2d     = 1.0e-06,
    const int                        NbIterations    = 5,
    const bool                       cutting         = true,
    const Approx_ParametrizationType parametrization = Approx_ChordLength,
    const bool                       Squares         = false);

  Standard_EXPORT void Interpol(const AppDef_MultiLine& Line);

  Standard_EXPORT void Init(const int                        degreemin       = 4,
                            const int                        degreemax       = 8,
                            const double                     Tolerance3d     = 1.0e-03,
                            const double                     Tolerance2d     = 1.0e-06,
                            const int                        NbIterations    = 5,
                            const bool                       cutting         = true,
                            const Approx_ParametrizationType parametrization = Approx_ChordLength,
                            const bool                       Squares         = false);

  Standard_EXPORT void Perform(const AppDef_MultiLine& Line);

  Standard_EXPORT void SetParameters(const math_Vector& ThePar);

  Standard_EXPORT void SetKnots(const NCollection_Array1<double>& Knots);

  Standard_EXPORT void SetKnotsAndMultiplicities(const NCollection_Array1<double>& Knots,
                                                 const NCollection_Array1<int>&    Mults);

  Standard_EXPORT void SetDegrees(const int degreemin, const int degreemax);

  Standard_EXPORT void SetTolerances(const double Tolerance3d, const double Tolerance2d);

  Standard_EXPORT void SetContinuity(const int C);

  Standard_EXPORT void SetConstraints(const AppParCurves_Constraint firstC,
                                      const AppParCurves_Constraint lastC);

  Standard_EXPORT void SetPeriodic(const bool thePeriodic);

  Standard_EXPORT bool IsAllApproximated() const;

  Standard_EXPORT bool IsToleranceReached() const;

  Standard_EXPORT void Error(double& tol3d, double& tol2d) const;

  Standard_EXPORT const AppParCurves_MultiBSpCurve& Value() const;

  Standard_EXPORT AppParCurves_MultiBSpCurve& ChangeValue();

  Standard_EXPORT const NCollection_Array1<double>& Parameters() const;

private:
  Standard_EXPORT bool Compute(const AppDef_MultiLine&           Line,
                               const int                         fpt,
                               const int                         lpt,
                               math_Vector&                      Para,
                               const NCollection_Array1<double>& Knots,
                               NCollection_Array1<int>&          Mults);

  Standard_EXPORT bool ComputeCurve(const AppDef_MultiLine& Line,
                                    const int               firspt,
                                    const int               lastpt);

  Standard_EXPORT void Parameters(const AppDef_MultiLine& Line,
                                  const int               firstP,
                                  const int               LastP,
                                  math_Vector&            TheParameters) const;

  Standard_EXPORT double SearchFirstLambda(const AppDef_MultiLine&           Line,
                                           const math_Vector&                Para,
                                           const NCollection_Array1<double>& Knots,
                                           const math_Vector&                V,
                                           const int                         index) const;

  Standard_EXPORT double SearchLastLambda(const AppDef_MultiLine&           Line,
                                          const math_Vector&                Para,
                                          const NCollection_Array1<double>& Knots,
                                          const math_Vector&                V,
                                          const int                         index) const;

  Standard_EXPORT void TangencyVector(const AppDef_MultiLine&        Line,
                                      const AppParCurves_MultiCurve& C,
                                      const double                   U,
                                      math_Vector&                   V) const;

  Standard_EXPORT void FirstTangencyVector(const AppDef_MultiLine& Line,
                                           const int               index,
                                           math_Vector&            V) const;

  Standard_EXPORT void LastTangencyVector(const AppDef_MultiLine& Line,
                                          const int               index,
                                          math_Vector&            V) const;

  Standard_EXPORT void FindRealConstraints(const AppDef_MultiLine& Line);

  AppParCurves_MultiBSpCurve                                      TheMultiBSpCurve;
  bool                                                            alldone;
  bool                                                            tolreached;
  Approx_ParametrizationType                                      Par;
  occ::handle<NCollection_HArray1<double>>                        myParameters;
  occ::handle<NCollection_HArray1<double>>                        myfirstParam;
  occ::handle<NCollection_HArray1<double>>                        myknots;
  occ::handle<NCollection_HArray1<int>>                           mymults;
  bool                                                            myhasknots;
  bool                                                            myhasmults;
  occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>> myConstraints;
  int                                                             mydegremin;
  int                                                             mydegremax;
  double                                                          mytol3d;
  double                                                          mytol2d;
  double                                                          currenttol3d;
  double                                                          currenttol2d;
  bool                                                            mycut;
  bool                                                            mysquares;
  int                                                             myitermax;
  AppParCurves_Constraint                                         myfirstC;
  AppParCurves_Constraint                                         mylastC;
  AppParCurves_Constraint                                         realfirstC;
  AppParCurves_Constraint                                         reallastC;
  int                                                             mycont;
  double                                                          mylambda1;
  double                                                          mylambda2;
  bool                                                            myPeriodic;
};
