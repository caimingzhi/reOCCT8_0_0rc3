

#include <gp_Circ.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>

void gp_Circ::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Circ gp_Circ::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Circ C = *this;
  C.pos.Mirror(P);
  return C;
}

void gp_Circ::Mirror(const gp_Ax1& A1)
{
  pos.Mirror(A1);
}

gp_Circ gp_Circ::Mirrored(const gp_Ax1& A1) const
{
  gp_Circ C = *this;
  C.pos.Mirror(A1);
  return C;
}

void gp_Circ::Mirror(const gp_Ax2& A2)
{
  pos.Mirror(A2);
}

gp_Circ gp_Circ::Mirrored(const gp_Ax2& A2) const
{
  gp_Circ C = *this;
  C.pos.Mirror(A2);
  return C;
}
