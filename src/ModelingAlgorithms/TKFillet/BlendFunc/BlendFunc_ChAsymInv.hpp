#pragma once

#include <Adaptor3d_Surface.hpp>
#include <math_Matrix.hpp>
#include <Blend_FuncInv.hpp>

class BlendFunc_ChAsymInv : public Blend_FuncInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ChAsymInv(const occ::handle<Adaptor3d_Surface>& S1,
                                      const occ::handle<Adaptor3d_Surface>& S2,
                                      const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT void Set(const bool                            OnFirst,
                           const occ::handle<Adaptor2d_Curve2d>& COnSurf) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool ComputeValues(const math_Vector& X, const int DegF, const int DegL);

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const double Dist1, const double Angle, const int Choix);

private:
  occ::handle<Adaptor3d_Surface> surf1;
  occ::handle<Adaptor3d_Surface> surf2;
  double                         dist1;
  double                         angle;
  double                         tgang;
  occ::handle<Adaptor3d_Curve>   curv;
  occ::handle<Adaptor2d_Curve2d> csurf;
  int                            choix;
  bool                           first;
  math_Vector                    FX;
  math_Matrix                    DX;
};
