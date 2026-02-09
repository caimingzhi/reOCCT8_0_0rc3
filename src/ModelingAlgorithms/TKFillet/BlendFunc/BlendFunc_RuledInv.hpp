#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Blend_FuncInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BlendFunc_RuledInv : public Blend_FuncInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_RuledInv(const occ::handle<Adaptor3d_Surface>& S1,
                                     const occ::handle<Adaptor3d_Surface>& S2,
                                     const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT void Set(const bool                            OnFirst,
                           const occ::handle<Adaptor2d_Curve2d>& COnSurf) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

private:
  occ::handle<Adaptor3d_Surface> surf1;
  occ::handle<Adaptor3d_Surface> surf2;
  occ::handle<Adaptor3d_Curve>   curv;
  occ::handle<Adaptor2d_Curve2d> csurf;
  bool                           first;
};
