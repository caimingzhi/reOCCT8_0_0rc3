#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_Corde.hpp>
#include <BlendFunc_GenChamfInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BlendFunc_ChamfInv : public BlendFunc_GenChamfInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ChamfInv(const occ::handle<Adaptor3d_Surface>& S1,
                                     const occ::handle<Adaptor3d_Surface>& S2,
                                     const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  using Blend_FuncInv::Set;

  Standard_EXPORT void Set(const double Dist1, const double Dist2, const int Choix) override;

private:
  BlendFunc_Corde corde1;
  BlendFunc_Corde corde2;
};
