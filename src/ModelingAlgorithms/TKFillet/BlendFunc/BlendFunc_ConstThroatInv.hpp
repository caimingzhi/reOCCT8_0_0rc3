#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_GenChamfInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BlendFunc_ConstThroatInv : public BlendFunc_GenChamfInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ConstThroatInv(const occ::handle<Adaptor3d_Surface>& S1,
                                           const occ::handle<Adaptor3d_Surface>& S2,
                                           const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  using Blend_FuncInv::Set;

  Standard_EXPORT void Set(const double theThroat, const double, const int Choix) override;

protected:
  double Throat;

  double param;
  double sign1;
  double sign2;

  gp_Pnt ptgui;
  gp_Vec nplan;
  double normtg;
  double theD;
  gp_Vec d1gui;
  gp_Vec d2gui;

  gp_Pnt pts1;
  gp_Pnt pts2;
  gp_Vec d1u1;
  gp_Vec d1v1;
  gp_Vec d1u2;
  gp_Vec d1v2;
};
