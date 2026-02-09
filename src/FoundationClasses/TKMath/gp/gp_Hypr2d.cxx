

#define No_Standard_OutOfRange

#include <gp_Hypr2d.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>

void gp_Hypr2d::Coefficients(double& A, double& B, double& C, double& D, double& E, double& F) const
{
  double DMin = minorRadius * minorRadius;
  double DMaj = majorRadius * majorRadius;
  if (DMin <= gp::Resolution() && DMaj <= gp::Resolution())
  {
    A = B = C = D = E = F = 0.0;
  }
  else
  {
    gp_Trsf2d T;
    T.SetTransformation(pos.XAxis());
    double T11 = T.Value(1, 1);
    double T12 = T.Value(1, 2);
    double T13 = T.Value(1, 3);
    if (DMin <= gp::Resolution())
    {
      A = T11 * T11;
      B = T12 * T12;
      C = T11 * T12;
      D = T11 * T13;
      E = T12 * T13;
      F = T13 * T13 - DMaj;
    }
    else
    {
      double T21 = T.Value(2, 1);
      double T22 = T.Value(2, 2);
      double T23 = T.Value(2, 3);
      A          = (T11 * T11 / DMaj) - (T21 * T21 / DMin);
      B          = (T12 * T12 / DMaj) - (T22 * T22 / DMin);
      C          = (T11 * T12 / DMaj) - (T21 * T22 / DMin);
      D          = (T11 * T13 / DMaj) - (T21 * T23 / DMin);
      E          = (T12 * T13 / DMaj) - (T22 * T23 / DMin);
      F          = (T13 * T13 / DMaj) - (T23 * T23 / DMin) - 1.0;
    }
  }
}

void gp_Hypr2d::Mirror(const gp_Pnt2d& P) noexcept
{
  pos.Mirror(P);
}

gp_Hypr2d gp_Hypr2d::Mirrored(const gp_Pnt2d& P) const noexcept
{
  gp_Hypr2d H = *this;
  H.pos.Mirror(P);
  return H;
}

void gp_Hypr2d::Mirror(const gp_Ax2d& A) noexcept
{
  pos.Mirror(A);
}

gp_Hypr2d gp_Hypr2d::Mirrored(const gp_Ax2d& A) const noexcept
{
  gp_Hypr2d H = *this;
  H.pos.Mirror(A);
  return H;
}
