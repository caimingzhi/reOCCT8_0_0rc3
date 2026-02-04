#include IntCurve_TheIntersector_hxx

#include <IntRes2d_Domain.hpp>
#include <IntCurve_IConicTool.hpp>

//=================================================================================================

IntCurve_IntConicCurveGen::IntCurve_IntConicCurveGen(const gp_Circ2d&       C,
                                                     const IntRes2d_Domain& D1,
                                                     const ThePCurve&       PCurve,
                                                     const IntRes2d_Domain& D2,
                                                     const double           TolConf,
                                                     const double           Tol)
{
  if (!D1.IsClosed())
  {
    IntRes2d_Domain D(D1);
    D.SetEquivalentParameters(D1.FirstParameter(), D1.FirstParameter() + M_PI + M_PI);
    Perform(IntCurve_IConicTool(C), D, PCurve, D2, TolConf, Tol);
    //-- throw Standard_ConstructionError("Domaine incorrect");
  }
  else
  {
    Perform(IntCurve_IConicTool(C), D1, PCurve, D2, TolConf, Tol);
  }
}

//=================================================================================================

IntCurve_IntConicCurveGen::IntCurve_IntConicCurveGen(const gp_Elips2d&      E,
                                                     const IntRes2d_Domain& D1,
                                                     const ThePCurve&       PCurve,
                                                     const IntRes2d_Domain& D2,
                                                     const double           TolConf,
                                                     const double           Tol)
{
  if (!D1.IsClosed())
  {
    IntRes2d_Domain D(D1);
    D.SetEquivalentParameters(D1.FirstParameter(), D1.FirstParameter() + M_PI + M_PI);
    Perform(IntCurve_IConicTool(E), D, PCurve, D2, TolConf, Tol);
    //-- throw Standard_ConstructionError("Domaine incorrect");
  }
  else
  {
    Perform(IntCurve_IConicTool(E), D1, PCurve, D2, TolConf, Tol);
  }
}

//=================================================================================================

IntCurve_IntConicCurveGen::IntCurve_IntConicCurveGen(const gp_Parab2d&      Prb,
                                                     const IntRes2d_Domain& D1,
                                                     const ThePCurve&       PCurve,
                                                     const IntRes2d_Domain& D2,
                                                     const double           TolConf,
                                                     const double           Tol)
{

  Perform(IntCurve_IConicTool(Prb), D1, PCurve, D2, TolConf, Tol);
}

//=================================================================================================

IntCurve_IntConicCurveGen::IntCurve_IntConicCurveGen(const gp_Hypr2d&       H,
                                                     const IntRes2d_Domain& D1,
                                                     const ThePCurve&       PCurve,
                                                     const IntRes2d_Domain& D2,
                                                     const double           TolConf,
                                                     const double           Tol)
{

  Perform(IntCurve_IConicTool(H), D1, PCurve, D2, TolConf, Tol);
}

//--------------------------------------------------------------------------------
