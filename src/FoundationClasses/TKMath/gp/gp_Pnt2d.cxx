

#define No_Standard_OutOfRange

#include <gp_Pnt2d.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_XY.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

void gp_Pnt2d::Transform(const gp_Trsf2d& T) noexcept
{
  if (T.Form() == gp_Identity)
  {
  }
  else if (T.Form() == gp_Translation)
  {
    coord.Add(T.TranslationPart());
  }
  else if (T.Form() == gp_Scale)
  {
    coord.Multiply(T.ScaleFactor());
    coord.Add(T.TranslationPart());
  }
  else if (T.Form() == gp_PntMirror)
  {
    coord.Reverse();
    coord.Add(T.TranslationPart());
  }
  else
  {
    T.Transforms(coord);
  }
}

void gp_Pnt2d::Mirror(const gp_Pnt2d& P) noexcept
{
  coord.Reverse();
  gp_XY XY = P.coord;
  XY.Multiply(2.0);
  coord.Add(XY);
}

gp_Pnt2d gp_Pnt2d::Mirrored(const gp_Pnt2d& P) const noexcept
{
  gp_Pnt2d Pres = *this;
  Pres.Mirror(P);
  return Pres;
}

void gp_Pnt2d::Mirror(const gp_Ax2d& A) noexcept
{
  gp_Trsf2d T;
  T.SetMirror(A);
  T.Transforms(coord);
}

gp_Pnt2d gp_Pnt2d::Mirrored(const gp_Ax2d& A) const noexcept
{
  gp_Pnt2d P = *this;
  P.Mirror(A);
  return P;
}

void gp_Pnt2d::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_Pnt2d", 2, coord.X(), coord.Y())
}
