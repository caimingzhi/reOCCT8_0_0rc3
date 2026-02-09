

#include <gp_Elips.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>

void gp_Elips::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Elips gp_Elips::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Elips E = *this;
  E.pos.Mirror(P);
  return E;
}

void gp_Elips::Mirror(const gp_Ax1& A1)
{
  pos.Mirror(A1);
}

gp_Elips gp_Elips::Mirrored(const gp_Ax1& A1) const
{
  gp_Elips E = *this;
  E.pos.Mirror(A1);
  return E;
}

void gp_Elips::Mirror(const gp_Ax2& A2)
{
  pos.Mirror(A2);
}

gp_Elips gp_Elips::Mirrored(const gp_Ax2& A2) const
{
  gp_Elips E = *this;
  E.pos.Mirror(A2);
  return E;
}
