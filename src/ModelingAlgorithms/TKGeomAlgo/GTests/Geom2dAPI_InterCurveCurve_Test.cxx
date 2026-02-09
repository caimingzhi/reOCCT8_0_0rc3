

#include <Geom2dAPI_InterCurveCurve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Dir2d.hpp>
#include <math_NewtonFunctionRoot.hpp>
#include <math_TrigonometricEquationFunction.hpp>

#include <gtest/gtest.h>

TEST(Geom2dAPI_InterCurveCurve_Test, OCC29289_EllipseIntersectionNewtonRoot)
{

  gp_Elips2d                  e1(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(gp_Dir2d::D::X)), 2., 1.);
  occ::handle<Geom2d_Ellipse> Ge1 = new Geom2d_Ellipse(e1);
  gp_Elips2d                  e2(gp_Ax2d(gp_Pnt2d(0.5, 0.5), gp_Dir2d(1., 1.)), 2., 1.);
  occ::handle<Geom2d_Ellipse> Ge2 = new Geom2d_Ellipse(e2);

  Geom2dAPI_InterCurveCurve Intersector;
  Intersector.Init(Ge1, Ge2, 1.e-7);
  EXPECT_GT(Intersector.NbPoints(), 0) << "Error: intersector found no points";

  double A, B, C, D, E;
  A = 1.875;
  B = -.75;
  C = -.5;
  D = -.25;
  E = -.25;
  math_TrigonometricEquationFunction MyF(A, B, C, D, E);

  double Tol1  = 1.e-15;
  double Eps   = 1.5e-12;
  int    Nit[] = {5, 6, 7, 6};

  double TetaPrev = 0.;
  int    i;
  for (i = 1; i <= Intersector.NbPoints(); i++)
  {
    double Teta = Intersector.Intersector().Point(i).ParamOnFirst();
    double X    = Teta - 0.1 * (Teta - TetaPrev);
    TetaPrev    = Teta;

    math_NewtonFunctionRoot Resol(MyF, X, Tol1, Eps, Nit[i - 1]);
    ASSERT_TRUE(Resol.IsDone()) << "Error: Newton is not done for " << Teta;

    double TetaNewton = Resol.Root();
    EXPECT_LE(std::abs(Teta - TetaNewton), 1.e-7) << "Error: Newton root is wrong for " << Teta;
  }
}
