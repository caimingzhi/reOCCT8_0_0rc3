#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>

//! This class implements function which calculate Eucluidean distance
//! between point on curve and point on other curve in case of C1 and C2 continuity is C0.
class Extrema_GlobOptFuncCCC0 : public math_MultipleVarFunction
{
public:
  Standard_EXPORT Extrema_GlobOptFuncCCC0(const Adaptor3d_Curve& C1, const Adaptor3d_Curve& C2);

  Standard_EXPORT Extrema_GlobOptFuncCCC0(const Adaptor2d_Curve2d& C1, const Adaptor2d_Curve2d& C2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

private:
  Extrema_GlobOptFuncCCC0& operator=(const Extrema_GlobOptFuncCCC0& theOther) = delete;

  const Adaptor3d_Curve *  myC1_3d, *myC2_3d;
  const Adaptor2d_Curve2d *myC1_2d, *myC2_2d;
  int                      myType;
};

//! This class implements function which calculate Eucluidean distance
//! between point on curve and point on other curve in case of C1 and C2 continuity is C1.
class Extrema_GlobOptFuncCCC1 : public math_MultipleVarFunctionWithGradient
{
public:
  Standard_EXPORT Extrema_GlobOptFuncCCC1(const Adaptor3d_Curve& C1, const Adaptor3d_Curve& C2);

  Standard_EXPORT Extrema_GlobOptFuncCCC1(const Adaptor2d_Curve2d& C1, const Adaptor2d_Curve2d& C2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

private:
  Extrema_GlobOptFuncCCC1& operator=(const Extrema_GlobOptFuncCCC1& theOther) = delete;

  const Adaptor3d_Curve *  myC1_3d, *myC2_3d;
  const Adaptor2d_Curve2d *myC1_2d, *myC2_2d;
  int                      myType;
};

//! This class implements function which calculate Eucluidean distance
//! between point on curve and point on other curve in case of C1 and C2 continuity is C2.
class Extrema_GlobOptFuncCCC2 : public math_MultipleVarFunctionWithHessian
{
public:
  Standard_EXPORT Extrema_GlobOptFuncCCC2(const Adaptor3d_Curve& C1, const Adaptor3d_Curve& C2);

  Standard_EXPORT Extrema_GlobOptFuncCCC2(const Adaptor2d_Curve2d& C1, const Adaptor2d_Curve2d& C2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& F, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X,
                              double&            F,
                              math_Vector&       G,
                              math_Matrix&       H) override;

private:
  Extrema_GlobOptFuncCCC2& operator=(const Extrema_GlobOptFuncCCC2& theOther) = delete;

  const Adaptor3d_Curve *  myC1_3d, *myC2_3d;
  const Adaptor2d_Curve2d *myC1_2d, *myC2_2d;
  int                      myType;
};
