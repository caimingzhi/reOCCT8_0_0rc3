

#include <gp_Dir.hpp>

#include <gp_Ax2.hpp>
#include <gp_Trsf.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

double gp_Dir::Angle(const gp_Dir& Other) const
{

  double Cosinus = coord.Dot(Other.coord);
  if (Cosinus > -0.70710678118655 && Cosinus < 0.70710678118655)
    return acos(Cosinus);
  else
  {
    double Sinus = (coord.Crossed(Other.coord)).Modulus();
    if (Cosinus < 0.0)
      return M_PI - asin(Sinus);
    else
      return asin(Sinus);
  }
}

double gp_Dir::AngleWithRef(const gp_Dir& Other, const gp_Dir& Vref) const
{
  double Ang;
  gp_XYZ XYZ     = coord.Crossed(Other.coord);
  double Cosinus = coord.Dot(Other.coord);
  double Sinus   = XYZ.Modulus();
  if (Cosinus > -0.70710678118655 && Cosinus < 0.70710678118655)
    Ang = acos(Cosinus);
  else
  {
    if (Cosinus < 0.0)
      Ang = M_PI - asin(Sinus);
    else
      Ang = asin(Sinus);
  }
  if (XYZ.Dot(Vref.coord) >= 0.0)
    return Ang;
  else
    return -Ang;
}

void gp_Dir::Mirror(const gp_Dir& V) noexcept
{
  const gp_XYZ& XYZ = V.coord;
  double        A   = XYZ.X();
  double        B   = XYZ.Y();
  double        C   = XYZ.Z();
  double        X   = coord.X();
  double        Y   = coord.Y();
  double        Z   = coord.Z();
  double        M1  = 2.0 * A * B;
  double        M2  = 2.0 * A * C;
  double        M3  = 2.0 * B * C;
  double        XX  = ((2.0 * A * A) - 1.0) * X + M1 * Y + M2 * Z;
  double        YY  = M1 * X + ((2.0 * B * B) - 1.0) * Y + M3 * Z;
  double        ZZ  = M2 * X + M3 * Y + ((2.0 * C * C) - 1.0) * Z;
  coord.SetCoord(XX, YY, ZZ);
}

void gp_Dir::Mirror(const gp_Ax1& A1) noexcept
{
  const gp_XYZ& XYZ = A1.Direction().coord;
  double        A   = XYZ.X();
  double        B   = XYZ.Y();
  double        C   = XYZ.Y();
  double        X   = coord.X();
  double        Y   = coord.Y();
  double        Z   = coord.Z();
  double        M1  = 2.0 * A * B;
  double        M2  = 2.0 * A * C;
  double        M3  = 2.0 * B * C;
  double        XX  = ((2.0 * A * A) - 1.0) * X + M1 * Y + M2 * Z;
  double        YY  = M1 * X + ((2.0 * B * B) - 1.0) * Y + M3 * Z;
  double        ZZ  = M2 * X + M3 * Y + ((2.0 * C * C) - 1.0) * Z;
  coord.SetCoord(XX, YY, ZZ);
}

void gp_Dir::Mirror(const gp_Ax2& A2) noexcept
{
  const gp_Dir& Vz = A2.Direction();
  Mirror(Vz);
  Reverse();
}

void gp_Dir::Transform(const gp_Trsf& T)
{
  if (T.Form() == gp_Identity || T.Form() == gp_Translation)
  {
  }
  else if (T.Form() == gp_PntMirror)
  {
    coord.Reverse();
  }
  else if (T.Form() == gp_Scale)
  {
    if (T.ScaleFactor() < 0.0)
    {
      coord.Reverse();
    }
  }
  else
  {
    coord.Multiply(T.HVectorialPart());
    double D = coord.Modulus();
    coord.Divide(D);
    if (T.ScaleFactor() < 0.0)
    {
      coord.Reverse();
    }
  }
}

gp_Dir gp_Dir::Mirrored(const gp_Dir& V) const noexcept
{
  gp_Dir Vres = *this;
  Vres.Mirror(V);
  return Vres;
}

gp_Dir gp_Dir::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Dir V = *this;
  V.Mirror(A1);
  return V;
}

gp_Dir gp_Dir::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Dir V = *this;
  V.Mirror(A2);
  return V;
}

void gp_Dir::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_Dir", 3, coord.X(), coord.Y(), coord.Z())
}

bool gp_Dir::InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
{
  int aPos = theStreamPos;

  OCCT_INIT_VECTOR_CLASS(Standard_Dump::Text(theSStream),
                         "gp_Dir",
                         aPos,
                         3,
                         &coord.ChangeCoord(1),
                         &coord.ChangeCoord(2),
                         &coord.ChangeCoord(3))

  theStreamPos = aPos;
  return true;
}
