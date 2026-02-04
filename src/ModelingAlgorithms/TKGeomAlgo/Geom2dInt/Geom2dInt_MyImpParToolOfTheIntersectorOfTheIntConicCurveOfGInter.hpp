#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntCurve_IConicTool.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
class IntCurve_IConicTool;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;

class Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter
    : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor of the class.
  Standard_EXPORT Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter(
    const IntCurve_IConicTool& IT,
    const Adaptor2d_Curve2d&   PC);

  //! Computes the value of the signed distance between
  //! the implicit curve and the point at parameter Param
  //! on the parametrised curve.
  Standard_EXPORT bool Value(const double Param, double& F) override;

  //! Computes the derivative of the previous function at
  //! parameter Param.
  Standard_EXPORT bool Derivative(const double Param, double& D) override;

  //! Computes the value and the derivative of the function.
  Standard_EXPORT bool Values(const double Param, double& F, double& D) override;

private:
  void*               TheParCurve;
  IntCurve_IConicTool TheImpTool;
};

