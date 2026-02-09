

#include <gp_Hypr.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>

void gp_Hypr::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Hypr gp_Hypr::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Hypr H = *this;
  H.pos.Mirror(P);
  return H;
}

void gp_Hypr::Mirror(const gp_Ax1& A1)
{
  pos.Mirror(A1);
}

gp_Hypr gp_Hypr::Mirrored(const gp_Ax1& A1) const
{
  gp_Hypr H = *this;
  H.pos.Mirror(A1);
  return H;
}

void gp_Hypr::Mirror(const gp_Ax2& A2)
{
  pos.Mirror(A2);
}

gp_Hypr gp_Hypr::Mirrored(const gp_Ax2& A2) const
{
  gp_Hypr H = *this;
  H.pos.Mirror(A2);
  return H;
}
