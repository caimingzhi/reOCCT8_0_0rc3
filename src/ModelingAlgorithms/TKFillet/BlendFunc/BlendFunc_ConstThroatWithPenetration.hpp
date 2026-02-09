#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_ConstThroat.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

class math_Matrix;

class BlendFunc_ConstThroatWithPenetration : public BlendFunc_ConstThroat
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ConstThroatWithPenetration(const occ::handle<Adaptor3d_Surface>& S1,
                                                       const occ::handle<Adaptor3d_Surface>& S2,
                                                       const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT const gp_Vec& TangentOnS1() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS1() const override;

  Standard_EXPORT const gp_Vec& TangentOnS2() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS2() const override;

  Standard_EXPORT double GetSectionSize() const override;
};
