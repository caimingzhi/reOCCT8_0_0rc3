#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>

enum Geom2dGcc_Type2
{
  Geom2dGcc_CuCuOnCu,
  Geom2dGcc_CiCuOnCu,
  Geom2dGcc_LiCuOnCu,
  Geom2dGcc_CuPtOnCu,
  Geom2dGcc_CuCuOnLi,
  Geom2dGcc_CiCuOnLi,
  Geom2dGcc_LiCuOnLi,
  Geom2dGcc_CuPtOnLi,
  Geom2dGcc_CuCuOnCi,
  Geom2dGcc_CiCuOnCi,
  Geom2dGcc_LiCuOnCi,
  Geom2dGcc_CuPtOnCi
};

#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class gp_Vec2d;
class math_Matrix;

class Geom2dGcc_FunctionTanCuCuOnCu : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Circ2d&           OnCi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Circ2d&           C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Circ2d&           OnCi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Lin2d&            L1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Circ2d&           OnCi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const gp_Pnt2d&            P2,
                                                const gp_Circ2d&           OnCi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Lin2d&            OnLi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Circ2d&           C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Lin2d&            OnLi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Lin2d&            L1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const gp_Lin2d&            OnLi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const gp_Pnt2d&            P2,
                                                const gp_Lin2d&            OnLi,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const Geom2dAdaptor_Curve& OnCu,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Circ2d&           C1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const Geom2dAdaptor_Curve& OnCu,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const gp_Lin2d&            L1,
                                                const Geom2dAdaptor_Curve& C2,
                                                const Geom2dAdaptor_Curve& OnCu,
                                                const double               Rad);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuOnCu(const Geom2dAdaptor_Curve& C1,
                                                const gp_Pnt2d&            P1,
                                                const Geom2dAdaptor_Curve& OnCu,
                                                const double               Rad);

  Standard_EXPORT void InitDerivative(const math_Vector& X,
                                      gp_Pnt2d&          Point1,
                                      gp_Pnt2d&          Point2,
                                      gp_Pnt2d&          Point3,
                                      gp_Vec2d&          Tan1,
                                      gp_Vec2d&          Tan2,
                                      gp_Vec2d&          Tan3,
                                      gp_Vec2d&          D21,
                                      gp_Vec2d&          D22,
                                      gp_Vec2d&          D23);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

private:
  Geom2dAdaptor_Curve Curv1;
  Geom2dAdaptor_Curve Curv2;
  gp_Circ2d           Circ1;
  gp_Lin2d            Lin1;
  gp_Pnt2d            Pnt2;
  gp_Circ2d           Circon;
  gp_Lin2d            Linon;
  Geom2dAdaptor_Curve Curvon;
  double              FirstRad;
  Geom2dGcc_Type2     TheType;
};
