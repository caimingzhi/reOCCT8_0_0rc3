#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_FunctionTanCirCu.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//=========================================================================
//  soit P1 le point sur la courbe Geom2dAdaptor_Curve d abscisse u.      +
//  soit C  le centre du cercle TheCirc.                                  +
//  Nous recherchons un point P2 appartenant au cercle tel que :          +
//           --->   -->                                                   +
//        *  P1P2 . CP2 = 0                                               +
//                                                                        +
//        *    -->  2    2                                                +
//           ||CP2||  = R                                                 +
//  Nous cherchons donc les zeros de la fonction suivante:                +
//                         -->  --> 2                                     +
//             -->  2    ( CP1 . T )      2                               +
//           ||CP1||  -  -----------  -  R   =  F(u)                      +
//                          --> 2                                         +
//                         ||T||                                          +
//                                                                        +
//  La derivee de cette fonction est :                                    +
//                                                                        +
//             2*(CP1.T)(CP1.N)     2*(CP1.T)*(CP1.T)*T.N                 +
//  f(u) =  -  ----------------  +  ---------------------                 +
//                  T.T                  (T.T)*(T.T)                      +
//=========================================================================
//                                                                        +
// skv: Small addition: The function and the derivative are normalized    +
//                      by an average square distance between the circle  +
//                      and the curve.                                    +
//=========================================================================
Geom2dGcc_FunctionTanCirCu::Geom2dGcc_FunctionTanCirCu(const gp_Circ2d&           Circ,
                                                       const Geom2dAdaptor_Curve& Curv)
{
  Curve   = Curv;
  TheCirc = Circ;

  //  Modified by Sergey KHROMOV - Thu Apr  5 09:51:21 2001 Begin
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
  //  Modified by Sergey KHROMOV - Thu Apr  5 09:51:25 2001 End
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
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:05 2001 Begin
  Fval /= myWeight;
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:06 2001 End
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
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:15 2001 Begin
  Deriv /= myWeight;
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:15 2001 End
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
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:28 2001 Begin
  Fval /= myWeight;
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:38:28 2001 End

  Deriv =
    -2. * (cp1dott / NormeD1) * ((TheDirection.Dot(Vect2)) - cp1dott * Vect1.Dot(Vect2) / NormeD1);
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:37:36 2001 Begin
  Deriv /= myWeight;
  //  Modified by Sergey KHROMOV - Thu Apr  5 17:37:37 2001 End
  return true;
}
