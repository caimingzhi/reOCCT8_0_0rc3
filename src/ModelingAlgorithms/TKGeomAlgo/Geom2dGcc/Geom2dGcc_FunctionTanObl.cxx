#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_FunctionTanObl.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

Geom2dGcc_FunctionTanObl::Geom2dGcc_FunctionTanObl(const Geom2dAdaptor_Curve& C,
                                                   const gp_Dir2d&            Dir)
{
  TheCurv      = C;
  TheDirection = Dir;
}

bool Geom2dGcc_FunctionTanObl::Value(const double X, double& Fval)
{
  gp_Pnt2d Point;
  gp_Vec2d Vect;
  Geom2dGcc_CurveTool::D1(TheCurv, X, Point, Vect);
  double NormeD1 = Vect.Magnitude();
  Fval           = TheDirection.XY().Crossed(Vect.XY()) / NormeD1;
  return true;
}

bool Geom2dGcc_FunctionTanObl::Derivative(const double X, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vec1;
  gp_Vec2d Vec2;
  Geom2dGcc_CurveTool::D2(TheCurv, X, Point, Vec1, Vec2);
  double NormeD1 = Vec1.Magnitude();
  Deriv          = TheDirection.XY().Crossed(Vec2.XY()) / NormeD1
          - Vec1.XY().Dot(Vec2.XY()) * TheDirection.XY().Crossed(Vec1.XY()) / NormeD1;
  return true;
}

bool Geom2dGcc_FunctionTanObl::Values(const double X, double& Fval, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vec1;
  gp_Vec2d Vec2;
  Geom2dGcc_CurveTool::D2(TheCurv, X, Point, Vec1, Vec2);
  double NormeD1 = Vec1.Magnitude();
  Fval           = TheDirection.XY().Crossed(Vec1.XY()) / NormeD1;
  Deriv          = TheDirection.XY().Crossed(Vec2.XY()) / NormeD1
          - Vec1.XY().Dot(Vec2.XY()) * TheDirection.XY().Crossed(Vec1.XY()) / NormeD1;
  return true;
}
