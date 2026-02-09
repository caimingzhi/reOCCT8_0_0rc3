#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_FunctionTanCirCu.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

Geom2dGcc_FunctionTanCirCu::Geom2dGcc_FunctionTanCirCu(const gp_Circ2d&           Circ,
                                                       const Geom2dAdaptor_Curve& Curv)
{
  Curve   = Curv;
  TheCirc = Circ;

  int    aNbSamp = Geom2dGcc_CurveTool::NbSamples(Curve);
  double aFirst  = Geom2dGcc_CurveTool::FirstParameter(Curve);
  double aLast   = Geom2dGcc_CurveTool::LastParameter(Curve);
  double aStep   = (aLast - aFirst) / aNbSamp;
  double anX     = aFirst + aStep / 2.;
  gp_XY  aLoc(0., 0.);

  while (anX <= aLast)
  {
    aLoc += (Geom2dGcc_CurveTool::Value(Curve, anX)).XY();
    anX += aStep;
  }
  myWeight = std::max((aLoc - TheCirc.Location().XY()).SquareModulus(), TheCirc.Radius());
}

bool Geom2dGcc_FunctionTanCirCu::Value(const double X, double& Fval)
{
  gp_Pnt2d Point;
  gp_Vec2d Vect1;
  Geom2dGcc_CurveTool::D1(Curve, X, Point, Vect1);
  double   NormeD1 = Vect1.Magnitude();
  gp_Vec2d TheDirection(TheCirc.Location(), Point);
  double   squaredir = TheDirection.Dot(TheDirection);
  double   R         = TheCirc.Radius();
  Fval =
    squaredir - R * R - (TheDirection.Dot(Vect1)) * (TheDirection.Dot(Vect1)) / (NormeD1 * NormeD1);

  Fval /= myWeight;

  return true;
}

bool Geom2dGcc_FunctionTanCirCu::Derivative(const double X, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vect1, Vect2;
  Geom2dGcc_CurveTool::D2(Curve, X, Point, Vect1, Vect2);
  double   NormeD1 = Vect1.SquareMagnitude();
  gp_Vec2d TheDirection(TheCirc.Location(), Point);
  double   cp1dott = TheDirection.Dot(Vect1);
  Deriv =
    -2. * (cp1dott / NormeD1) * ((TheDirection.Dot(Vect2)) - cp1dott * Vect1.Dot(Vect2) / NormeD1);

  Deriv /= myWeight;

  return true;
}

bool Geom2dGcc_FunctionTanCirCu::Values(const double X, double& Fval, double& Deriv)
{
  gp_Pnt2d Point;
  gp_Vec2d Vect1, Vect2;
  Geom2dGcc_CurveTool::D2(Curve, X, Point, Vect1, Vect2);
  double   NormeD1 = Vect1.SquareMagnitude();
  gp_Vec2d TheDirection(TheCirc.Location(), Point);
  double   squaredir = TheDirection.SquareMagnitude();
  double   cp1dott   = TheDirection.Dot(Vect1);
  double   R         = TheCirc.Radius();

  Fval = squaredir - R * R - cp1dott * cp1dott / NormeD1;

  Fval /= myWeight;

  Deriv =
    -2. * (cp1dott / NormeD1) * ((TheDirection.Dot(Vect2)) - cp1dott * Vect1.Dot(Vect2) / NormeD1);

  Deriv /= myWeight;

  return true;
}
