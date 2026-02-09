

#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_XY.hpp>
#include <IntAna2d_Conic.hpp>

IntAna2d_Conic::IntAna2d_Conic(const gp_Lin2d& L)
{

  a = 0.0;
  b = 0.0;
  c = 0.0;
  L.Coefficients(d, e, f);
  f = 2 * f;
}

IntAna2d_Conic::IntAna2d_Conic(const gp_Circ2d& C)
{

  C.Coefficients(a, b, c, d, e, f);
}

IntAna2d_Conic::IntAna2d_Conic(const gp_Elips2d& E)
{

  E.Coefficients(a, b, c, d, e, f);
}

IntAna2d_Conic::IntAna2d_Conic(const gp_Parab2d& P)
{
  P.Coefficients(a, b, c, d, e, f);
}

IntAna2d_Conic::IntAna2d_Conic(const gp_Hypr2d& H)
{
  H.Coefficients(a, b, c, d, e, f);
}

void IntAna2d_Conic::NewCoefficients(double&        A,
                                     double&        B,
                                     double&        C,
                                     double&        D,
                                     double&        E,
                                     double&        F,
                                     const gp_Ax2d& Dir1) const
{
  double t11, t12, t13;
  double t21, t22, t23;
  double A1, B1, C1, D1, E1, F1;

  Dir1.Direction().Coord(t11, t21);
  Dir1.Location().Coord(t13, t23);

  t22 = t11;
  t12 = -t21;

  A1 = (t11 * (A * t11 + 2 * C * t21) + B * t21 * t21);
  B1 = (t12 * (A * t12 + 2 * C * t22) + B * t22 * t22);
  C1 = (t12 * (A * t11 + C * t21) + t22 * (C * t11 + B * t21));
  D1 = (t11 * (D + A * t13) + t21 * (E + C * t13) + t23 * (C * t11 + B * t21));
  E1 = (t12 * (D + A * t13) + t22 * (E + C * t13) + t23 * (C * t12 + B * t22));
  F1 = F + t13 * (2.0 * D + A * t13) + t23 * (2.0 * E + 2.0 * C * t13 + B * t23);

  A = A1;
  B = B1;
  C = C1;
  D = D1;
  E = E1;
  F = F1;
}

double IntAna2d_Conic::Value(const double X, const double Y) const
{
  double _a, _b, _c, _d, _e, _f;
  this->Coefficients(_a, _b, _c, _d, _e, _f);
  return (_a * X * X + _b * Y * Y + 2. * _c * X * Y + 2. * _d * X + 2. * _e * Y + _f);
}

gp_XY IntAna2d_Conic::Grad(const double X, const double Y) const
{
  double _a, _b, _c, _d, _e, _f;
  this->Coefficients(_a, _b, _c, _d, _e, _f);
  return gp_XY(2. * _a * X + 2. * _c * Y + 2. * _d, 2. * _b * Y + 2. * _c * X + 2. * _e);
}

void IntAna2d_Conic::ValAndGrad(const double X, const double Y, double& Val, gp_XY& Grd) const
{
  double la, lb, lc, ld, le, lf;
  this->Coefficients(la, lb, lc, ld, le, lf);
  Grd.SetCoord(2. * la * X + 2. * lc * Y + 2. * ld, 2. * lb * Y + 2. * lc * X + 2. * le);
  Val = la * X * X + lb * Y * Y + 2. * lc * X * Y + 2. * ld * X + 2. * le * Y + lf;
}

void IntAna2d_Conic::Coefficients(double& A, double& B, double& C, double& D, double& E, double& F)
  const
{
  A = a;
  B = b;
  C = c;
  D = d;
  E = e;
  F = f;
}
