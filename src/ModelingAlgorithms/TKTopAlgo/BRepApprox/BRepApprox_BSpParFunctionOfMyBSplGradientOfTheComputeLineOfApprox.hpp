#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>
#include <math_IntegerVector.hpp>
#include <AppParCurves_Constraint.hpp>
class BRepApprox_TheMultiLineOfApprox;
class BRepApprox_TheMultiLineToolOfApprox;
class BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox;
class AppParCurves_MultiBSpCurve;
class math_Matrix;

class BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox
    : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox(
    const BRepApprox_TheMultiLineOfApprox&                                 SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const math_Vector&                                                     Parameters,
    const NCollection_Array1<double>&                                      Knots,
    const NCollection_Array1<int>&                                         Mults,
    const int                                                              NbPol);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

  Standard_EXPORT const math_Vector& NewParameters() const;

  Standard_EXPORT AppParCurves_MultiBSpCurve CurveValue();

  Standard_EXPORT double Error(const int IPoint, const int CurveIndex);

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT double MaxError2d() const;

  Standard_EXPORT const math_Matrix& FunctionMatrix() const;

  Standard_EXPORT const math_Matrix& DerivativeFunctionMatrix() const;

  Standard_EXPORT const math_IntegerVector& Index() const;

  Standard_EXPORT AppParCurves_Constraint FirstConstraint(
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const int                                                              FirstPoint) const;

  Standard_EXPORT AppParCurves_Constraint LastConstraint(
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const int                                                              LastPoint) const;

  Standard_EXPORT void SetFirstLambda(const double l1);

  Standard_EXPORT void SetLastLambda(const double l2);

protected:
  Standard_EXPORT void Perform(const math_Vector& X);

private:
  bool                                                                 Done;
  BRepApprox_TheMultiLineOfApprox                                      MyMultiLine;
  AppParCurves_MultiBSpCurve                                           MyMultiBSpCurve;
  int                                                                  nbpoles;
  math_Vector                                                          myParameters;
  double                                                               FVal;
  math_Vector                                                          ValGrad_F;
  math_Matrix                                                          MyF;
  math_Matrix                                                          PTLX;
  math_Matrix                                                          PTLY;
  math_Matrix                                                          PTLZ;
  math_Matrix                                                          A;
  math_Matrix                                                          DA;
  BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox MyLeastSquare;
  bool                                                                 Contraintes;
  int                                                                  NbP;
  int                                                                  NbCu;
  int                                                                  Adeb;
  int                                                                  Afin;
  occ::handle<NCollection_HArray1<int>>                                tabdim;
  double                                                               ERR3d;
  double                                                               ERR2d;
  int                                                                  FirstP;
  int                                                                  LastP;
  occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>      myConstraints;
  double                                                               mylambda1;
  double                                                               mylambda2;
};
