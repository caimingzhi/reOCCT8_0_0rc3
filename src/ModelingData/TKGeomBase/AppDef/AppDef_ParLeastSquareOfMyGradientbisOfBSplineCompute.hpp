#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_Constraint.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
#include <Standard_Real.hpp>
class StdFail_NotDone;
class Standard_OutOfRange;
class Standard_DimensionError;
class Standard_NoSuchObject;
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppParCurves_MultiCurve;
class AppParCurves_MultiBSpCurve;
class math_Matrix;

class AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute(
    const AppDef_MultiLine&       SSP,
    const int                     FirstPoint,
    const int                     LastPoint,
    const AppParCurves_Constraint FirstCons,
    const AppParCurves_Constraint LastCons,
    const math_Vector&            Parameters,
    const int                     NbPol);

  Standard_EXPORT AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute(
    const AppDef_MultiLine&       SSP,
    const int                     FirstPoint,
    const int                     LastPoint,
    const AppParCurves_Constraint FirstCons,
    const AppParCurves_Constraint LastCons,
    const int                     NbPol);

  Standard_EXPORT AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute(
    const AppDef_MultiLine&           SSP,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const int                         FirstPoint,
    const int                         LastPoint,
    const AppParCurves_Constraint     FirstCons,
    const AppParCurves_Constraint     LastCons,
    const math_Vector&                Parameters,
    const int                         NbPol);

  Standard_EXPORT AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute(
    const AppDef_MultiLine&           SSP,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const int                         FirstPoint,
    const int                         LastPoint,
    const AppParCurves_Constraint     FirstCons,
    const AppParCurves_Constraint     LastCons,
    const int                         NbPol);

  Standard_EXPORT void Perform(const math_Vector& Parameters);

  Standard_EXPORT void Perform(const math_Vector& Parameters, const double l1, const double l2);

  Standard_EXPORT void Perform(const math_Vector& Parameters,
                               const math_Vector& V1t,
                               const math_Vector& V2t,
                               const double       l1,
                               const double       l2);

  Standard_EXPORT void Perform(const math_Vector& Parameters,
                               const math_Vector& V1t,
                               const math_Vector& V2t,
                               const math_Vector& V1c,
                               const math_Vector& V2c,
                               const double       l1,
                               const double       l2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT AppParCurves_MultiCurve BezierValue();

  Standard_EXPORT const AppParCurves_MultiBSpCurve& BSplineValue();

  Standard_EXPORT const math_Matrix& FunctionMatrix() const;

  Standard_EXPORT const math_Matrix& DerivativeFunctionMatrix() const;

  Standard_EXPORT void ErrorGradient(math_Vector& Grad, double& F, double& MaxE3d, double& MaxE2d);

  Standard_EXPORT const math_Matrix& Distance();

  Standard_EXPORT void Error(double& F, double& MaxE3d, double& MaxE2d);

  Standard_EXPORT double FirstLambda() const;

  Standard_EXPORT double LastLambda() const;

  Standard_EXPORT const math_Matrix& Points() const;

  Standard_EXPORT const math_Matrix& Poles() const;

  Standard_EXPORT const math_IntegerVector& KIndex() const;

protected:
  Standard_EXPORT void Init(const AppDef_MultiLine& SSP, const int FirstPoint, const int LastPoint);

  Standard_EXPORT int NbBColumns(const AppDef_MultiLine& SSP) const;

  Standard_EXPORT int TheFirstPoint(const AppParCurves_Constraint FirstCons,
                                    const int                     FirstPoint) const;

  Standard_EXPORT int TheLastPoint(const AppParCurves_Constraint LastCons,
                                   const int                     LastPoint) const;

  Standard_EXPORT void Affect(const AppDef_MultiLine&  SSP,
                              const int                Index,
                              AppParCurves_Constraint& Cons,
                              math_Vector&             Vt,
                              math_Vector&             Vc);

  Standard_EXPORT void ComputeFunction(const math_Vector& Parameters);

  Standard_EXPORT void SearchIndex(math_IntegerVector& Index);

  Standard_EXPORT void MakeTAA(math_Vector& TheA, math_Vector& TheB);

  Standard_EXPORT void MakeTAA(math_Vector& TheA);

  Standard_EXPORT void MakeTAA(math_Vector& TheA, math_Matrix& TheB);

private:
  AppParCurves_Constraint                  FirstConstraint;
  AppParCurves_Constraint                  LastConstraint;
  AppParCurves_MultiBSpCurve               SCU;
  occ::handle<NCollection_HArray1<double>> myknots;
  occ::handle<NCollection_HArray1<int>>    mymults;
  math_Matrix                              mypoles;
  math_Matrix                              A;
  math_Matrix                              DA;
  math_Matrix                              B2;
  math_Matrix                              mypoints;
  math_Vector                              Vflatknots;
  math_Vector                              Vec1t;
  math_Vector                              Vec1c;
  math_Vector                              Vec2t;
  math_Vector                              Vec2c;
  math_Matrix                              theError;
  math_IntegerVector                       myindex;
  double                                   lambda1;
  double                                   lambda2;
  int                                      FirstP;
  int                                      LastP;
  int                                      Nlignes;
  int                                      Ninc;
  int                                      NA;
  int                                      myfirstp;
  int                                      mylastp;
  int                                      resinit;
  int                                      resfin;
  int                                      nbP2d;
  int                                      nbP;
  int                                      nbpoles;
  int                                      deg;
  bool                                     done;
  bool                                     iscalculated;
  bool                                     isready;
};
