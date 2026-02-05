#pragma once

#include <math_Function.hpp>
#include <math_MultipleVarFunction.hpp>
#include <Adaptor2d_Curve2d.hpp>

//! Class to define function, which calculates square distance between point on curve
//! C(u), U1 <= u <= U2 and line passing through points C(U1) and C(U2)
//! This function is used in any minimisation algorithm to define maximal deviation between curve
//! and line, which required one variable function without derivative (for ex. math_BrentMinimum)
class GCPnts_DistFunction2d : public math_Function
{
public:
  Standard_EXPORT GCPnts_DistFunction2d(const Adaptor2d_Curve2d& theCurve,
                                        const double             U1,
                                        const double             U2);
  //
  Standard_EXPORT GCPnts_DistFunction2d(const GCPnts_DistFunction2d& theOther);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  GCPnts_DistFunction2d& operator=(const GCPnts_DistFunction2d& theOther);

  const Adaptor2d_Curve2d& myCurve;
  gp_Lin2d                 myLin;
  double                   myU1;
  double                   myU2;
};

//
//! The same as class GCPnts_DistFunction2d,
//! but it can be used in minimization algorithms that
//! requires multi variable function
class GCPnts_DistFunction2dMV : public math_MultipleVarFunction
{
public:
  Standard_EXPORT GCPnts_DistFunction2dMV(GCPnts_DistFunction2d& theCurvLinDist);

  Standard_EXPORT bool Value(const math_Vector& X, double& F) override;

  Standard_EXPORT int NbVariables() const override;

private:
  GCPnts_DistFunction2dMV& operator=(const GCPnts_DistFunction2dMV& theOther) = delete;
  GCPnts_DistFunction2d&   myMaxCurvLinDist;
};

//
