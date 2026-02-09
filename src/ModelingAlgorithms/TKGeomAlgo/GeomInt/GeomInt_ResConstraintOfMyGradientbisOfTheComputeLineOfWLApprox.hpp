#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <NCollection_HArray1.hpp>
class Standard_OutOfRange;
class GeomInt_TheMultiLineOfWLApprox;
class GeomInt_TheMultiLineToolOfWLApprox;
class AppParCurves_MultiCurve;
class math_Matrix;

class GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox(
    const GeomInt_TheMultiLineOfWLApprox&                                  SSP,
    AppParCurves_MultiCurve&                                               SCurv,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& Constraints,
    const math_Matrix&                                                     Bern,
    const math_Matrix&                                                     DerivativeBern,
    const double                                                           Tolerance = 1.0e-10);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double Error() const;

  Standard_EXPORT const math_Matrix& ConstraintMatrix() const;

  Standard_EXPORT const math_Vector& Duale() const;

  Standard_EXPORT const math_Matrix& ConstraintDerivative(const GeomInt_TheMultiLineOfWLApprox& SSP,
                                                          const math_Vector& Parameters,
                                                          const int          Deg,
                                                          const math_Matrix& DA);

  Standard_EXPORT const math_Matrix& InverseMatrix() const;

protected:
  Standard_EXPORT int NbConstraints(
    const GeomInt_TheMultiLineOfWLApprox&                                  SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints) const;

  Standard_EXPORT int NbColumns(const GeomInt_TheMultiLineOfWLApprox& SSP, const int Deg) const;

private:
  bool                    Done;
  double                  Err;
  math_Matrix             Cont;
  math_Matrix             DeCont;
  math_Vector             Secont;
  math_Matrix             CTCinv;
  math_Vector             Vardua;
  int                     IncPass;
  int                     IncTan;
  int                     IncCurv;
  NCollection_Array1<int> IPas;
  NCollection_Array1<int> ITan;
  NCollection_Array1<int> ICurv;
};
