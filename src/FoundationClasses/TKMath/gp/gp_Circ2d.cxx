

#include <gp_Circ2d.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Pnt2d.hpp>

void gp_Circ2d::Mirror(const gp_Pnt2d& P) noexcept
{
  pos.Mirror(P);
}

gp_Circ2d gp_Circ2d::Mirrored(const gp_Pnt2d& P) const noexcept
{
  gp_Circ2d C = *this;
  C.pos.Mirror(P);
  return C;
}

void gp_Circ2d::Mirror(const gp_Ax2d& A) noexcept
{
  pos.Mirror(A);
}

gp_Circ2d gp_Circ2d::Mirrored(const gp_Ax2d& A) const noexcept
{
  gp_Circ2d C = *this;
  C.pos.Mirror(A);
  return C;
}
