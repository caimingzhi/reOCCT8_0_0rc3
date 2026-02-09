#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <Blend_SurfPointFuncInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BRepBlend_SurfPointConstRadInv : public Blend_SurfPointFuncInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_SurfPointConstRadInv(const occ::handle<Adaptor3d_Surface>& S,
                                                 const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT void Set(const double R, const int Choix);

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const gp_Pnt& P) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

private:
  occ::handle<Adaptor3d_Surface> surf;
  occ::handle<Adaptor3d_Curve>   curv;
  gp_Pnt                         point;
  double                         ray;
  int                            choix;
};
