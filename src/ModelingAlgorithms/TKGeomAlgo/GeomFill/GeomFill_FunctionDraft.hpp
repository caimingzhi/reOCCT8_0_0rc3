#pragma once

#include <Adaptor3d_Surface.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class math_Matrix;
class gp_Vec;
class GeomFill_Tensor;

class GeomFill_FunctionDraft : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_FunctionDraft(const occ::handle<Adaptor3d_Surface>& S,
                                         const occ::handle<Adaptor3d_Curve>&   C);

  //! returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override;

  //! returns the number of equations of the function.
  Standard_EXPORT int NbEquations() const override;

  //! computes the values <F> of the Functions for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  //! returns the values <D> of the derivatives for the
  //! variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  //! returns the values <F> of the functions and the derivatives
  //! <D> for the variable <X>.
  //! Returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  //! returns the values <F> of the T derivatives for
  //! the parameter Param.
  Standard_EXPORT bool DerivT(const occ::handle<Adaptor3d_Curve>& C,
                              const double                        Param,
                              const double                        W,
                              const gp_Vec&                       dN,
                              const double                        teta,
                              math_Vector&                        F);

  //! returns the values <F> of the T2 derivatives for
  //! the parameter Param.
  Standard_EXPORT bool Deriv2T(const occ::handle<Adaptor3d_Curve>& C,
                               const double                        Param,
                               const double                        W,
                               const gp_Vec&                       d2N,
                               const double                        teta,
                               math_Vector&                        F);

  //! returns the values <D> of the TX derivatives for
  //! the parameter Param.
  Standard_EXPORT bool DerivTX(const gp_Vec& dN, const double teta, math_Matrix& D);

  //! returns the values <T> of the X2 derivatives for
  //! the parameter Param.
  Standard_EXPORT bool Deriv2X(const math_Vector& X, GeomFill_Tensor& T);

private:
  occ::handle<Adaptor3d_Curve>   TheCurve;
  occ::handle<Adaptor3d_Surface> TheSurface;
};
