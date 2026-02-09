

#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dGcc_CurveTool.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

double Geom2dGcc_CurveTool::EpsX(const Geom2dAdaptor_Curve& C, const double Tol)
{
  return C.Resolution(Tol);
}

int Geom2dGcc_CurveTool::NbSamples(const Geom2dAdaptor_Curve&)
{
  return 20;
}

gp_Pnt2d Geom2dGcc_CurveTool::Value(const Geom2dAdaptor_Curve& C, const double U)
{
  return C.Value(U);
}

double Geom2dGcc_CurveTool::FirstParameter(const Geom2dAdaptor_Curve& C)
{
  return C.FirstParameter();
}

double Geom2dGcc_CurveTool::LastParameter(const Geom2dAdaptor_Curve& C)
{
  return C.LastParameter();
}

void Geom2dGcc_CurveTool::D1(const Geom2dAdaptor_Curve& C, const double U, gp_Pnt2d& P, gp_Vec2d& T)
{

  C.D1(U, P, T);
}

void Geom2dGcc_CurveTool::D2(const Geom2dAdaptor_Curve& C,
                             const double               U,
                             gp_Pnt2d&                  P,
                             gp_Vec2d&                  T,
                             gp_Vec2d&                  N)
{

  C.D2(U, P, T, N);
}

void Geom2dGcc_CurveTool::D3(const Geom2dAdaptor_Curve& C,
                             const double               U,
                             gp_Pnt2d&                  P,
                             gp_Vec2d&                  T,
                             gp_Vec2d&                  N,
                             gp_Vec2d&                  dN)
{

  C.D3(U, P, T, N, dN);
}
