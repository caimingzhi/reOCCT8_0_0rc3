#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>

enum Geom2dGcc_Type1
{
  Geom2dGcc_CuCuCu,
  Geom2dGcc_CiCuCu,
  Geom2dGcc_CiCiCu,
  Geom2dGcc_CiLiCu,
  Geom2dGcc_LiLiCu,
  Geom2dGcc_LiCuCu
};

#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class gp_Pnt2d;
class gp_Vec2d;
class math_Matrix;

//! This abstract class describes a set on N Functions of
//! M independent variables.
class Geom2dGcc_FunctionTanCuCuCu : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const Geom2dAdaptor_Curve& C1,
                                              const Geom2dAdaptor_Curve& C2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Circ2d&           C1,
                                              const Geom2dAdaptor_Curve& C2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Circ2d&           C1,
                                              const gp_Circ2d&           C2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Circ2d&           C1,
                                              const gp_Lin2d&            L2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Lin2d&            L1,
                                              const gp_Lin2d&            L2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Lin2d&            L1,
                                              const Geom2dAdaptor_Curve& C2,
                                              const Geom2dAdaptor_Curve& C3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Circ2d&           C1,
                                              const Geom2dAdaptor_Curve& C2,
                                              const gp_Pnt2d&            P3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const gp_Lin2d&            L1,
                                              const Geom2dAdaptor_Curve& C2,
                                              const gp_Pnt2d&            P3);

  Standard_EXPORT Geom2dGcc_FunctionTanCuCuCu(const Geom2dAdaptor_Curve& C1,
                                              const gp_Pnt2d&            P2,
                                              const gp_Pnt2d&            P3);

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

  //! Returns the number of variables of the function.
  Standard_EXPORT int NbVariables() const override;

  //! Returns the number of equations of the function.
  Standard_EXPORT int NbEquations() const override;

  //! Computes the values of the Functions for the variable <X>.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  //! Returns the values of the derivatives for the variable <X>.
  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  //! Returns the values of the functions and the derivatives
  //! for the variable <X>.
  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

private:
  Geom2dAdaptor_Curve Curv1;
  Geom2dAdaptor_Curve Curv2;
  Geom2dAdaptor_Curve Curv3;
  gp_Circ2d           Circ1;
  gp_Circ2d           Circ2;
  gp_Lin2d            Lin1;
  gp_Lin2d            Lin2;
  Geom2dGcc_Type1     TheType;
};
