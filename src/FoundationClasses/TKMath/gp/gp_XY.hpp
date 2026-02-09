#pragma once

#include <gp.hpp>
#include <gp_Mat2d.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>

class gp_XY
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_XY() noexcept
      : x(0.),
        y(0.)
  {
  }

  constexpr gp_XY(const double theX, const double theY) noexcept
      : x(theX),
        y(theY)
  {
  }

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 2, nullptr);
    if (theIndex == 1)
    {
      x = theXi;
    }
    else
    {
      y = theXi;
    }
  }

  constexpr void SetCoord(const double theX, const double theY) noexcept
  {
    x = theX;
    y = theY;
  }

  constexpr void SetX(const double theX) noexcept { x = theX; }

  constexpr void SetY(const double theY) noexcept { y = theY; }

  constexpr double Coord(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 2, nullptr);
    if (theIndex == 1)
    {
      return x;
    }
    return y;
  }

  constexpr double& ChangeCoord(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 2, nullptr);
    if (theIndex == 1)
    {
      return x;
    }
    return y;
  }

  constexpr void Coord(double& theX, double& theY) const noexcept
  {
    theX = x;
    theY = y;
  }

  constexpr double X() const noexcept { return x; }

  constexpr double Y() const noexcept { return y; }

  double Modulus() const { return sqrt(SquareModulus()); }

  constexpr double SquareModulus() const noexcept { return x * x + y * y; }

  bool IsEqual(const gp_XY& theOther, const double theTolerance) const
  {
    return (std::abs(x - theOther.x) < theTolerance) && (std::abs(y - theOther.y) < theTolerance);
  }

  constexpr void Add(const gp_XY& theOther) noexcept
  {
    x += theOther.x;
    y += theOther.y;
  }

  constexpr void operator+=(const gp_XY& theOther) noexcept { Add(theOther); }

  [[nodiscard]] constexpr gp_XY Added(const gp_XY& theOther) const noexcept
  {
    return gp_XY(x + theOther.X(), y + theOther.Y());
  }

  [[nodiscard]] constexpr gp_XY operator+(const gp_XY& theOther) const noexcept
  {
    return Added(theOther);
  }

  [[nodiscard]] constexpr double Crossed(const gp_XY& theOther) const noexcept
  {
    return x * theOther.y - y * theOther.x;
  }

  [[nodiscard]] constexpr double operator^(const gp_XY& theOther) const noexcept
  {
    return Crossed(theOther);
  }

  double CrossMagnitude(const gp_XY& theRight) const
  {
    return std::abs(x * theRight.y - y * theRight.x);
  }

  constexpr double CrossSquareMagnitude(const gp_XY& theRight) const noexcept
  {
    const double aZresult = x * theRight.y - y * theRight.x;
    return aZresult * aZresult;
  }

  constexpr void Divide(const double theScalar)
  {
    x /= theScalar;
    y /= theScalar;
  }

  constexpr void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] constexpr gp_XY Divided(const double theScalar) const
  {
    return gp_XY(x / theScalar, y / theScalar);
  }

  [[nodiscard]] constexpr gp_XY operator/(const double theScalar) const
  {
    return Divided(theScalar);
  }

  constexpr double Dot(const gp_XY& theOther) const noexcept
  {
    return x * theOther.x + y * theOther.y;
  }

  constexpr double operator*(const gp_XY& theOther) const noexcept { return Dot(theOther); }

  constexpr void Multiply(const double theScalar) noexcept
  {
    x *= theScalar;
    y *= theScalar;
  }

  constexpr void operator*=(const double theScalar) noexcept { Multiply(theScalar); }

  constexpr void Multiply(const gp_XY& theOther) noexcept
  {
    x *= theOther.x;
    y *= theOther.y;
  }

  constexpr void operator*=(const gp_XY& theOther) noexcept { Multiply(theOther); }

  constexpr void Multiply(const gp_Mat2d& theMatrix) noexcept;

  constexpr void operator*=(const gp_Mat2d& theMatrix) noexcept { Multiply(theMatrix); }

  [[nodiscard]] constexpr gp_XY Multiplied(const double theScalar) const noexcept
  {
    return gp_XY(x * theScalar, y * theScalar);
  }

  [[nodiscard]] constexpr gp_XY operator*(const double theScalar) const noexcept
  {
    return Multiplied(theScalar);
  }

  [[nodiscard]] constexpr gp_XY Multiplied(const gp_XY& theOther) const noexcept
  {
    return gp_XY(x * theOther.X(), y * theOther.Y());
  }

  [[nodiscard]] constexpr gp_XY Multiplied(const gp_Mat2d& theMatrix) const noexcept
  {
    return gp_XY(theMatrix.myMat[0][0] * x + theMatrix.myMat[0][1] * y,
                 theMatrix.myMat[1][0] * x + theMatrix.myMat[1][1] * y);
  }

  [[nodiscard]] constexpr gp_XY operator*(const gp_Mat2d& theMatrix) const noexcept
  {
    return Multiplied(theMatrix);
  }

  void Normalize();

  [[nodiscard]] gp_XY Normalized() const
  {
    double aD = Modulus();
    Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                        "gp_XY::Normalized() - vector has zero norm");
    return gp_XY(x / aD, y / aD);
  }

  constexpr void Reverse() noexcept
  {
    x = -x;
    y = -y;
  }

  [[nodiscard]] constexpr gp_XY Reversed() const noexcept { return gp_XY(-x, -y); }

  [[nodiscard]] constexpr gp_XY operator-() const noexcept { return Reversed(); }

  constexpr void SetLinearForm(const double theA1,
                               const gp_XY& theXY1,
                               const double theA2,
                               const gp_XY& theXY2) noexcept
  {
    x = theA1 * theXY1.x + theA2 * theXY2.x;
    y = theA1 * theXY1.y + theA2 * theXY2.y;
  }

  constexpr void SetLinearForm(const double theA1,
                               const gp_XY& theXY1,
                               const double theA2,
                               const gp_XY& theXY2,
                               const gp_XY& theXY3) noexcept
  {
    x = theA1 * theXY1.x + theA2 * theXY2.x + theXY3.x;
    y = theA1 * theXY1.y + theA2 * theXY2.y + theXY3.y;
  }

  constexpr void SetLinearForm(const double theA1,
                               const gp_XY& theXY1,
                               const gp_XY& theXY2) noexcept
  {
    x = theA1 * theXY1.x + theXY2.x;
    y = theA1 * theXY1.y + theXY2.y;
  }

  constexpr void SetLinearForm(const gp_XY& theXY1, const gp_XY& theXY2) noexcept
  {
    x = theXY1.x + theXY2.x;
    y = theXY1.y + theXY2.y;
  }

  constexpr void Subtract(const gp_XY& theOther) noexcept
  {
    x -= theOther.x;
    y -= theOther.y;
  }

  constexpr void operator-=(const gp_XY& theOther) noexcept { Subtract(theOther); }

  [[nodiscard]] constexpr gp_XY Subtracted(const gp_XY& theOther) const noexcept
  {
    return gp_XY(x - theOther.x, y - theOther.y);
  }

  [[nodiscard]] constexpr gp_XY operator-(const gp_XY& theOther) const noexcept
  {
    return Subtracted(theOther);
  }

private:
  double x;
  double y;
};

inline constexpr void gp_XY::Multiply(const gp_Mat2d& theMatrix) noexcept
{
  const double aXresult = theMatrix.myMat[0][0] * x + theMatrix.myMat[0][1] * y;
  y                     = theMatrix.myMat[1][0] * x + theMatrix.myMat[1][1] * y;
  x                     = aXresult;
}

inline void gp_XY::Normalize()
{
  double aD = Modulus();
  Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                      "gp_XY::Normalize() - vector has zero norm");
  x = x / aD;
  y = y / aD;
}

inline constexpr gp_XY operator*(const gp_Mat2d& theMatrix, const gp_XY& theCoord1) noexcept
{
  return theCoord1.Multiplied(theMatrix);
}

inline constexpr gp_XY operator*(const double theScalar, const gp_XY& theCoord1) noexcept
{
  return theCoord1.Multiplied(theScalar);
}
