#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_FunctionTanCuPnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

Geom2dGcc_FunctionTanCuPnt::Geom2dGcc_FunctionTanCuPnt(const Geom2dAdaptor_Curve& C,
                                                       const gp_Pnt2d&            Point)
{
  TheCurv  = C;
  ThePoint = Point;
}

bool Geom2dGcc_FunctionTanCuPnt::Value(const double X, double& Fval)
{
  gp_Pnt2d Point;
  gp_Vec2d Vect;
  Geom2dGcc_CurveTool::D1(TheCurv, X, Point, Vect);
  double   NormeD1 = Vect.Magnitude();
  gp_Vec2d TheDirection(ThePoint, Point);
  double   NormeDir = TheDirection.Magnitude();
  Fval              = TheDirection.Crossed(Vect) / (NormeD1 * NormeDir);
  return true;
}

bool Geom2dGcc_FunctionTanCuPnt::Derivative(const double X, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vec1;
  gp_Vec2d Vec2;
  Geom2dGcc_CurveTool::D2(TheCurv, X, Point, Vec1, Vec2);
  gp_Vec2d TheDirection(ThePoint.XY(), gp_XY(Point.XY()));
  double   NormeD1  = Vec1.Magnitude();
  double   NormeDir = TheDirection.Magnitude();
  Deriv =
    TheDirection.Crossed(Vec2) / (NormeD1 * NormeDir)
    - (TheDirection.Crossed(Vec1) / (NormeD1 * NormeDir))
        * (Vec1.Dot(Vec2) / (NormeD1 * NormeD1) + Vec1.Dot(TheDirection) / (NormeDir * NormeDir));
  return true;
}

bool Geom2dGcc_FunctionTanCuPnt::Values(const double X, double& Fval, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vec1;
  gp_Vec2d Vec2;
  Geom2dGcc_CurveTool::D2(TheCurv, X, Point, Vec1, Vec2);
  gp_Vec2d TheDirection(ThePoint.XY(), gp_XY(Point.XY()));
  double   NormeD1  = Vec1.Magnitude();
  double   NormeDir = TheDirection.Magnitude();
  Fval              = TheDirection.Crossed(Vec1) / (NormeD1 * NormeDir);
  Deriv =
    TheDirection.Crossed(Vec2) / (NormeD1 * NormeDir)
    - (TheDirection.Crossed(Vec1) / (NormeD1 * NormeDir))
        * (Vec1.Dot(Vec2) / (NormeD1 * NormeD1) + Vec1.Dot(TheDirection) / (NormeDir * NormeDir));

  return true;
}
