#pragma once

#include <math_Function.hpp>
#include <math_MultipleVarFunction.hpp>
#include <Adaptor3d_Curve.hpp>

class GCPnts_DistFunction : public math_Function
{
public:
  Standard_EXPORT GCPnts_DistFunction(const Adaptor3d_Curve& theCurve,
                                      const double           U1,
                                      const double           U2);

  Standard_EXPORT GCPnts_DistFunction(const GCPnts_DistFunction& theOther);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  GCPnts_DistFunction& operator=(const GCPnts_DistFunction& theOther);

  const Adaptor3d_Curve& myCurve;
  gp_Lin                 myLin;
  double                 myU1;
  double                 myU2;
};

class GCPnts_DistFunctionMV : public math_MultipleVarFunction
{
public:
  Standard_EXPORT GCPnts_DistFunctionMV(GCPnts_DistFunction& theCurvLinDist);

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT int NbVariables() const override;

private:
  GCPnts_DistFunctionMV& operator=(const GCPnts_DistFunctionMV& theOther) = delete;
  GCPnts_DistFunction&   myMaxCurvLinDist;
};
