#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_FunctionTanCuPnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//=========================================================================
//  soit P1 le point sur la courbe Geom2dAdaptor_Curve d abscisse u.      +
//  soit C  le point ThePoint.                                            +
//  Nous cherchons donc les zeros de la fonction suivante:                +
//                                                                        +
//                 -->   -->                                              +
//                 CP1 /\ T                                               +
//             ---------------  =  F(u)                                   +
//             ||CP1|| * ||T||                                            +
//                                                                        +
//  La derivee de cette fonction est :                                    +
//            CP1 /\ N        (T.N)*((CP1/\T).((CP1/\T))                  +
//     f(u) = --------  -  --------------------------------               +
//               N.N            N*N*N*CP1*CP1*CP1                         +
//=========================================================================
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

  //  std::cout  << "U = "<< X << " F ="<< Fval <<" DF ="<< Deriv<<std::endl;

  return true;
}
