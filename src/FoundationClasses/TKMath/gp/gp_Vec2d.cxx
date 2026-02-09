

#define No_Standard_OutOfRange

#include <gp_Vec2d.hpp>

#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_VectorWithNullMagnitude.hpp>
#include <gp_XY.hpp>

bool gp_Vec2d::IsEqual(const gp_Vec2d& theOther,
                       const double    theLinearTolerance,
                       const double    theAngularTolerance) const
{
  const double aNorm       = Magnitude();
  const double anOtherNorm = theOther.Magnitude();
  const double aVal        = std::abs(aNorm - anOtherNorm);

  const bool isEqualLength = (aVal <= theLinearTolerance);

  if (aNorm > theLinearTolerance && anOtherNorm > theLinearTolerance)
  {
    const double anAng = std::abs(Angle(theOther));

    return isEqualLength && (anAng <= theAngularTolerance);
  }
  return isEqualLength;
}

double gp_Vec2d::Angle(const gp_Vec2d& theOther) const
{

  const double aNorm       = Magnitude();
  const double anOtherNorm = theOther.Magnitude();
  if (aNorm <= gp::Resolution() || anOtherNorm <= gp::Resolution())
    throw gp_VectorWithNullMagnitude();

  const double aD       = aNorm * anOtherNorm;
  const double aCosinus = coord.Dot(theOther.coord) / aD;
  const double aSinus   = coord.Crossed(theOther.coord) / aD;

  constexpr double aCOS_45_DEG = M_SQRT1_2;

  if (aCosinus > -aCOS_45_DEG && aCosinus < aCOS_45_DEG)
  {

    return (aSinus > 0.0) ? acos(aCosinus) : -acos(aCosinus);
  }
  else
  {

    if (aCosinus > 0.0)
      return asin(aSinus);
    else
      return (aSinus > 0.0) ? M_PI - asin(aSinus) : -M_PI - asin(aSinus);
  }
}

void gp_Vec2d::Mirror(const gp_Ax2d& theA1)
{
  const gp_XY& aDirectionXY = theA1.Direction().XY();
  const double aOrigX       = coord.X();
  const double aOrigY       = coord.Y();
  const double aDirX        = aDirectionXY.X();
  const double aDirY        = aDirectionXY.Y();

  const double aCrossTerm = 2.0 * aDirX * aDirY;
  const double aXXTerm    = 2.0 * aDirX * aDirX - 1.0;
  const double aYYTerm    = 2.0 * aDirY * aDirY - 1.0;

  coord.SetX(aXXTerm * aOrigX + aCrossTerm * aOrigY);
  coord.SetY(aCrossTerm * aOrigX + aYYTerm * aOrigY);
}

gp_Vec2d gp_Vec2d::Mirrored(const gp_Ax2d& theA1) const
{
  gp_Vec2d Vres = *this;
  Vres.Mirror(theA1);
  return Vres;
}

void gp_Vec2d::Transform(const gp_Trsf2d& theT) noexcept
{
  switch (theT.Form())
  {
    case gp_Identity:
    case gp_Translation:
      break;

    case gp_PntMirror:
      coord.Reverse();
      break;

    case gp_Scale:
      coord.Multiply(theT.ScaleFactor());
      break;

    default:
      coord.Multiply(theT.VectorialPart());
  }
}

void gp_Vec2d::Mirror(const gp_Vec2d& theV)
{
  const double aMagnitude = theV.coord.Modulus();
  if (aMagnitude > gp::Resolution())
  {
    const gp_XY& aMirrorVecXY = theV.coord;
    const double aOrigX       = coord.X();
    const double aOrigY       = coord.Y();

    const double aNormDirX = aMirrorVecXY.X() / aMagnitude;
    const double aNormDirY = aMirrorVecXY.Y() / aMagnitude;

    const double aCrossTerm = 2.0 * aNormDirX * aNormDirY;
    const double aXXTerm    = 2.0 * aNormDirX * aNormDirX - 1.0;
    const double aYYTerm    = 2.0 * aNormDirY * aNormDirY - 1.0;

    coord.SetX(aXXTerm * aOrigX + aCrossTerm * aOrigY);
    coord.SetY(aCrossTerm * aOrigX + aYYTerm * aOrigY);
  }
}

gp_Vec2d gp_Vec2d::Mirrored(const gp_Vec2d& theV) const
{
  gp_Vec2d aVres = *this;
  aVres.Mirror(theV);
  return aVres;
}
