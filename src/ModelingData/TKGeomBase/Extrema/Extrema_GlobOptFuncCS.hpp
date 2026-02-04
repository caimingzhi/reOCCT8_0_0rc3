#pragma once


#include <Adaptor3d_Surface.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>

//! This class implements function which calculate square Eucluidean distance
//! between point on curve and point on surface in case of continuity is C2.
class Extrema_GlobOptFuncCS : public math_MultipleVarFunctionWithHessian
{
public:
  //! Curve and surface should exist during all the lifetime of Extrema_GlobOptFuncCS.
  Standard_EXPORT Extrema_GlobOptFuncCS(const Adaptor3d_Curve* C, const Adaptor3d_Surface* S);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& theX, double& theF) override;

  Standard_EXPORT bool Gradient(const math_Vector& theX, math_Vector& theG) override;

  Standard_EXPORT bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override;

  Standard_EXPORT bool Values(const math_Vector& theX,
                              double&            theF,
                              math_Vector&       theG,
                              math_Matrix&       theH) override;

private:
  bool checkInputData(const math_Vector& X, double& cu, double& su, double& sv);

  void value(double cu, double su, double sv, double& F);

  void gradient(double cu, double su, double sv, math_Vector& G);

  void hessian(double cu, double su, double sv, math_Matrix& H);

  Extrema_GlobOptFuncCS& operator=(const Extrema_GlobOptFuncCS& theOther) = delete;

  const Adaptor3d_Curve*   myC;
  const Adaptor3d_Surface* myS;
};

