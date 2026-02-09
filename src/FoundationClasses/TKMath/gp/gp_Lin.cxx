

#include <gp_Lin.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>

double gp_Lin::Distance(const gp_Lin& Other) const
{
  if (pos.IsParallel(Other.pos, gp::Resolution()))
  {
    return Other.Distance(pos.Location());
  }
  else
  {
    const gp_Dir dir(pos.Direction().Crossed(Other.pos.Direction()));
    return std::abs(gp_Vec(pos.Location(), Other.pos.Location()).Dot(gp_Vec(dir)));
  }
}

void gp_Lin::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Lin gp_Lin::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Lin L = *this;
  L.pos.Mirror(P);
  return L;
}

void gp_Lin::Mirror(const gp_Ax1& A1) noexcept
{
  pos.Mirror(A1);
}

gp_Lin gp_Lin::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Lin L = *this;
  L.pos.Mirror(A1);
  return L;
}

void gp_Lin::Mirror(const gp_Ax2& A2) noexcept
{
  pos.Mirror(A2);
}

gp_Lin gp_Lin::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Lin L = *this;
  L.pos.Mirror(A2);
  return L;
}
