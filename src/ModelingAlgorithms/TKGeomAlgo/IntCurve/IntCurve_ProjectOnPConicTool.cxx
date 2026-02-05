#include <ElCLib.hpp>
#include <gp_Pnt2d.hpp>
#include <IntCurve_PConic.hpp>
#include <IntCurve_ProjectOnPConicTool.hpp>

double IntCurve_ProjectOnPConicTool::FindParameter(const IntCurve_PConic& ThePConic,
                                                   const gp_Pnt2d&        P,
                                                   const double           LowParameter,
                                                   const double           HighParameter,
                                                   const double)
{

  double ParamSup, ParamInf, Param = 0;
  if (LowParameter > HighParameter)
  {
    ParamSup = LowParameter;
    ParamInf = HighParameter;
  }
  else
  {
    ParamInf = LowParameter;
    ParamSup = HighParameter;
  }

  switch (ThePConic.TypeCurve())
  {

    case GeomAbs_Line:
      Param = ElCLib::LineParameter(ThePConic.Axis2().XAxis(), P);
      break;

    case GeomAbs_Circle:
      Param = ElCLib::CircleParameter(ThePConic.Axis2(), P);
      if (Param < 0.0)
      {
        Param += M_PI + M_PI;
      }
      break;

    case GeomAbs_Ellipse:
    {
      Param =
        ElCLib::EllipseParameter(ThePConic.Axis2(), ThePConic.Param1(), ThePConic.Param2(), P);
      if (Param < 0.0)
      {
        Param += M_PI + M_PI;
      }
      break;
    }

    case GeomAbs_Parabola:
    {
      Param = ElCLib::ParabolaParameter(ThePConic.Axis2(), P);
      break;
    }
    case GeomAbs_Hyperbola:
    {
      Param =
        ElCLib::HyperbolaParameter(ThePConic.Axis2(), ThePConic.Param1(), ThePConic.Param2(), P);
      break;
    }
    default:
      break;
  }
  if (ParamInf != ParamSup)
  {
    if (Param < ParamInf)
      return (ParamInf);
    if (Param > ParamSup)
      return (ParamSup);
  }
  return (Param);
}

double IntCurve_ProjectOnPConicTool::FindParameter(const IntCurve_PConic& ThePConic,
                                                   const gp_Pnt2d&        P,
                                                   const double)
{

  // std::cout<<"\n\n---- Dans ProjectOnPConicTool::FindParameter  Point : "<<P.X()<<","<<P.Y();

  double Param = 0;

  switch (ThePConic.TypeCurve())
  {

    case GeomAbs_Line:
      Param = ElCLib::LineParameter(ThePConic.Axis2().XAxis(), P);
      break;

    case GeomAbs_Circle:
      Param = ElCLib::CircleParameter(ThePConic.Axis2(), P);
      if (Param < 0.0)
      {
        Param += M_PI + M_PI;
      }
      break;

    case GeomAbs_Ellipse:
    {
      Param =
        ElCLib::EllipseParameter(ThePConic.Axis2(), ThePConic.Param1(), ThePConic.Param2(), P);
      if (Param < 0.0)
      {
        Param += M_PI + M_PI;
      }
      break;
    }

    case GeomAbs_Parabola:
    {
      Param = ElCLib::ParabolaParameter(ThePConic.Axis2(), P);
      break;
    }
    case GeomAbs_Hyperbola:
    {
      Param =
        ElCLib::HyperbolaParameter(ThePConic.Axis2(), ThePConic.Param1(), ThePConic.Param2(), P);
      break;
    }
    default:
      break;
  }

  return (Param);
}
