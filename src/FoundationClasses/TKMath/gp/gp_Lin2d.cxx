

#define No_Standard_OutOfRange

#include <gp_Lin2d.hpp>

#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <Standard_ConstructionError.hpp>

gp_Lin2d::gp_Lin2d(const double A, const double B, const double C)
{
  const double Norm2 = A * A + B * B;
  Standard_ConstructionError_Raise_if(Norm2 <= gp::Resolution(), " ");
  const gp_Pnt2d P(-A * C / Norm2, -B * C / Norm2);
  const gp_Dir2d V(-B, A);

  pos = gp_Ax2d(P, V);
}

void gp_Lin2d::Mirror(const gp_Pnt2d& P) noexcept
{
  pos.Mirror(P);
}

gp_Lin2d gp_Lin2d::Mirrored(const gp_Pnt2d& P) const noexcept
{
  gp_Lin2d L = *this;
  L.pos.Mirror(P);
  return L;
}

void gp_Lin2d::Mirror(const gp_Ax2d& A) noexcept
{
  pos.Mirror(A);
}

gp_Lin2d gp_Lin2d::Mirrored(const gp_Ax2d& A) const noexcept
{
  gp_Lin2d L = *this;
  L.pos.Mirror(A);
  return L;
}
