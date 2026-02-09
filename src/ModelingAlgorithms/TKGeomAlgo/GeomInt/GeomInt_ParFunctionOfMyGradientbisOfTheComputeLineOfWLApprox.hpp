#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>
#include <AppParCurves_Constraint.hpp>
class GeomInt_TheMultiLineOfWLApprox;
class GeomInt_TheMultiLineToolOfWLApprox;
class GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox;
class GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox;
class AppParCurves_MultiCurve;

class GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox
    : public math_MultipleVarFunctionWithGradient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox(
    const GeomInt_TheMultiLineOfWLApprox&                                  SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const math_Vector&                                                     Parameters,
    const int                                                              Deg);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

  Standard_EXPORT const math_Vector& NewParameters() const;

  Standard_EXPORT const AppParCurves_MultiCurve& CurveValue();

  Standard_EXPORT double Error(const int IPoint, const int CurveIndex) const;

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT double MaxError2d() const;

  Standard_EXPORT AppParCurves_Constraint FirstConstraint(
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const int                                                              FirstPoint) const;

  Standard_EXPORT AppParCurves_Constraint LastConstraint(
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
    const int                                                              LastPoint) const;

protected:
  Standard_EXPORT void Perform(const math_Vector& X);

private:
  bool                                                            Done;
  GeomInt_TheMultiLineOfWLApprox                                  MyMultiLine;
  AppParCurves_MultiCurve                                         MyMultiCurve;
  int                                                             Degre;
  math_Vector                                                     myParameters;
  double                                                          FVal;
  math_Vector                                                     ValGrad_F;
  math_Matrix                                                     MyF;
  math_Matrix                                                     PTLX;
  math_Matrix                                                     PTLY;
  math_Matrix                                                     PTLZ;
  math_Matrix                                                     A;
  math_Matrix                                                     DA;
  GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox MyLeastSquare;
  bool                                                            Contraintes;
  int                                                             NbP;
  int                                                             NbCu;
  int                                                             Adeb;
  int                                                             Afin;
  occ::handle<NCollection_HArray1<int>>                           tabdim;
  double                                                          ERR3d;
  double                                                          ERR2d;
  int                                                             FirstP;
  int                                                             LastP;
  occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>> myConstraints;
};
