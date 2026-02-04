#pragma once


#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <Blend_SurfPointFuncInv.hpp>
#include <math_Vector.hpp>

class Law_Function;
class math_Matrix;

//! Function of reframing between a point and a surface.
//! This function is used to find a solution on a done
//! point of the curve when using SurfRstConsRad or
//! CSConstRad...
//! The vector <X> used in Value, Values and Derivatives
//! methods has to be the vector of the parametric
//! coordinates w, U, V where w is the parameter on the
//! guide line, U,V are the parametric coordinates of a
//! point on the partner surface.
class BRepBlend_SurfPointEvolRadInv : public Blend_SurfPointFuncInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_SurfPointEvolRadInv(const occ::handle<Adaptor3d_Surface>& S,
                                                const occ::handle<Adaptor3d_Curve>&   C,
                                                const occ::handle<Law_Function>&      Evol);

  Standard_EXPORT void Set(const int Choix);

  //! returns 3.
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

  //! Set the Point on which a solution has to be found.
  Standard_EXPORT void Set(const gp_Pnt& P) override;

  //! Returns in the vector Tolerance the parametric tolerance
  //! for each of the 3 variables;
  //! Tol is the tolerance used in 3d space.
  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  //! Returns in the vector InfBound the lowest values allowed
  //! for each of the 3 variables.
  //! Returns in the vector SupBound the greatest values allowed
  //! for each of the 3 variables.
  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  //! Returns true if Sol is a zero of the function.
  //! Tol is the tolerance used in 3d space.
  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

private:
  occ::handle<Adaptor3d_Surface> surf;
  occ::handle<Adaptor3d_Curve>   curv;
  gp_Pnt                         point;
  double                         ray;
  int                            choix;
  occ::handle<Law_Function>      tevol;
  double                         sg1;
};

