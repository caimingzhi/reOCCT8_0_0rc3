#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Circ2d.hpp>

enum Geom2dGcc_Type3
{
  Geom2dGcc_CuCu,
  Geom2dGcc_CiCu
};

#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class gp_Pnt2d;
class gp_Vec2d;
class math_Matrix;

class Geom2dGcc_FunctionTanCuCu : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanCuCu(const Geom2dAdaptor_Curve& Curv1,
                                            const Geom2dAdaptor_Curve& Curv2);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCu(const gp_Circ2d&           Circ1,
                                            const Geom2dAdaptor_Curve& Curv2);

  Standard_EXPORT void InitDerivative(const math_Vector& X,
                                      gp_Pnt2d&          Point1,
                                      gp_Pnt2d&          Point2,
                                      gp_Vec2d&          Tan1,
                                      gp_Vec2d&          Tan2,
                                      gp_Vec2d&          D21,
                                      gp_Vec2d&          D22);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& Deriv) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& Deriv) override;

private:
  Geom2dAdaptor_Curve TheCurve1;
  Geom2dAdaptor_Curve TheCurve2;
  gp_Circ2d           TheCirc1;
  Geom2dGcc_Type3     TheType;
};
