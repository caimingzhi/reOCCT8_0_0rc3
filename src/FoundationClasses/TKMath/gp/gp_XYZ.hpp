#pragma once

#include <gp.hpp>
#include <gp_Mat.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_OStream.hpp>
#include <Standard_SStream.hpp>

class gp_XYZ
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_XYZ() noexcept
      : x(0.),
        y(0.),
        z(0.)
  {
  }

  constexpr gp_XYZ(const double theX, const double theY, const double theZ) noexcept
      : x(theX),
        y(theY),
        z(theZ)
  {
  }

  constexpr void SetCoord(const double theX, const double theY, const double theZ) noexcept
  {
    x = theX;
    y = theY;
    z = theZ;
  }

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3, nullptr);
    if (theIndex == 1)
    {
      x = theXi;
    }
    else if (theIndex == 2)
    {
      y = theXi;
    }
    else
    {
      z = theXi;
    }
  }

  constexpr void SetX(const double theX) noexcept { x = theX; }

  constexpr void SetY(const double theY) noexcept { y = theY; }

  constexpr void SetZ(const double theZ) noexcept { z = theZ; }

  constexpr double Coord(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3, nullptr);
    if (theIndex == 1)
    {
      return x;
    }
    else if (theIndex == 2)
    {
      return y;
    }
    return z;
  }

  constexpr double& ChangeCoord(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3, nullptr);
    if (theIndex == 1)
    {
      return x;
    }
    else if (theIndex == 2)
    {
      return y;
    }
    return z;
  }

  constexpr void Coord(double& theX, double& theY, double& theZ) const noexcept
  {
    theX = x;
    theY = y;
    theZ = z;
  }

  constexpr const double* GetData() const noexcept { return (&x); }

  double* ChangeData() noexcept { return (&x); }

  constexpr double X() const noexcept { return x; }

  constexpr double Y() const noexcept { return y; }

  constexpr double Z() const noexcept { return z; }

  double Modulus() const { return sqrt(x * x + y * y + z * z); }

  constexpr double SquareModulus() const noexcept { return (x * x + y * y + z * z); }

  bool IsEqual(const gp_XYZ& theOther, const double theTolerance) const

  {
    return (std::abs(x - theOther.x) < theTolerance) && (std::abs(y - theOther.y) < theTolerance)
           && (std::abs(z - theOther.z) < theTolerance);
  }

  constexpr void Add(const gp_XYZ& theOther) noexcept
  {
    x += theOther.x;
    y += theOther.y;
    z += theOther.z;
  }

  constexpr void operator+=(const gp_XYZ& theOther) noexcept { Add(theOther); }

  [[nodiscard]] constexpr gp_XYZ Added(const gp_XYZ& theOther) const noexcept
  {
    return gp_XYZ(x + theOther.x, y + theOther.y, z + theOther.z);
  }

  [[nodiscard]] constexpr gp_XYZ operator+(const gp_XYZ& theOther) const noexcept
  {
    return Added(theOther);
  }

  constexpr void Cross(const gp_XYZ& theOther) noexcept;

  constexpr void operator^=(const gp_XYZ& theOther) noexcept { Cross(theOther); }

  [[nodiscard]] constexpr gp_XYZ Crossed(const gp_XYZ& theOther) const noexcept
  {
    return gp_XYZ(y * theOther.z - z * theOther.y,
                  z * theOther.x - x * theOther.z,
                  x * theOther.y - y * theOther.x);
  }

  [[nodiscard]] constexpr gp_XYZ operator^(const gp_XYZ& theOther) const noexcept
  {
    return Crossed(theOther);
  }

  double CrossMagnitude(const gp_XYZ& theRight) const;

  constexpr double CrossSquareMagnitude(const gp_XYZ& theRight) const noexcept;

  constexpr void CrossCross(const gp_XYZ& theCoord1, const gp_XYZ& theCoord2) noexcept;

  [[nodiscard]] constexpr gp_XYZ CrossCrossed(const gp_XYZ& theCoord1,
                                              const gp_XYZ& theCoord2) const noexcept
  {
    gp_XYZ aCoord0 = *this;
    aCoord0.CrossCross(theCoord1, theCoord2);
    return aCoord0;
  }

  constexpr void Divide(const double theScalar)
  {
    x /= theScalar;
    y /= theScalar;
    z /= theScalar;
  }

  constexpr void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] constexpr gp_XYZ Divided(const double theScalar) const
  {
    return gp_XYZ(x / theScalar, y / theScalar, z / theScalar);
  }

  [[nodiscard]] constexpr gp_XYZ operator/(const double theScalar) const
  {
    return Divided(theScalar);
  }

  constexpr double Dot(const gp_XYZ& theOther) const noexcept
  {
    return (x * theOther.x + y * theOther.y + z * theOther.z);
  }

  constexpr double operator*(const gp_XYZ& theOther) const noexcept { return Dot(theOther); }

  constexpr double DotCross(const gp_XYZ& theCoord1, const gp_XYZ& theCoord2) const noexcept;

  constexpr void Multiply(const double theScalar) noexcept
  {
    x *= theScalar;
    y *= theScalar;
    z *= theScalar;
  }

  constexpr void operator*=(const double theScalar) noexcept { Multiply(theScalar); }

  constexpr void Multiply(const gp_XYZ& theOther) noexcept
  {
    x *= theOther.x;
    y *= theOther.y;
    z *= theOther.z;
  }

  constexpr void operator*=(const gp_XYZ& theOther) noexcept { Multiply(theOther); }

  constexpr void Multiply(const gp_Mat& theMatrix) noexcept;

  constexpr void operator*=(const gp_Mat& theMatrix) noexcept { Multiply(theMatrix); }

  [[nodiscard]] constexpr gp_XYZ Multiplied(const double theScalar) const noexcept
  {
    return gp_XYZ(x * theScalar, y * theScalar, z * theScalar);
  }

  [[nodiscard]] constexpr gp_XYZ operator*(const double theScalar) const noexcept
  {
    return Multiplied(theScalar);
  }

  [[nodiscard]] constexpr gp_XYZ Multiplied(const gp_XYZ& theOther) const noexcept
  {
    return gp_XYZ(x * theOther.x, y * theOther.y, z * theOther.z);
  }

  [[nodiscard]] constexpr gp_XYZ Multiplied(const gp_Mat& theMatrix) const noexcept
  {

    return gp_XYZ(theMatrix.myMat[0][0] * x + theMatrix.myMat[0][1] * y + theMatrix.myMat[0][2] * z,
                  theMatrix.myMat[1][0] * x + theMatrix.myMat[1][1] * y + theMatrix.myMat[1][2] * z,
                  theMatrix.myMat[2][0] * x + theMatrix.myMat[2][1] * y
                    + theMatrix.myMat[2][2] * z);
  }

  [[nodiscard]] constexpr gp_XYZ operator*(const gp_Mat& theMatrix) const noexcept
  {
    return Multiplied(theMatrix);
  }

  void Normalize();

  [[nodiscard]] gp_XYZ Normalized() const
  {
    const double aD = Modulus();
    Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                        "gp_XYZ::Normalized() - vector has zero norm");
    return gp_XYZ(x / aD, y / aD, z / aD);
  }

  constexpr void Reverse() noexcept
  {
    x = -x;
    y = -y;
    z = -z;
  }

  [[nodiscard]] constexpr gp_XYZ Reversed() const noexcept { return gp_XYZ(-x, -y, -z); }

  constexpr void Subtract(const gp_XYZ& theOther) noexcept
  {
    x -= theOther.x;
    y -= theOther.y;
    z -= theOther.z;
  }

  constexpr void operator-=(const gp_XYZ& theOther) noexcept { Subtract(theOther); }

  [[nodiscard]] constexpr gp_XYZ Subtracted(const gp_XYZ& theOther) const noexcept
  {
    return gp_XYZ(x - theOther.x, y - theOther.y, z - theOther.z);
  }

  [[nodiscard]] constexpr gp_XYZ operator-(const gp_XYZ& theOther) const noexcept
  {
    return Subtracted(theOther);
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_XYZ& theXYZ1,
                               const double  theA2,
                               const gp_XYZ& theXYZ2,
                               const double  theA3,
                               const gp_XYZ& theXYZ3,
                               const gp_XYZ& theXYZ4) noexcept
  {
    x = theA1 * theXYZ1.x + theA2 * theXYZ2.x + theA3 * theXYZ3.x + theXYZ4.x;
    y = theA1 * theXYZ1.y + theA2 * theXYZ2.y + theA3 * theXYZ3.y + theXYZ4.y;
    z = theA1 * theXYZ1.z + theA2 * theXYZ2.z + theA3 * theXYZ3.z + theXYZ4.z;
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_XYZ& theXYZ1,
                               const double  theA2,
                               const gp_XYZ& theXYZ2,
                               const double  theA3,
                               const gp_XYZ& theXYZ3) noexcept
  {
    x = theA1 * theXYZ1.x + theA2 * theXYZ2.x + theA3 * theXYZ3.x;
    y = theA1 * theXYZ1.y + theA2 * theXYZ2.y + theA3 * theXYZ3.y;
    z = theA1 * theXYZ1.z + theA2 * theXYZ2.z + theA3 * theXYZ3.z;
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_XYZ& theXYZ1,
                               const double  theA2,
                               const gp_XYZ& theXYZ2,
                               const gp_XYZ& theXYZ3) noexcept
  {
    x = theA1 * theXYZ1.x + theA2 * theXYZ2.x + theXYZ3.x;
    y = theA1 * theXYZ1.y + theA2 * theXYZ2.y + theXYZ3.y;
    z = theA1 * theXYZ1.z + theA2 * theXYZ2.z + theXYZ3.z;
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_XYZ& theXYZ1,
                               const double  theA2,
                               const gp_XYZ& theXYZ2) noexcept
  {
    x = theA1 * theXYZ1.x + theA2 * theXYZ2.x;
    y = theA1 * theXYZ1.y + theA2 * theXYZ2.y;
    z = theA1 * theXYZ1.z + theA2 * theXYZ2.z;
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_XYZ& theXYZ1,
                               const gp_XYZ& theXYZ2) noexcept
  {
    x = theA1 * theXYZ1.x + theXYZ2.x;
    y = theA1 * theXYZ1.y + theXYZ2.y;
    z = theA1 * theXYZ1.z + theXYZ2.z;
  }

  constexpr void SetLinearForm(const gp_XYZ& theXYZ1, const gp_XYZ& theXYZ2) noexcept
  {
    x = theXYZ1.x + theXYZ2.x;
    y = theXYZ1.y + theXYZ2.y;
    z = theXYZ1.z + theXYZ2.z;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  double x;
  double y;
  double z;
};

inline constexpr void gp_XYZ::Cross(const gp_XYZ& theRight) noexcept
{
  const double aXresult = y * theRight.z - z * theRight.y;
  const double aYresult = z * theRight.x - x * theRight.z;
  z                     = x * theRight.y - y * theRight.x;
  x                     = aXresult;
  y                     = aYresult;
}

inline double gp_XYZ::CrossMagnitude(const gp_XYZ& theRight) const
{
  return sqrt(CrossSquareMagnitude(theRight));
}

inline constexpr double gp_XYZ::CrossSquareMagnitude(const gp_XYZ& theRight) const noexcept
{
  const double aXresult = y * theRight.z - z * theRight.y;
  const double aYresult = z * theRight.x - x * theRight.z;
  const double aZresult = x * theRight.y - y * theRight.x;
  return aXresult * aXresult + aYresult * aYresult + aZresult * aZresult;
}

inline constexpr void gp_XYZ::CrossCross(const gp_XYZ& theCoord1, const gp_XYZ& theCoord2) noexcept
{

  const double aCrossX = theCoord1.y * theCoord2.z - theCoord1.z * theCoord2.y;
  const double aCrossY = theCoord1.z * theCoord2.x - theCoord1.x * theCoord2.z;
  const double aCrossZ = theCoord1.x * theCoord2.y - theCoord1.y * theCoord2.x;

  const double aXresult = y * aCrossZ - z * aCrossY;
  const double aYresult = z * aCrossX - x * aCrossZ;

  z = x * aCrossY - y * aCrossX;
  x = aXresult;
  y = aYresult;
}

inline constexpr double gp_XYZ::DotCross(const gp_XYZ& theCoord1,
                                         const gp_XYZ& theCoord2) const noexcept
{
  const double aXresult  = theCoord1.y * theCoord2.z - theCoord1.z * theCoord2.y;
  const double anYresult = theCoord1.z * theCoord2.x - theCoord1.x * theCoord2.z;
  const double aZresult  = theCoord1.x * theCoord2.y - theCoord1.y * theCoord2.x;
  return (x * aXresult + y * anYresult + z * aZresult);
}

inline constexpr void gp_XYZ::Multiply(const gp_Mat& theMatrix) noexcept
{

  const double aOrigX = x;
  const double aOrigY = y;
  const double aOrigZ = z;

  x = theMatrix.myMat[0][0] * aOrigX + theMatrix.myMat[0][1] * aOrigY
      + theMatrix.myMat[0][2] * aOrigZ;
  y = theMatrix.myMat[1][0] * aOrigX + theMatrix.myMat[1][1] * aOrigY
      + theMatrix.myMat[1][2] * aOrigZ;
  z = theMatrix.myMat[2][0] * aOrigX + theMatrix.myMat[2][1] * aOrigY
      + theMatrix.myMat[2][2] * aOrigZ;
}

inline void gp_XYZ::Normalize()
{
  double aD = Modulus();
  Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                      "gp_XYZ::Normalize() - vector has zero norm");
  x = x / aD;
  y = y / aD;
  z = z / aD;
}

inline constexpr gp_XYZ operator*(const gp_Mat& theMatrix, const gp_XYZ& theCoord1) noexcept
{
  return theCoord1.Multiplied(theMatrix);
}

inline constexpr gp_XYZ operator*(const double theScalar, const gp_XYZ& theCoord1) noexcept
{
  return theCoord1.Multiplied(theScalar);
}
