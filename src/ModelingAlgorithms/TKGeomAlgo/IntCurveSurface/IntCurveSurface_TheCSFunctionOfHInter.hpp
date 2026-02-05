#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class Adaptor3d_HSurfaceTool;
class IntCurveSurface_TheHCurveTool;
class math_Matrix;

class IntCurveSurface_TheCSFunctionOfHInter : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_TheCSFunctionOfHInter(const occ::handle<Adaptor3d_Surface>& S,
                                                        const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT double Root() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Surface>& AuxillarSurface() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Curve>& AuxillarCurve() const;

private:
  occ::handle<Adaptor3d_Surface> surface;
  occ::handle<Adaptor3d_Curve>   curve;
  gp_Pnt                         p;
  double                         f;
};
