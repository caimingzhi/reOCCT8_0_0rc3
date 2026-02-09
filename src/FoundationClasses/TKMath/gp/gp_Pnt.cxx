

#define No_Standard_OutOfRange

#include <gp_Pnt.hpp>

#include <gp_Ax2.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

void gp_Pnt::Transform(const gp_Trsf& T)
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

void gp_Pnt::Mirror(const gp_Pnt& P) noexcept
{
  coord.Reverse();
  gp_XYZ XYZ = P.coord;
  XYZ.Multiply(2.0);
  coord.Add(XYZ);
}

gp_Pnt gp_Pnt::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Pnt Pres = *this;
  Pres.Mirror(P);
  return Pres;
}

void gp_Pnt::Mirror(const gp_Ax1& A1) noexcept
{
  gp_Trsf T;
  T.SetMirror(A1);
  T.Transforms(coord);
}

gp_Pnt gp_Pnt::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Pnt P = *this;
  P.Mirror(A1);
  return P;
}

void gp_Pnt::Mirror(const gp_Ax2& A2) noexcept
{
  gp_Trsf T;
  T.SetMirror(A2);
  T.Transforms(coord);
}

gp_Pnt gp_Pnt::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Pnt P = *this;
  P.Mirror(A2);
  return P;
}

void gp_Pnt::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_Pnt", 3, coord.X(), coord.Y(), coord.Z())
}

bool gp_Pnt::InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
{
  int aPos = theStreamPos;

  OCCT_INIT_VECTOR_CLASS(Standard_Dump::Text(theSStream),
                         "gp_Pnt",
                         aPos,
                         3,
                         &coord.ChangeCoord(1),
                         &coord.ChangeCoord(2),
                         &coord.ChangeCoord(3))

  theStreamPos = aPos;
  return true;
}
