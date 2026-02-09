#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Integer.hpp>
#include <Blend_CurvPointFuncInv.hpp>
#include <math_Vector.hpp>

class math_Matrix;

class BRepBlend_CurvPointRadInv : public Blend_CurvPointFuncInv
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_CurvPointRadInv(const occ::handle<Adaptor3d_Curve>& C1,
                                            const occ::handle<Adaptor3d_Curve>& C2);

  Standard_EXPORT void Set(const int Choix);

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const gp_Pnt& P) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

private:
  occ::handle<Adaptor3d_Curve> curv1;
  occ::handle<Adaptor3d_Curve> curv2;
  gp_Pnt                       point;
  int                          choix;
};
