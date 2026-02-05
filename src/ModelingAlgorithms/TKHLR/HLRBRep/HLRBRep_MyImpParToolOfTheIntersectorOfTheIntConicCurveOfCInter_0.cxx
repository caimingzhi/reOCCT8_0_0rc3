#include <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>

#include <IntCurve_IConicTool.hpp>
#include <HLRBRep_CurveTool.hpp>

#include <gp_Vec2d.hpp>

HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter::
  HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter(const IntCurve_IConicTool& ITool,
                                                                 const HLRBRep_CurvePtr&    PC)
    : TheImpTool(ITool)
{
  TheParCurve = (HLRBRep_CurvePtr)(&PC);
}

bool HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter::Value(const double Param,
                                                                           double& ApproxDistance)
{
  ApproxDistance =
    TheImpTool.Distance(HLRBRep_CurveTool::Value((*((HLRBRep_CurvePtr*)(TheParCurve))), Param));
  return (true);
}

bool HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter::Derivative(
  const double Param,
  double&      D_ApproxDistance_DV)
{
  gp_Pnt2d Pt;
  gp_Vec2d TanParCurve;
  gp_Vec2d Grad =
    TheImpTool.GradDistance(HLRBRep_CurveTool::Value((*((HLRBRep_CurvePtr*)(TheParCurve))), Param));
  HLRBRep_CurveTool::D1((*((HLRBRep_CurvePtr*)(TheParCurve))), Param, Pt, TanParCurve);
  D_ApproxDistance_DV = Grad.Dot(TanParCurve);
  return (true);
}

bool HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter::Values(const double Param,
                                                                            double& ApproxDistance,
                                                                            double& Deriv)
{
  this->Value(Param, ApproxDistance);
  this->Derivative(Param, Deriv);
  return (true);
}
