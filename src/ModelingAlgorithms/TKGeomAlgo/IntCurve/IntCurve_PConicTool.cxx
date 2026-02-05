#include <ElCLib.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <IntCurve_PConic.hpp>
#include <IntCurve_PConicTool.hpp>

//----------------------------------------------------------------------
gp_Pnt2d IntCurve_PConicTool::Value(const IntCurve_PConic& PConic, const double X)
{
  switch (PConic.TypeCurve())
  {

    case GeomAbs_Line:
      return (ElCLib::LineValue(X, PConic.Axis2().XAxis()));

    case GeomAbs_Circle:
      return (ElCLib::CircleValue(X, PConic.Axis2(), PConic.Param1()));

    case GeomAbs_Ellipse:
      return (ElCLib::EllipseValue(X, PConic.Axis2(), PConic.Param1(), PConic.Param2()));

    case GeomAbs_Parabola:
      return (ElCLib::ParabolaValue(X, PConic.Axis2(), PConic.Param1()));

    default: //-- case GeomAbs_Hyperbola:
      return (ElCLib::HyperbolaValue(X, PConic.Axis2(), PConic.Param1(), PConic.Param2()));
  }
}

//----------------------------------------------------------------------
void IntCurve_PConicTool::D1(const IntCurve_PConic& PConic,
                             const double           U,
                             gp_Pnt2d&              Pt,
                             gp_Vec2d&              Tan)
{

  switch (PConic.TypeCurve())
  {

    case GeomAbs_Line:
      ElCLib::LineD1(U, PConic.Axis2().XAxis(), Pt, Tan);
      break;

    case GeomAbs_Circle:
      ElCLib::CircleD1(U, PConic.Axis2(), PConic.Param1(), Pt, Tan);
      break;

    case GeomAbs_Ellipse:
      ElCLib::EllipseD1(U, PConic.Axis2(), PConic.Param1(), PConic.Param2(), Pt, Tan);
      break;

    case GeomAbs_Parabola:
      ElCLib::ParabolaD1(U, PConic.Axis2(), PConic.Param1(), Pt, Tan);
      break;

    case GeomAbs_Hyperbola:
      ElCLib::HyperbolaD1(U, PConic.Axis2(), PConic.Param1(), PConic.Param2(), Pt, Tan);
      break;
    default:
      break;
  }
}

//----------------------------------------------------------------------
void IntCurve_PConicTool::D2(const IntCurve_PConic& PConic,
                             const double           U,
                             gp_Pnt2d&              Pt,
                             gp_Vec2d&              Tan,
                             gp_Vec2d&              Norm)
{

  switch (PConic.TypeCurve())
  {

    case GeomAbs_Line:
      Tan.SetCoord(0.0, 0.0);
      ElCLib::LineD1(U, PConic.Axis2().XAxis(), Pt, Tan);
      break;

    case GeomAbs_Circle:
      ElCLib::CircleD2(U, PConic.Axis2(), PConic.Param1(), Pt, Tan, Norm);
      break;

    case GeomAbs_Ellipse:
      ElCLib::EllipseD2(U, PConic.Axis2(), PConic.Param1(), PConic.Param2(), Pt, Tan, Norm);
      break;

    case GeomAbs_Parabola:
      ElCLib::ParabolaD2(U, PConic.Axis2(), PConic.Param1(), Pt, Tan, Norm);
      break;

    case GeomAbs_Hyperbola:
      ElCLib::HyperbolaD2(U, PConic.Axis2(), PConic.Param1(), PConic.Param2(), Pt, Tan, Norm);
      break;
    default:
      break;
  }
}

double IntCurve_PConicTool::EpsX(const IntCurve_PConic& PConic)
{
  return (PConic.EpsX());
}

int IntCurve_PConicTool::NbSamples(const IntCurve_PConic& PConic)
{
  return (PConic.Accuracy());
}

// int IntCurve_PConicTool::NbSamples(const IntCurve_PConic& PConic,const double
// U0,const double U1) {
int IntCurve_PConicTool::NbSamples(const IntCurve_PConic& PConic, const double, const double)
{
  return (PConic.Accuracy());
}
