#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiCurve.hpp>
#include <NCollection_Sequence.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <Approx_ParametrizationType.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <Standard_Integer.hpp>
#include <AppParCurves_Constraint.hpp>
#include <math_Vector.hpp>
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_MyGradientOfCompute;
class AppDef_ParLeastSquareOfMyGradientOfCompute;
class AppDef_ResConstraintOfMyGradientOfCompute;
class AppDef_ParFunctionOfMyGradientOfCompute;
class AppDef_Gradient_BFGSOfMyGradientOfCompute;
class AppParCurves_MultiCurve;
class AppParCurves_MultiBSpCurve;

class AppDef_Compute
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_Compute(
    const AppDef_MultiLine&          Line,
    const int                        degreemin       = 4,
    const int                        degreemax       = 8,
    const double                     Tolerance3d     = 1.0e-3,
    const double                     Tolerance2d     = 1.0e-6,
    const int                        NbIterations    = 5,
    const bool                       cutting         = true,
    const Approx_ParametrizationType parametrization = Approx_ChordLength,
    const bool                       Squares         = false);

  Standard_EXPORT AppDef_Compute(const AppDef_MultiLine& Line,
                                 const math_Vector&      Parameters,
                                 const int               degreemin    = 4,
                                 const int               degreemax    = 8,
                                 const double            Tolerance3d  = 1.0e-03,
                                 const double            Tolerance2d  = 1.0e-06,
                                 const int               NbIterations = 5,
                                 const bool              cutting      = true,
                                 const bool              Squares      = false);

  Standard_EXPORT AppDef_Compute(const math_Vector& Parameters,
                                 const int          degreemin    = 4,
                                 const int          degreemax    = 8,
                                 const double       Tolerance3d  = 1.0e-03,
                                 const double       Tolerance2d  = 1.0e-06,
                                 const int          NbIterations = 5,
                                 const bool         cutting      = true,
                                 const bool         Squares      = false);

  Standard_EXPORT AppDef_Compute(
    const int                        degreemin       = 4,
    const int                        degreemax       = 8,
    const double                     Tolerance3d     = 1.0e-03,
    const double                     Tolerance2d     = 1.0e-06,
    const int                        NbIterations    = 5,
    const bool                       cutting         = true,
    const Approx_ParametrizationType parametrization = Approx_ChordLength,
    const bool                       Squares         = false);

  Standard_EXPORT void Init(const int                        degreemin       = 4,
                            const int                        degreemax       = 8,
                            const double                     Tolerance3d     = 1.0e-03,
                            const double                     Tolerance2d     = 1.0e-06,
                            const int                        NbIterations    = 5,
                            const bool                       cutting         = true,
                            const Approx_ParametrizationType parametrization = Approx_ChordLength,
                            const bool                       Squares         = false);

  Standard_EXPORT void Perform(const AppDef_MultiLine& Line);

  Standard_EXPORT void SetDegrees(const int degreemin, const int degreemax);

  Standard_EXPORT void SetTolerances(const double Tolerance3d, const double Tolerance2d);

  Standard_EXPORT void SetConstraints(const AppParCurves_Constraint firstC,
                                      const AppParCurves_Constraint lastC);

  Standard_EXPORT bool IsAllApproximated() const;

  Standard_EXPORT bool IsToleranceReached() const;

  Standard_EXPORT void Error(const int Index, double& tol3d, double& tol2d) const;

  Standard_EXPORT int NbMultiCurves() const;

  Standard_EXPORT const AppParCurves_MultiCurve& Value(const int Index = 1) const;

  Standard_EXPORT AppParCurves_MultiCurve& ChangeValue(const int Index = 1);

  Standard_EXPORT const AppParCurves_MultiBSpCurve& SplineValue();

  Standard_EXPORT Approx_ParametrizationType Parametrization() const;

  Standard_EXPORT const NCollection_Array1<double>& Parameters(const int Index = 1) const;

private:
  Standard_EXPORT bool Compute(const AppDef_MultiLine& Line,
                               const int               fpt,
                               const int               lpt,
                               math_Vector&            Para,
                               double&                 TheTol3d,
                               double&                 TheTol2d,
                               int&                    indbad);

  Standard_EXPORT bool ComputeCurve(const AppDef_MultiLine& Line,
                                    const int               firspt,
                                    const int               lastpt);

  Standard_EXPORT void Parameters(const AppDef_MultiLine& Line,
                                  const int               firstP,
                                  const int               LastP,
                                  math_Vector&            TheParameters) const;

  Standard_EXPORT double SearchFirstLambda(const AppDef_MultiLine& Line,
                                           const math_Vector&      Para,
                                           const math_Vector&      V,
                                           const int               index) const;

  Standard_EXPORT double SearchLastLambda(const AppDef_MultiLine& Line,
                                          const math_Vector&      Para,
                                          const math_Vector&      V,
                                          const int               index) const;

  Standard_EXPORT void FirstTangencyVector(const AppDef_MultiLine& Line,
                                           const int               index,
                                           math_Vector&            V) const;

  Standard_EXPORT void LastTangencyVector(const AppDef_MultiLine& Line,
                                          const int               index,
                                          math_Vector&            V) const;

  NCollection_Sequence<AppParCurves_MultiCurve>                   myMultiCurves;
  AppParCurves_MultiCurve                                         TheMultiCurve;
  AppParCurves_MultiBSpCurve                                      myspline;
  bool                                                            alldone;
  bool                                                            tolreached;
  Approx_ParametrizationType                                      Par;
  occ::handle<NCollection_HArray1<double>>                        myParameters;
  occ::handle<NCollection_HArray1<double>>                        myfirstParam;
  NCollection_Sequence<occ::handle<NCollection_HArray1<double>>>  myPar;
  NCollection_Sequence<double>                                    Tolers3d;
  NCollection_Sequence<double>                                    Tolers2d;
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
  int                                                             myMultiLineNb;
  bool                                                            myIsClear;
};
