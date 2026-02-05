#include <IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter.hpp>

#include <Adaptor3d_Curve.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntCurveSurface_TheHCurveTool.hpp>
#include <gp_Vec.hpp>

IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter::
  IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter(const IntSurf_Quadric&              Q,
                                                          const occ::handle<Adaptor3d_Curve>& C)
    : myQuadric(Q),
      myCurve(C)
{
}

bool IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter::Value(const double Param, double& F)
{
  F = myQuadric.Distance(IntCurveSurface_TheHCurveTool::Value(myCurve, Param));
  return (true);
}

bool IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter::Derivative(const double Param,
                                                                         double&      D)
{
  gp_Pnt P;
  gp_Vec T;
  IntCurveSurface_TheHCurveTool::D1(myCurve, Param, P, T);
  D = T.Dot(myQuadric.Gradient(P));
  return (true);
}

bool IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter::Values(const double Param,
                                                                     double&      F,
                                                                     double&      D)
{
  gp_Pnt P;
  gp_Vec T, Grad;
  IntCurveSurface_TheHCurveTool::D1(myCurve, Param, P, T);
  myQuadric.ValAndGrad(P, F, Grad);
  D = T.Dot(Grad);
  return (true);
}
