

#include <gp_Pln.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Dump.hpp>

gp_Pln::gp_Pln(const gp_Pnt& P, const gp_Dir& V)
{
  double A    = V.X();
  double B    = V.Y();
  double C    = V.Z();
  double Aabs = A;
  if (Aabs < 0)
    Aabs = -Aabs;
  double Babs = B;
  if (Babs < 0)
    Babs = -Babs;
  double Cabs = C;
  if (Cabs < 0)
    Cabs = -Cabs;

  if (Babs <= Aabs && Babs <= Cabs)
  {
    if (Aabs > Cabs)
      pos = gp_Ax3(P, V, gp_Dir(-C, 0., A));
    else
      pos = gp_Ax3(P, V, gp_Dir(C, 0., -A));
  }
  else if (Aabs <= Babs && Aabs <= Cabs)
  {
    if (Babs > Cabs)
      pos = gp_Ax3(P, V, gp_Dir(0., -C, B));
    else
      pos = gp_Ax3(P, V, gp_Dir(0., C, -B));
  }
  else
  {
    if (Aabs > Babs)
      pos = gp_Ax3(P, V, gp_Dir(-B, A, 0.));
    else
      pos = gp_Ax3(P, V, gp_Dir(B, -A, 0.));
  }
}

gp_Pln::gp_Pln(const double A, const double B, const double C, const double D)
{
  double Aabs = A;
  if (Aabs < 0)
    Aabs = -Aabs;
  double Babs = B;
  if (Babs < 0)
    Babs = -Babs;
  double Cabs = C;
  if (Cabs < 0)
    Cabs = -Cabs;
  if (Babs <= Aabs && Babs <= Cabs)
  {
    if (Aabs > Cabs)
      pos = gp_Ax3(gp_Pnt(-D / A, 0., 0.), gp_Dir(A, B, C), gp_Dir(-C, 0., A));
    else
      pos = gp_Ax3(gp_Pnt(0., 0., -D / C), gp_Dir(A, B, C), gp_Dir(C, 0., -A));
  }
  else if (Aabs <= Babs && Aabs <= Cabs)
  {
    if (Babs > Cabs)
      pos = gp_Ax3(gp_Pnt(0., -D / B, 0.), gp_Dir(A, B, C), gp_Dir(0., -C, B));
    else
      pos = gp_Ax3(gp_Pnt(0., 0., -D / C), gp_Dir(A, B, C), gp_Dir(0., C, -B));
  }
  else
  {
    if (Aabs > Babs)
      pos = gp_Ax3(gp_Pnt(-D / A, 0., 0.), gp_Dir(A, B, C), gp_Dir(-B, A, 0.));
    else
      pos = gp_Ax3(gp_Pnt(0., -D / B, 0.), gp_Dir(A, B, C), gp_Dir(B, -A, 0.));
  }
}

void gp_Pln::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Pln gp_Pln::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Pln Pl = *this;
  Pl.pos.Mirror(P);
  return Pl;
}

void gp_Pln::Mirror(const gp_Ax1& A1) noexcept
{
  pos.Mirror(A1);
}

gp_Pln gp_Pln::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Pln Pl = *this;
  Pl.pos.Mirror(A1);
  return Pl;
}

void gp_Pln::Mirror(const gp_Ax2& A2) noexcept
{
  pos.Mirror(A2);
}

gp_Pln gp_Pln::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Pln Pl = *this;
  Pl.pos.Mirror(A2);
  return Pl;
}

void gp_Pln::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &pos)
}
