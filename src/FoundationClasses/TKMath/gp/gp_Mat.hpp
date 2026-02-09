#pragma once

#include <gp.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_OStream.hpp>
#include <Standard_ConstructionError.hpp>

class gp_XYZ;

class gp_Mat
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Mat() noexcept
      : myMat{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}
  {
  }

  constexpr gp_Mat(const double theA11,
                   const double theA12,
                   const double theA13,
                   const double theA21,
                   const double theA22,
                   const double theA23,
                   const double theA31,
                   const double theA32,
                   const double theA33) noexcept;

  Standard_EXPORT gp_Mat(const gp_XYZ& theCol1, const gp_XYZ& theCol2, const gp_XYZ& theCol3);

  Standard_EXPORT void SetCol(const int theCol, const gp_XYZ& theValue);

  Standard_EXPORT void SetCols(const gp_XYZ& theCol1, const gp_XYZ& theCol2, const gp_XYZ& theCol3);

  Standard_EXPORT void SetCross(const gp_XYZ& theRef);

  constexpr void SetDiagonal(const double theX1, const double theX2, const double theX3) noexcept
  {
    myMat[0][0] = theX1;
    myMat[1][1] = theX2;
    myMat[2][2] = theX3;
  }

  Standard_EXPORT void SetDot(const gp_XYZ& theRef) noexcept;

  constexpr void SetIdentity() noexcept
  {
    myMat[0][0] = myMat[1][1] = myMat[2][2] = 1.0;
    myMat[0][1] = myMat[0][2] = myMat[1][0] = myMat[1][2] = myMat[2][0] = myMat[2][1] = 0.0;
  }

  Standard_EXPORT void SetRotation(const gp_XYZ& theAxis, const double theAng);

  Standard_EXPORT void SetRow(const int theRow, const gp_XYZ& theValue);

  Standard_EXPORT void SetRows(const gp_XYZ& theRow1, const gp_XYZ& theRow2, const gp_XYZ& theRow3);

  constexpr void SetScale(const double theS) noexcept
  {
    myMat[0][0] = myMat[1][1] = myMat[2][2] = theS;
    myMat[0][1] = myMat[0][2] = myMat[1][0] = myMat[1][2] = myMat[2][0] = myMat[2][1] = 0.0;
  }

  void SetValue(const int theRow, const int theCol, const double theValue)
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 3, " ");
    myMat[theRow - 1][theCol - 1] = theValue;
  }

  Standard_EXPORT gp_XYZ Column(const int theCol) const;

  constexpr double Determinant() const noexcept
  {
    const double a00 = myMat[0][0], a01 = myMat[0][1], a02 = myMat[0][2];
    const double a10 = myMat[1][0], a11 = myMat[1][1], a12 = myMat[1][2];
    const double a20 = myMat[2][0], a21 = myMat[2][1], a22 = myMat[2][2];

    return a00 * (a11 * a22 - a21 * a12) - a01 * (a10 * a22 - a20 * a12)
           + a02 * (a10 * a21 - a20 * a11);
  }

  Standard_EXPORT gp_XYZ Diagonal() const;

  Standard_EXPORT gp_XYZ Row(const int theRow) const;

  const double& Value(const int theRow, const int theCol) const
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 3, " ");
    return myMat[theRow - 1][theCol - 1];
  }

  const double& operator()(const int theRow, const int theCol) const
  {
    return Value(theRow, theCol);
  }

  double& ChangeValue(const int theRow, const int theCol)
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 3, " ");
    return myMat[theRow - 1][theCol - 1];
  }

  double& operator()(const int theRow, const int theCol) { return ChangeValue(theRow, theCol); }

  constexpr bool IsSingular() const noexcept
  {

    const double aDet = Determinant();
    return (aDet < 0.0 ? -aDet : aDet) <= gp::Resolution();
  }

  constexpr void Add(const gp_Mat& theOther) noexcept;

  constexpr void operator+=(const gp_Mat& theOther) noexcept { Add(theOther); }

  [[nodiscard]] constexpr gp_Mat Added(const gp_Mat& theOther) const noexcept;

  [[nodiscard]] constexpr gp_Mat operator+(const gp_Mat& theOther) const noexcept
  {
    return Added(theOther);
  }

  constexpr void Divide(const double theScalar);

  constexpr void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] constexpr gp_Mat Divided(const double theScalar) const;

  [[nodiscard]] constexpr gp_Mat operator/(const double theScalar) const
  {
    return Divided(theScalar);
  }

  Standard_EXPORT void Invert();

  [[nodiscard]] Standard_EXPORT gp_Mat Inverted() const;

  [[nodiscard]] constexpr gp_Mat Multiplied(const gp_Mat& theOther) const noexcept
  {
    gp_Mat aNewMat = *this;
    aNewMat.Multiply(theOther);
    return aNewMat;
  }

  [[nodiscard]] constexpr gp_Mat operator*(const gp_Mat& theOther) const noexcept
  {
    return Multiplied(theOther);
  }

  constexpr void Multiply(const gp_Mat& theOther) noexcept;

  constexpr void operator*=(const gp_Mat& theOther) noexcept { Multiply(theOther); }

  constexpr void PreMultiply(const gp_Mat& theOther) noexcept;

  [[nodiscard]] constexpr gp_Mat Multiplied(const double theScalar) const noexcept;

  [[nodiscard]] constexpr gp_Mat operator*(const double theScalar) const noexcept
  {
    return Multiplied(theScalar);
  }

  constexpr void Multiply(const double theScalar) noexcept;

  constexpr void operator*=(const double theScalar) noexcept { Multiply(theScalar); }

  Standard_EXPORT void Power(const int N);

  [[nodiscard]] gp_Mat Powered(const int theN) const
  {
    gp_Mat aMatN = *this;
    aMatN.Power(theN);
    return aMatN;
  }

  constexpr void Subtract(const gp_Mat& theOther) noexcept;

  constexpr void operator-=(const gp_Mat& theOther) noexcept { Subtract(theOther); }

  [[nodiscard]] constexpr gp_Mat Subtracted(const gp_Mat& theOther) const noexcept;

  [[nodiscard]] constexpr gp_Mat operator-(const gp_Mat& theOther) const noexcept
  {
    return Subtracted(theOther);
  }

  void Transpose();

  [[nodiscard]] gp_Mat Transposed() const
  {
    gp_Mat aNewMat = *this;
    aNewMat.Transpose();
    return aNewMat;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class gp_XYZ;
  friend class gp_Trsf;
  friend class gp_GTrsf;

private:
  double myMat[3][3];
};

inline constexpr gp_Mat::gp_Mat(const double theA11,
                                const double theA12,
                                const double theA13,
                                const double theA21,
                                const double theA22,
                                const double theA23,
                                const double theA31,
                                const double theA32,
                                const double theA33) noexcept
    : myMat{{theA11, theA12, theA13}, {theA21, theA22, theA23}, {theA31, theA32, theA33}}
{
}

inline constexpr void gp_Mat::Add(const gp_Mat& theOther) noexcept
{
  myMat[0][0] += theOther.myMat[0][0];
  myMat[0][1] += theOther.myMat[0][1];
  myMat[0][2] += theOther.myMat[0][2];
  myMat[1][0] += theOther.myMat[1][0];
  myMat[1][1] += theOther.myMat[1][1];
  myMat[1][2] += theOther.myMat[1][2];
  myMat[2][0] += theOther.myMat[2][0];
  myMat[2][1] += theOther.myMat[2][1];
  myMat[2][2] += theOther.myMat[2][2];
}

inline constexpr gp_Mat gp_Mat::Added(const gp_Mat& theOther) const noexcept
{
  gp_Mat aNewMat(*this);
  aNewMat.Add(theOther);
  return aNewMat;
}

inline constexpr void gp_Mat::Divide(const double theScalar)
{
  Standard_ConstructionError_Raise_if((theScalar < 0.0 ? -theScalar : theScalar)
                                        <= gp::Resolution(),
                                      "gp_Mat : Divide by 0");
  const double anUnSurScalar = 1.0 / theScalar;
  myMat[0][0] *= anUnSurScalar;
  myMat[0][1] *= anUnSurScalar;
  myMat[0][2] *= anUnSurScalar;
  myMat[1][0] *= anUnSurScalar;
  myMat[1][1] *= anUnSurScalar;
  myMat[1][2] *= anUnSurScalar;
  myMat[2][0] *= anUnSurScalar;
  myMat[2][1] *= anUnSurScalar;
  myMat[2][2] *= anUnSurScalar;
}

inline constexpr gp_Mat gp_Mat::Divided(const double theScalar) const
{
  gp_Mat aNewMat(*this);
  aNewMat.Divide(theScalar);
  return aNewMat;
}

inline constexpr void gp_Mat::Multiply(const gp_Mat& theOther) noexcept
{
  const double aT00 = myMat[0][0] * theOther.myMat[0][0] + myMat[0][1] * theOther.myMat[1][0]
                      + myMat[0][2] * theOther.myMat[2][0];
  const double aT01 = myMat[0][0] * theOther.myMat[0][1] + myMat[0][1] * theOther.myMat[1][1]
                      + myMat[0][2] * theOther.myMat[2][1];
  const double aT02 = myMat[0][0] * theOther.myMat[0][2] + myMat[0][1] * theOther.myMat[1][2]
                      + myMat[0][2] * theOther.myMat[2][2];
  const double aT10 = myMat[1][0] * theOther.myMat[0][0] + myMat[1][1] * theOther.myMat[1][0]
                      + myMat[1][2] * theOther.myMat[2][0];
  const double aT11 = myMat[1][0] * theOther.myMat[0][1] + myMat[1][1] * theOther.myMat[1][1]
                      + myMat[1][2] * theOther.myMat[2][1];
  const double aT12 = myMat[1][0] * theOther.myMat[0][2] + myMat[1][1] * theOther.myMat[1][2]
                      + myMat[1][2] * theOther.myMat[2][2];
  const double aT20 = myMat[2][0] * theOther.myMat[0][0] + myMat[2][1] * theOther.myMat[1][0]
                      + myMat[2][2] * theOther.myMat[2][0];
  const double aT21 = myMat[2][0] * theOther.myMat[0][1] + myMat[2][1] * theOther.myMat[1][1]
                      + myMat[2][2] * theOther.myMat[2][1];
  const double aT22 = myMat[2][0] * theOther.myMat[0][2] + myMat[2][1] * theOther.myMat[1][2]
                      + myMat[2][2] * theOther.myMat[2][2];
  myMat[0][0] = aT00;
  myMat[0][1] = aT01;
  myMat[0][2] = aT02;
  myMat[1][0] = aT10;
  myMat[1][1] = aT11;
  myMat[1][2] = aT12;
  myMat[2][0] = aT20;
  myMat[2][1] = aT21;
  myMat[2][2] = aT22;
}

inline constexpr void gp_Mat::PreMultiply(const gp_Mat& theOther) noexcept
{
  const double aT00 = theOther.myMat[0][0] * myMat[0][0] + theOther.myMat[0][1] * myMat[1][0]
                      + theOther.myMat[0][2] * myMat[2][0];
  const double aT01 = theOther.myMat[0][0] * myMat[0][1] + theOther.myMat[0][1] * myMat[1][1]
                      + theOther.myMat[0][2] * myMat[2][1];
  const double aT02 = theOther.myMat[0][0] * myMat[0][2] + theOther.myMat[0][1] * myMat[1][2]
                      + theOther.myMat[0][2] * myMat[2][2];
  const double aT10 = theOther.myMat[1][0] * myMat[0][0] + theOther.myMat[1][1] * myMat[1][0]
                      + theOther.myMat[1][2] * myMat[2][0];
  const double aT11 = theOther.myMat[1][0] * myMat[0][1] + theOther.myMat[1][1] * myMat[1][1]
                      + theOther.myMat[1][2] * myMat[2][1];
  const double aT12 = theOther.myMat[1][0] * myMat[0][2] + theOther.myMat[1][1] * myMat[1][2]
                      + theOther.myMat[1][2] * myMat[2][2];
  const double aT20 = theOther.myMat[2][0] * myMat[0][0] + theOther.myMat[2][1] * myMat[1][0]
                      + theOther.myMat[2][2] * myMat[2][0];
  const double aT21 = theOther.myMat[2][0] * myMat[0][1] + theOther.myMat[2][1] * myMat[1][1]
                      + theOther.myMat[2][2] * myMat[2][1];
  const double aT22 = theOther.myMat[2][0] * myMat[0][2] + theOther.myMat[2][1] * myMat[1][2]
                      + theOther.myMat[2][2] * myMat[2][2];
  myMat[0][0] = aT00;
  myMat[0][1] = aT01;
  myMat[0][2] = aT02;
  myMat[1][0] = aT10;
  myMat[1][1] = aT11;
  myMat[1][2] = aT12;
  myMat[2][0] = aT20;
  myMat[2][1] = aT21;
  myMat[2][2] = aT22;
}

inline constexpr gp_Mat gp_Mat::Multiplied(const double theScalar) const noexcept
{
  gp_Mat aNewMat(*this);
  aNewMat.Multiply(theScalar);
  return aNewMat;
}

inline constexpr void gp_Mat::Multiply(const double theScalar) noexcept
{
  myMat[0][0] *= theScalar;
  myMat[0][1] *= theScalar;
  myMat[0][2] *= theScalar;
  myMat[1][0] *= theScalar;
  myMat[1][1] *= theScalar;
  myMat[1][2] *= theScalar;
  myMat[2][0] *= theScalar;
  myMat[2][1] *= theScalar;
  myMat[2][2] *= theScalar;
}

inline constexpr void gp_Mat::Subtract(const gp_Mat& theOther) noexcept
{
  myMat[0][0] -= theOther.myMat[0][0];
  myMat[0][1] -= theOther.myMat[0][1];
  myMat[0][2] -= theOther.myMat[0][2];
  myMat[1][0] -= theOther.myMat[1][0];
  myMat[1][1] -= theOther.myMat[1][1];
  myMat[1][2] -= theOther.myMat[1][2];
  myMat[2][0] -= theOther.myMat[2][0];
  myMat[2][1] -= theOther.myMat[2][1];
  myMat[2][2] -= theOther.myMat[2][2];
}

inline constexpr gp_Mat gp_Mat::Subtracted(const gp_Mat& theOther) const noexcept
{
  gp_Mat aNewMat(*this);
  aNewMat.Subtract(theOther);
  return aNewMat;
}

#if defined(__APPLE__) && (__apple_build_version__ > 9020000)
__attribute__((optnone))
#endif
inline void
  gp_Mat::Transpose()
{
  std::swap(myMat[0][1], myMat[1][0]);
  std::swap(myMat[0][2], myMat[2][0]);
  std::swap(myMat[1][2], myMat[2][1]);
}

inline constexpr gp_Mat operator*(const double theScalar, const gp_Mat& theMat3D) noexcept
{
  return theMat3D.Multiplied(theScalar);
}
