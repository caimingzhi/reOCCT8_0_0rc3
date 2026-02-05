#pragma once

#include <math_Function.hpp>
#include <math_MultipleVarFunction.hpp>
#include <Adaptor3d_Curve.hpp>

//! Class to define function, which calculates square distance between point on curve
//! C(u), U1 <= u <= U2 and line passing through points C(U1) and C(U2)
//! This function is used in any minimization algorithm to define maximal deviation between curve
//! and line, which required one variable function without derivative (for ex. math_BrentMinimum)
class GCPnts_DistFunction : public math_Function
{
public:
  Standard_EXPORT GCPnts_DistFunction(const Adaptor3d_Curve& theCurve,
                                      const double           U1,
                                      const double           U2);
  //
  Standard_EXPORT GCPnts_DistFunction(const GCPnts_DistFunction& theOther);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  GCPnts_DistFunction& operator=(const GCPnts_DistFunction& theOther);

  const Adaptor3d_Curve& myCurve;
  gp_Lin                 myLin;
  double                 myU1;
  double                 myU2;
};

//
//! The same as class GCPnts_DistFunction, but it can be used in minimization algorithms that
//! requires multi variable function
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

//
