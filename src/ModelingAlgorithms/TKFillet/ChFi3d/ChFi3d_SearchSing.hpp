#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_FunctionWithDerivative.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;

class ChFi3d_SearchSing : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFi3d_SearchSing(const occ::handle<Geom_Curve>& C1,
                                    const occ::handle<Geom_Curve>& C2);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

private:
  occ::handle<Geom_Curve> myC1;
  occ::handle<Geom_Curve> myC2;
};
