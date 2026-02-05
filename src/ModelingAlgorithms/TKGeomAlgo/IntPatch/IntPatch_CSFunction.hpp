#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class math_Matrix;

//! this function is associated to the intersection between
//! a curve on surface and a surface.
class IntPatch_CSFunction : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  //! S1 is the surface on which the intersection is searched.
  //! C is a curve on the surface S2.
  Standard_EXPORT IntPatch_CSFunction(const occ::handle<Adaptor3d_Surface>& S1,
                                      const occ::handle<Adaptor2d_Curve2d>& C,
                                      const occ::handle<Adaptor3d_Surface>& S2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT double Root() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Surface>& AuxillarSurface() const;

  Standard_EXPORT const occ::handle<Adaptor2d_Curve2d>& AuxillarCurve() const;

private:
  void*  curve;
  void*  surface1;
  void*  surface2;
  gp_Pnt p;
  double f;
};
