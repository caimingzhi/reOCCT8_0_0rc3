#include <gp_Ax3.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Dump.hpp>

gp_Ax3::gp_Ax3(const gp_Pnt& P, const gp_Dir& V)
    : axis(P, V)
{
  const double A    = V.X();
  const double B    = V.Y();
  const double C    = V.Z();
  const double Aabs = std::abs(A);
  const double Babs = std::abs(B);
  const double Cabs = std::abs(C);
  gp_Dir       D;

  if (Babs <= Aabs && Babs <= Cabs)
  {
    if (Aabs > Cabs)
      D.SetCoord(-C, 0., A);
    else
      D.SetCoord(C, 0., -A);
  }
  else if (Aabs <= Babs && Aabs <= Cabs)
  {
    if (Babs > Cabs)
      D.SetCoord(0., -C, B);
    else
      D.SetCoord(0., C, -B);
  }
  else
  {
    if (Aabs > Babs)
      D.SetCoord(-B, A, 0.);
    else
      D.SetCoord(B, -A, 0.);
  }
  vxdir = D;
  vydir = V.Crossed(vxdir);
}

void gp_Ax3::Mirror(const gp_Pnt& P) noexcept
{
  axis.Mirror(P);
  vxdir.Reverse();
  vydir.Reverse();
}

gp_Ax3 gp_Ax3::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Ax3 Temp = *this;
  Temp.Mirror(P);
  return Temp;
}

void gp_Ax3::Mirror(const gp_Ax1& A1) noexcept
{
  vydir.Mirror(A1);
  vxdir.Mirror(A1);
  axis.Mirror(A1);
}

gp_Ax3 gp_Ax3::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Ax3 Temp = *this;
  Temp.Mirror(A1);
  return Temp;
}

void gp_Ax3::Mirror(const gp_Ax2& A2) noexcept
{
  vydir.Mirror(A2);
  vxdir.Mirror(A2);
  axis.Mirror(A2);
}

gp_Ax3 gp_Ax3::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Ax3 Temp = *this;
  Temp.Mirror(A2);
  return Temp;
}

void gp_Ax3::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "Location", 3, Location().X(), Location().Y(), Location().Z())
  OCCT_DUMP_VECTOR_CLASS(theOStream,
                         "Direction",
                         3,
                         Direction().X(),
                         Direction().Y(),
                         Direction().Z())

  OCCT_DUMP_VECTOR_CLASS(theOStream,
                         "XDirection",
                         3,
                         XDirection().X(),
                         XDirection().Y(),
                         XDirection().Z())
  OCCT_DUMP_VECTOR_CLASS(theOStream,
                         "YDirection",
                         3,
                         YDirection().X(),
                         YDirection().Y(),
                         YDirection().Z())
}

bool gp_Ax3::InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
{
  int                     aPos       = theStreamPos;
  TCollection_AsciiString aStreamStr = Standard_Dump::Text(theSStream);

  gp_XYZ anXYZLoc;
  OCCT_INIT_VECTOR_CLASS(aStreamStr,
                         "Location",
                         aPos,
                         3,
                         &anXYZLoc.ChangeCoord(1),
                         &anXYZLoc.ChangeCoord(2),
                         &anXYZLoc.ChangeCoord(3))
  SetLocation(anXYZLoc);

  gp_XYZ aDir;
  OCCT_INIT_VECTOR_CLASS(aStreamStr,
                         "Direction",
                         aPos,
                         3,
                         &aDir.ChangeCoord(1),
                         &aDir.ChangeCoord(2),
                         &aDir.ChangeCoord(3))
  gp_XYZ aXDir;
  OCCT_INIT_VECTOR_CLASS(aStreamStr,
                         "XDirection",
                         aPos,
                         3,
                         &aXDir.ChangeCoord(1),
                         &aXDir.ChangeCoord(2),
                         &aXDir.ChangeCoord(3))
  gp_XYZ anYDir;
  OCCT_INIT_VECTOR_CLASS(aStreamStr,
                         "YDirection",
                         aPos,
                         3,
                         &anYDir.ChangeCoord(1),
                         &anYDir.ChangeCoord(2),
                         &anYDir.ChangeCoord(3))

  axis.SetDirection(gp_Dir(aDir));
  vxdir = gp_Dir(aXDir);
  vydir = gp_Dir(anYDir);

  if (!Direction().IsEqual(aDir, Precision::Angular()))
    return false;

  theStreamPos = aPos;
  return true;
}
