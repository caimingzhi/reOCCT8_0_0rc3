#include <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>

#include <IntCurve_IConicTool.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>

#include <gp_Vec2d.hpp>

Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter::
  Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter(const IntCurve_IConicTool& ITool,
                                                                   const Adaptor2d_Curve2d&   PC)
    : TheImpTool(ITool)
{
  TheParCurve = (void*)(&PC);
}

bool Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter::Value(const double Param,
                                                                             double& ApproxDistance)
{
  ApproxDistance = TheImpTool.Distance(
    Geom2dInt_Geom2dCurveTool::Value((*((Adaptor2d_Curve2d*)(TheParCurve))), Param));
  return (true);
}

bool Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter::Derivative(
  const double Param,
  double&      D_ApproxDistance_DV)
{
  gp_Pnt2d Pt;
  gp_Vec2d TanParCurve;
  gp_Vec2d Grad = TheImpTool.GradDistance(
    Geom2dInt_Geom2dCurveTool::Value((*((Adaptor2d_Curve2d*)(TheParCurve))), Param));
  Geom2dInt_Geom2dCurveTool::D1((*((Adaptor2d_Curve2d*)(TheParCurve))), Param, Pt, TanParCurve);
  D_ApproxDistance_DV = Grad.Dot(TanParCurve);
  return (true);
}

bool Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter::Values(
  const double Param,
  double&      ApproxDistance,
  double&      Deriv)
{
  this->Value(Param, ApproxDistance);
  this->Derivative(Param, Deriv);
  return (true);
}
