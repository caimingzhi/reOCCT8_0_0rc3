#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class math_Matrix;
class gp_Pnt2d;

class ProjLib_PrjFunc : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_PrjFunc(const Adaptor3d_Curve*   C,
                                  const double             FixVal,
                                  const Adaptor3d_Surface* S,
                                  const int                Fix);

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

  //! returns point on surface
  Standard_EXPORT gp_Pnt2d Solution() const;

private:
  const Adaptor3d_Curve*   myCurve;
  const Adaptor3d_Surface* mySurface;
  double                   myt;
  double                   myU;
  double                   myV;
  int                      myFix;
  double                   myNorm;
};

