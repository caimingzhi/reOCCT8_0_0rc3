#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_ConstThroatInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BlendFunc_ConstThroatWithPenetrationInv : public BlendFunc_ConstThroatInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ConstThroatWithPenetrationInv(const occ::handle<Adaptor3d_Surface>& S1,
                                                          const occ::handle<Adaptor3d_Surface>& S2,
                                                          const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;
};
