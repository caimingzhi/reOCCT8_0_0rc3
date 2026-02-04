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
class BRepApprox_TheMultiLineOfApprox;
class BRepApprox_TheMultiLineToolOfApprox;
class AppParCurves_MultiCurve;
class math_Matrix;

class BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox
{
public:
  DEFINE_STANDARD_ALLOC

  //! Given a MultiLine SSP with constraints points, this
  //! algorithm finds the best curve solution to approximate it.
  //! The poles from SCurv issued for example from the least
  //! squares are used as a guess solution for the uzawa
  //! algorithm. The tolerance used in the Uzawa algorithms
  //! is Tolerance.
  //! A is the Bernstein matrix associated to the MultiLine
  //! and DA is the derivative bernstein matrix.(They can come
  //! from an approximation with ParLeastSquare.)
  //! The MultiCurve is modified. New MultiPoles are given.
  Standard_EXPORT BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox(
    const BRepApprox_TheMultiLineOfApprox&                                 SSP,
    AppParCurves_MultiCurve&                                               SCurv,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& Constraints,
    const math_Matrix&                                                     Bern,
    const math_Matrix&                                                     DerivativeBern,
    const double                                                           Tolerance = 1.0e-10);

  //! returns True if all has been correctly done.
  Standard_EXPORT bool IsDone() const;

  //! returns the maximum difference value between the curve
  //! and the given points.
  Standard_EXPORT double Error() const;

  Standard_EXPORT const math_Matrix& ConstraintMatrix() const;

  //! returns the duale variables of the system.
  Standard_EXPORT const math_Vector& Duale() const;

  //! Returns the derivative of the constraint matrix.
  Standard_EXPORT const math_Matrix& ConstraintDerivative(
    const BRepApprox_TheMultiLineOfApprox& SSP,
    const math_Vector&                     Parameters,
    const int                              Deg,
    const math_Matrix&                     DA);

  //! returns the Inverse of Cont*Transposed(Cont), where
  //! Cont is the constraint matrix for the algorithm.
  Standard_EXPORT const math_Matrix& InverseMatrix() const;

protected:
  //! is used internally to create the fields.
  Standard_EXPORT int NbConstraints(
    const BRepApprox_TheMultiLineOfApprox&                                 SSP,
    const int                                                              FirstPoint,
    const int                                                              LastPoint,
    const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints) const;

  //! is internally used for the fields creation.
  Standard_EXPORT int NbColumns(const BRepApprox_TheMultiLineOfApprox& SSP, const int Deg) const;

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

