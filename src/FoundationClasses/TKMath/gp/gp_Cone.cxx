

#include <gp_Cone.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>

void gp_Cone::Coefficients(double& A1,
                           double& A2,
                           double& A3,
                           double& B1,
                           double& B2,
                           double& B3,
                           double& C1,
                           double& C2,
                           double& C3,
                           double& D) const
{

  gp_Trsf T;
  T.SetTransformation(pos);
  double KAng = std::tan(semiAngle);
  double T11  = T.Value(1, 1);
  double T12  = T.Value(1, 2);
  double T13  = T.Value(1, 3);
  double T14  = T.Value(1, 4);
  double T21  = T.Value(2, 1);
  double T22  = T.Value(2, 2);
  double T23  = T.Value(2, 3);
  double T24  = T.Value(2, 4);
  double T31  = T.Value(3, 1) * KAng;
  double T32  = T.Value(3, 2) * KAng;
  double T33  = T.Value(3, 3) * KAng;
  double T34  = T.Value(3, 4) * KAng;
  A1          = T11 * T11 + T21 * T21 - T31 * T31;
  A2          = T12 * T12 + T22 * T22 - T32 * T32;
  A3          = T13 * T13 + T23 * T23 - T33 * T33;
  B1          = T11 * T12 + T21 * T22 - T31 * T32;
  B2          = T11 * T13 + T21 * T23 - T31 * T33;
  B3          = T12 * T13 + T22 * T23 - T32 * T33;
  C1          = T11 * T14 + T21 * T24 - T31 * (radius + T34);
  C2          = T12 * T14 + T22 * T24 - T32 * (radius + T34);
  C3          = T13 * T14 + T23 * T24 - T33 * (radius + T34);
  D           = T14 * T14 + T24 * T24 - radius * radius - T34 * T34 - 2.0 * radius * T34;
}

void gp_Cone::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Cone gp_Cone::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Cone C = *this;
  C.pos.Mirror(P);
  return C;
}

void gp_Cone::Mirror(const gp_Ax1& A1) noexcept
{
  pos.Mirror(A1);
}

gp_Cone gp_Cone::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Cone C = *this;
  C.pos.Mirror(A1);
  return C;
}

void gp_Cone::Mirror(const gp_Ax2& A2) noexcept
{
  pos.Mirror(A2);
}

gp_Cone gp_Cone::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Cone C = *this;
  C.pos.Mirror(A2);
  return C;
}
