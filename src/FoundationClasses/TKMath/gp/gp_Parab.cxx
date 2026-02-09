

#include <gp_Parab.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>

void gp_Parab::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Parab gp_Parab::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Parab Prb = *this;
  Prb.pos.Mirror(P);
  return Prb;
}

void gp_Parab::Mirror(const gp_Ax1& A1)
{
  pos.Mirror(A1);
}

gp_Parab gp_Parab::Mirrored(const gp_Ax1& A1) const
{
  gp_Parab Prb = *this;
  Prb.pos.Mirror(A1);
  return Prb;
}

void gp_Parab::Mirror(const gp_Ax2& A2)
{
  pos.Mirror(A2);
}

gp_Parab gp_Parab::Mirrored(const gp_Ax2& A2) const
{
  gp_Parab Prb = *this;
  Prb.pos.Mirror(A2);
  return Prb;
}
