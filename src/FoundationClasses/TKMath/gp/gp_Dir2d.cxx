

#include <gp_Dir2d.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_XY.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

double gp_Dir2d::Angle(const gp_Dir2d& Other) const
{

  double Cosinus = coord.Dot(Other.coord);
  double Sinus   = coord.Crossed(Other.coord);
  if (Cosinus > -0.70710678118655 && Cosinus < 0.70710678118655)
  {
    if (Sinus > 0.0)
      return acos(Cosinus);
    else
      return -acos(Cosinus);
  }
  else
  {
    if (Cosinus > 0.0)
      return asin(Sinus);
    else
    {
      if (Sinus > 0.0)
        return M_PI - asin(Sinus);
      else
        return -M_PI - asin(Sinus);
    }
  }
}

void gp_Dir2d::Mirror(const gp_Ax2d& A2) noexcept
{
  const gp_XY& XY = A2.Direction().XY();
  double       A  = XY.X();
  double       B  = XY.Y();
  double       X  = coord.X();
  double       Y  = coord.Y();
  double       M1 = 2.0 * A * B;
  double       XX = ((2.0 * A * A) - 1.0) * X + M1 * Y;
  double       YY = M1 * X + ((2.0 * B * B) - 1.0) * Y;
  coord.SetCoord(XX, YY);
}

void gp_Dir2d::Transform(const gp_Trsf2d& T) noexcept
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

void gp_Dir2d::Mirror(const gp_Dir2d& V) noexcept
{
  const gp_XY& XY = V.coord;
  double       A  = XY.X();
  double       B  = XY.Y();
  double       X  = coord.X();
  double       Y  = coord.Y();
  double       M1 = 2.0 * A * B;
  double       XX = ((2.0 * A * A) - 1.0) * X + M1 * Y;
  double       YY = M1 * X + ((2.0 * B * B) - 1.0) * Y;
  coord.SetCoord(XX, YY);
}

gp_Dir2d gp_Dir2d::Mirrored(const gp_Dir2d& V) const noexcept
{
  gp_Dir2d Vres = *this;
  Vres.Mirror(V);
  return Vres;
}

gp_Dir2d gp_Dir2d::Mirrored(const gp_Ax2d& A) const noexcept
{
  gp_Dir2d V = *this;
  V.Mirror(A);
  return V;
}

void gp_Dir2d::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_Dir2d", 2, coord.X(), coord.Y())
}
