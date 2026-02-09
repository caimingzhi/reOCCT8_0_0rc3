

#include <gp_Ax22d.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Dump.hpp>

void gp_Ax22d::Mirror(const gp_Pnt2d& P) noexcept
{
  gp_Pnt2d Temp = point;
  Temp.Mirror(P);
  point = Temp;
  vxdir.Reverse();
  vydir.Reverse();
}

gp_Ax22d gp_Ax22d::Mirrored(const gp_Pnt2d& P) const noexcept
{
  gp_Ax22d Temp = *this;
  Temp.Mirror(P);
  return Temp;
}

void gp_Ax22d::Mirror(const gp_Ax2d& A1) noexcept
{
  vydir.Mirror(A1);
  vxdir.Mirror(A1);
  gp_Pnt2d Temp = point;
  Temp.Mirror(A1);
  point = Temp;
}

gp_Ax22d gp_Ax22d::Mirrored(const gp_Ax2d& A1) const noexcept
{
  gp_Ax22d Temp = *this;
  Temp.Mirror(A1);
  return Temp;
}

void gp_Ax22d::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "Location", 2, point.X(), point.Y())

  OCCT_DUMP_VECTOR_CLASS(theOStream, "XAxis", 2, vxdir.X(), vxdir.Y())
  OCCT_DUMP_VECTOR_CLASS(theOStream, "YAxis", 2, vydir.X(), vydir.Y())
}
