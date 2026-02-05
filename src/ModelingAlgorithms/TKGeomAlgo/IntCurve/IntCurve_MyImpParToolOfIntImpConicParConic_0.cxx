#include <IntCurve_MyImpParToolOfIntImpConicParConic.hpp>

#include <IntCurve_IConicTool.hpp>
#include <IntCurve_PConic.hpp>
#include <IntCurve_PConicTool.hpp>

#include <gp_Vec2d.hpp>

IntCurve_MyImpParToolOfIntImpConicParConic::IntCurve_MyImpParToolOfIntImpConicParConic(
  const IntCurve_IConicTool& ITool,
  const IntCurve_PConic&     PC)
    : TheImpTool(ITool)
{
  TheParCurve = (void*)(&PC);
}

bool IntCurve_MyImpParToolOfIntImpConicParConic::Value(const double Param, double& ApproxDistance)
{
  ApproxDistance =
    TheImpTool.Distance(IntCurve_PConicTool::Value((*((IntCurve_PConic*)(TheParCurve))), Param));
  return (true);
}

bool IntCurve_MyImpParToolOfIntImpConicParConic::Derivative(const double Param,
                                                            double&      D_ApproxDistance_DV)
{
  gp_Pnt2d Pt;
  gp_Vec2d TanParCurve;
  gp_Vec2d Grad = TheImpTool.GradDistance(
    IntCurve_PConicTool::Value((*((IntCurve_PConic*)(TheParCurve))), Param));
  IntCurve_PConicTool::D1((*((IntCurve_PConic*)(TheParCurve))), Param, Pt, TanParCurve);
  D_ApproxDistance_DV = Grad.Dot(TanParCurve);
  return (true);
}

bool IntCurve_MyImpParToolOfIntImpConicParConic::Values(const double Param,
                                                        double&      ApproxDistance,
                                                        double&      Deriv)
{
  this->Value(Param, ApproxDistance);
  this->Derivative(Param, Deriv);
  return (true);
}
