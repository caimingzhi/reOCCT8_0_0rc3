#include <HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf.hpp>

#include <IntSurf_Quadric.hpp>
#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <gp_Vec.hpp>

HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf::
  HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf(const IntSurf_Quadric& Q, const gp_Lin& C)
    : myQuadric(Q),
      myCurve(C)
{
}

bool HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf::Value(const double Param, double& F)
{
  F = myQuadric.Distance(HLRBRep_LineTool::Value(myCurve, Param));
  return (true);
}

bool HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf::Derivative(const double Param, double& D)
{
  gp_Pnt P;
  gp_Vec T;
  HLRBRep_LineTool::D1(myCurve, Param, P, T);
  D = T.Dot(myQuadric.Gradient(P));
  return (true);
}

bool HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf::Values(const double Param,
                                                                 double&      F,
                                                                 double&      D)
{
  gp_Pnt P;
  gp_Vec T, Grad;
  HLRBRep_LineTool::D1(myCurve, Param, P, T);
  myQuadric.ValAndGrad(P, F, Grad);
  D = T.Dot(Grad);
  return (true);
}
