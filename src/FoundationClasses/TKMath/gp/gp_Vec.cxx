

#define No_Standard_OutOfRange

#include <gp_Vec.hpp>

#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Trsf.hpp>
#include <gp_XYZ.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_OutOfRange.hpp>

bool gp_Vec::IsEqual(const gp_Vec& theOther,
                     const double  theLinearTolerance,
                     const double  theAngularTolerance) const
{
  const double aMagnitude       = Magnitude();
  const double anOtherMagnitude = theOther.Magnitude();

  if (aMagnitude <= theLinearTolerance || anOtherMagnitude <= theLinearTolerance)
  {
    const double aVal = std::abs(aMagnitude - anOtherMagnitude);
    return aVal <= theLinearTolerance;
  }
  else
  {
    const double aVal = std::abs(aMagnitude - anOtherMagnitude);
    return aVal <= theLinearTolerance && Angle(theOther) <= theAngularTolerance;
  }
}

void gp_Vec::Mirror(const gp_Vec& theVec) noexcept
{
  const double aMagnitude = theVec.coord.Modulus();
  if (aMagnitude > gp::Resolution())
  {
    const gp_XYZ& aMirrorVecXYZ = theVec.coord;
    const double  aOrigX        = coord.X();
    const double  aOrigY        = coord.Y();
    const double  aOrigZ        = coord.Z();

    const double aNormDirX = aMirrorVecXYZ.X() / aMagnitude;
    const double aNormDirY = aMirrorVecXYZ.Y() / aMagnitude;
    const double aNormDirZ = aMirrorVecXYZ.Z() / aMagnitude;

    const double aCrossTermXY = 2.0 * aNormDirX * aNormDirY;
    const double aCrossTermXZ = 2.0 * aNormDirX * aNormDirZ;
    const double aCrossTermYZ = 2.0 * aNormDirY * aNormDirZ;
    const double aXXTerm      = 2.0 * aNormDirX * aNormDirX - 1.0;
    const double aYYTerm      = 2.0 * aNormDirY * aNormDirY - 1.0;
    const double aZZTerm      = 2.0 * aNormDirZ * aNormDirZ - 1.0;

    coord.SetX(aXXTerm * aOrigX + aCrossTermXY * aOrigY + aCrossTermXZ * aOrigZ);
    coord.SetY(aCrossTermXY * aOrigX + aYYTerm * aOrigY + aCrossTermYZ * aOrigZ);
    coord.SetZ(aCrossTermXZ * aOrigX + aCrossTermYZ * aOrigY + aZZTerm * aOrigZ);
  }
}

void gp_Vec::Mirror(const gp_Ax1& theAxis) noexcept
{
  const gp_XYZ& aDirectionXYZ = theAxis.Direction().XYZ();
  const double  aOrigX        = coord.X();
  const double  aOrigY        = coord.Y();
  const double  aOrigZ        = coord.Z();
  const double  aDirX         = aDirectionXYZ.X();
  const double  aDirY         = aDirectionXYZ.Y();
  const double  aDirZ         = aDirectionXYZ.Z();

  const double aCrossTermXY = 2.0 * aDirX * aDirY;
  const double aCrossTermXZ = 2.0 * aDirX * aDirZ;
  const double aCrossTermYZ = 2.0 * aDirY * aDirZ;
  const double aXXTerm      = 2.0 * aDirX * aDirX - 1.0;
  const double aYYTerm      = 2.0 * aDirY * aDirY - 1.0;
  const double aZZTerm      = 2.0 * aDirZ * aDirZ - 1.0;

  coord.SetX(aXXTerm * aOrigX + aCrossTermXY * aOrigY + aCrossTermXZ * aOrigZ);
  coord.SetY(aCrossTermXY * aOrigX + aYYTerm * aOrigY + aCrossTermYZ * aOrigZ);
  coord.SetZ(aCrossTermXZ * aOrigX + aCrossTermYZ * aOrigY + aZZTerm * aOrigZ);
}

void gp_Vec::Mirror(const gp_Ax2& theAxis) noexcept
{
  const gp_XYZ& aZDir   = theAxis.Direction().XYZ();
  const gp_XYZ  aMirXYZ = aZDir.Crossed(coord);

  if (aMirXYZ.Modulus() <= gp::Resolution())
  {
    coord.Reverse();
  }
  else
  {
    gp_XYZ aNewZ = aZDir;
    aNewZ.Cross(aMirXYZ);
    Mirror(gp_Vec(aNewZ));
  }
}

void gp_Vec::Transform(const gp_Trsf& theTransformation)
{
  if (theTransformation.Form() == gp_Identity || theTransformation.Form() == gp_Translation)
  {
  }
  else if (theTransformation.Form() == gp_PntMirror)
  {
    coord.Reverse();
  }
  else if (theTransformation.Form() == gp_Scale)
  {
    coord.Multiply(theTransformation.ScaleFactor());
  }
  else
  {
    coord.Multiply(theTransformation.VectorialPart());
  }
}

gp_Vec gp_Vec::Mirrored(const gp_Vec& theVec) const noexcept
{
  gp_Vec aResult = *this;
  aResult.Mirror(theVec);
  return aResult;
}

gp_Vec gp_Vec::Mirrored(const gp_Ax1& theAxis) const noexcept
{
  gp_Vec aResult = *this;
  aResult.Mirror(theAxis);
  return aResult;
}

gp_Vec gp_Vec::Mirrored(const gp_Ax2& theAxis) const noexcept
{
  gp_Vec aResult = *this;
  aResult.Mirror(theAxis);
  return aResult;
}

void gp_Vec::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_VECTOR_CLASS(theOStream, "gp_Vec", 3, coord.X(), coord.Y(), coord.Z())
}
