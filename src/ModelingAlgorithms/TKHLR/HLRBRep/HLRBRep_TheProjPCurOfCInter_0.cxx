#include <HLRBRep_TheProjPCurOfCInter.hpp>

#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter.hpp>
#include <HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter.hpp>
#include <HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter.hpp>
#include <gp_Pnt2d.hpp>
#include <Extrema_POnCurv2d.hpp>

double HLRBRep_TheProjPCurOfCInter::FindParameter(const HLRBRep_CurvePtr& C,
                                                  const gp_Pnt2d&         P,
                                                  const double            LowParameter,
                                                  const double            HighParameter,
                                                  const double)
{
  double            theparam, defaultparam;
  int               NbPts   = HLRBRep_CurveTool::NbSamples(C);
  double            theEpsX = HLRBRep_CurveTool::EpsX(C);
  Extrema_POnCurv2d POnC;

  HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter::Locate(P,
                                                       C,
                                                       NbPts,
                                                       LowParameter,
                                                       HighParameter,
                                                       POnC);
  defaultparam = POnC.Parameter();
  HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter Loc(P, C, defaultparam, theEpsX);

  if (!Loc.IsDone())
  {

    theparam = defaultparam;
  }
  else
  {
    if (!Loc.IsMin())
    {

      theparam = defaultparam;
    }
    else
    {
      theparam = Loc.Point().Parameter();
    }
  }
  return theparam;
}

double HLRBRep_TheProjPCurOfCInter::FindParameter(const HLRBRep_CurvePtr& C,
                                                  const gp_Pnt2d&         P,
                                                  const double            Tol)
{

  double theParam;
  theParam = FindParameter(C,
                           P,
                           HLRBRep_CurveTool::FirstParameter(C),
                           HLRBRep_CurveTool::LastParameter(C),
                           Tol);
  return theParam;
}
