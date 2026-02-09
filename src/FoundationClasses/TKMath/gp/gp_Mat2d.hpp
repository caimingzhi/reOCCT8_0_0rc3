#pragma once

#include <gp.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>

class gp_XY;

class gp_Mat2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Mat2d() noexcept
      : myMat{{0.0, 0.0}, {0.0, 0.0}}
  {
  }

  Standard_EXPORT gp_Mat2d(const gp_XY& theCol1, const gp_XY& theCol2);

  Standard_EXPORT void SetCol(const int theCol, const gp_XY& theValue);

  Standard_EXPORT void SetCols(const gp_XY& theCol1, const gp_XY& theCol2);

  constexpr void SetDiagonal(const double theX1, const double theX2) noexcept
  {
    myMat[0][0] = theX1;
    myMat[1][1] = theX2;
  }

  constexpr void SetIdentity() noexcept
  {
    myMat[0][0] = myMat[1][1] = 1.0;
    myMat[0][1] = myMat[1][0] = 0.0;
  }

  void SetRotation(const double theAng);

  Standard_EXPORT void SetRow(const int theRow, const gp_XY& theValue);

  Standard_EXPORT void SetRows(const gp_XY& theRow1, const gp_XY& theRow2);

  constexpr void SetScale(const double theS) noexcept
  {
    myMat[0][0] = myMat[1][1] = theS;
    myMat[0][1] = myMat[1][0] = 0.0;
  }

  void SetValue(const int theRow, const int theCol, const double theValue)
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 2, " ");
    myMat[theRow - 1][theCol - 1] = theValue;
  }

  Standard_EXPORT gp_XY Column(const int theCol) const;

  constexpr double Determinant() const noexcept
  {
    return myMat[0][0] * myMat[1][1] - myMat[1][0] * myMat[0][1];
  }

  Standard_EXPORT gp_XY Diagonal() const;

  Standard_EXPORT gp_XY Row(const int theRow) const;

  const double& Value(const int theRow, const int theCol) const
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 2, " ");
    return myMat[theRow - 1][theCol - 1];
  }

  const double& operator()(const int theRow, const int theCol) const
  {
    return Value(theRow, theCol);
  }

  double& ChangeValue(const int theRow, const int theCol)
  {
    Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 2, " ");
    return myMat[theRow - 1][theCol - 1];
  }

  double& operator()(const int theRow, const int theCol) { return ChangeValue(theRow, theCol); }

  constexpr bool IsSingular() const noexcept
  {
    double aDet = Determinant();
    if (aDet < 0)
    {
      aDet = -aDet;
    }
    return aDet <= gp::Resolution();
  }

  constexpr void Add(const gp_Mat2d& Other) noexcept;

  constexpr void operator+=(const gp_Mat2d& theOther) noexcept { Add(theOther); }

  [[nodiscard]] constexpr gp_Mat2d Added(const gp_Mat2d& theOther) const noexcept;

  [[nodiscard]] constexpr gp_Mat2d operator+(const gp_Mat2d& theOther) const noexcept
  {
    return Added(theOther);
  }

  constexpr void Divide(const double theScalar);

  constexpr void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] constexpr gp_Mat2d Divided(const double theScalar) const;

  [[nodiscard]] constexpr gp_Mat2d operator/(const double theScalar) const
  {
    return Divided(theScalar);
  }

  Standard_EXPORT void Invert();

  [[nodiscard]] gp_Mat2d Inverted() const
  {
    gp_Mat2d aNewMat = *this;
    aNewMat.Invert();
    return aNewMat;
  }

  [[nodiscard]] constexpr gp_Mat2d Multiplied(const gp_Mat2d& theOther) const noexcept
  {
    gp_Mat2d aNewMat2d = *this;
    aNewMat2d.Multiply(theOther);
    return aNewMat2d;
  }

  [[nodiscard]] constexpr gp_Mat2d operator*(const gp_Mat2d& theOther) const noexcept
  {
    return Multiplied(theOther);
  }

  constexpr void Multiply(const gp_Mat2d& theOther) noexcept;

  constexpr void PreMultiply(const gp_Mat2d& theOther) noexcept;

  [[nodiscard]] constexpr gp_Mat2d Multiplied(const double theScalar) const noexcept;

  [[nodiscard]] constexpr gp_Mat2d operator*(const double theScalar) const noexcept
  {
    return Multiplied(theScalar);
  }

  constexpr void Multiply(const double theScalar) noexcept;

  constexpr void operator*=(const double theScalar) noexcept { Multiply(theScalar); }

  Standard_EXPORT void Power(const int theN);

  [[nodiscard]] gp_Mat2d Powered(const int theN) const
  {
    gp_Mat2d aMat2dN = *this;
    aMat2dN.Power(theN);
    return aMat2dN;
  }

  constexpr void Subtract(const gp_Mat2d& theOther) noexcept;

  constexpr void operator-=(const gp_Mat2d& theOther) noexcept { Subtract(theOther); }

  [[nodiscard]] constexpr gp_Mat2d Subtracted(const gp_Mat2d& theOther) const noexcept;

  [[nodiscard]] constexpr gp_Mat2d operator-(const gp_Mat2d& theOther) const noexcept
  {
    return Subtracted(theOther);
  }

  constexpr void Transpose() noexcept;

  [[nodiscard]] constexpr gp_Mat2d Transposed() const noexcept;

  friend class gp_Trsf2d;
  friend class gp_GTrsf2d;
  friend class gp_XY;

private:
  double myMat[2][2];
};

inline void gp_Mat2d::SetRotation(const double theAng)
{
  double aSinA = sin(theAng);
  double aCosA = cos(theAng);
  myMat[0][0] = myMat[1][1] = aCosA;
  myMat[0][1]               = -aSinA;
  myMat[1][0]               = aSinA;
}

inline constexpr void gp_Mat2d::Add(const gp_Mat2d& theOther) noexcept
{
  myMat[0][0] += theOther.myMat[0][0];
  myMat[0][1] += theOther.myMat[0][1];
  myMat[1][0] += theOther.myMat[1][0];
  myMat[1][1] += theOther.myMat[1][1];
}

inline constexpr gp_Mat2d gp_Mat2d::Added(const gp_Mat2d& theOther) const noexcept
{
  gp_Mat2d aNewMat2d;
  aNewMat2d.myMat[0][0] = myMat[0][0] + theOther.myMat[0][0];
  aNewMat2d.myMat[0][1] = myMat[0][1] + theOther.myMat[0][1];
  aNewMat2d.myMat[1][0] = myMat[1][0] + theOther.myMat[1][0];
  aNewMat2d.myMat[1][1] = myMat[1][1] + theOther.myMat[1][1];
  return aNewMat2d;
}

inline constexpr void gp_Mat2d::Divide(const double theScalar)
{
  myMat[0][0] /= theScalar;
  myMat[0][1] /= theScalar;
  myMat[1][0] /= theScalar;
  myMat[1][1] /= theScalar;
}

inline constexpr gp_Mat2d gp_Mat2d::Divided(const double theScalar) const
{
  gp_Mat2d aNewMat2d;
  aNewMat2d.myMat[0][0] = myMat[0][0] / theScalar;
  aNewMat2d.myMat[0][1] = myMat[0][1] / theScalar;
  aNewMat2d.myMat[1][0] = myMat[1][0] / theScalar;
  aNewMat2d.myMat[1][1] = myMat[1][1] / theScalar;
  return aNewMat2d;
}

inline constexpr void gp_Mat2d::Multiply(const gp_Mat2d& theOther) noexcept
{
  const double aT00 = myMat[0][0] * theOther.myMat[0][0] + myMat[0][1] * theOther.myMat[1][0];
  const double aT10 = myMat[1][0] * theOther.myMat[0][0] + myMat[1][1] * theOther.myMat[1][0];
  myMat[0][1]       = myMat[0][0] * theOther.myMat[0][1] + myMat[0][1] * theOther.myMat[1][1];
  myMat[1][1]       = myMat[1][0] * theOther.myMat[0][1] + myMat[1][1] * theOther.myMat[1][1];
  myMat[0][0]       = aT00;
  myMat[1][0]       = aT10;
}

inline constexpr void gp_Mat2d::PreMultiply(const gp_Mat2d& theOther) noexcept
{
  const double aT00 = theOther.myMat[0][0] * myMat[0][0] + theOther.myMat[0][1] * myMat[1][0];
  myMat[1][0]       = theOther.myMat[1][0] * myMat[0][0] + theOther.myMat[1][1] * myMat[1][0];
  const double aT01 = theOther.myMat[0][0] * myMat[0][1] + theOther.myMat[0][1] * myMat[1][1];
  myMat[1][1]       = theOther.myMat[1][0] * myMat[0][1] + theOther.myMat[1][1] * myMat[1][1];
  myMat[0][0]       = aT00;
  myMat[0][1]       = aT01;
}

inline constexpr gp_Mat2d gp_Mat2d::Multiplied(const double theScalar) const noexcept
{
  gp_Mat2d aNewMat2d;
  aNewMat2d.myMat[0][0] = myMat[0][0] * theScalar;
  aNewMat2d.myMat[0][1] = myMat[0][1] * theScalar;
  aNewMat2d.myMat[1][0] = myMat[1][0] * theScalar;
  aNewMat2d.myMat[1][1] = myMat[1][1] * theScalar;
  return aNewMat2d;
}

inline constexpr void gp_Mat2d::Multiply(const double theScalar) noexcept
{
  myMat[0][0] *= theScalar;
  myMat[0][1] *= theScalar;
  myMat[1][0] *= theScalar;
  myMat[1][1] *= theScalar;
}

inline constexpr void gp_Mat2d::Subtract(const gp_Mat2d& theOther) noexcept
{
  myMat[0][0] -= theOther.myMat[0][0];
  myMat[0][1] -= theOther.myMat[0][1];
  myMat[1][0] -= theOther.myMat[1][0];
  myMat[1][1] -= theOther.myMat[1][1];
}

inline constexpr gp_Mat2d gp_Mat2d::Subtracted(const gp_Mat2d& theOther) const noexcept
{
  gp_Mat2d aNewMat2d;
  aNewMat2d.myMat[0][0] = myMat[0][0] - theOther.myMat[0][0];
  aNewMat2d.myMat[0][1] = myMat[0][1] - theOther.myMat[0][1];
  aNewMat2d.myMat[1][0] = myMat[1][0] - theOther.myMat[1][0];
  aNewMat2d.myMat[1][1] = myMat[1][1] - theOther.myMat[1][1];
  return aNewMat2d;
}

inline constexpr void gp_Mat2d::Transpose() noexcept
{
  const double aTemp = myMat[0][1];
  myMat[0][1]        = myMat[1][0];
  myMat[1][0]        = aTemp;
}

inline constexpr gp_Mat2d gp_Mat2d::Transposed() const noexcept
{
  gp_Mat2d aNewMat2d;
  aNewMat2d.myMat[1][0] = myMat[0][1];
  aNewMat2d.myMat[0][1] = myMat[1][0];
  aNewMat2d.myMat[0][0] = myMat[0][0];
  aNewMat2d.myMat[1][1] = myMat[1][1];
  return aNewMat2d;
}

inline constexpr gp_Mat2d operator*(const double theScalar, const gp_Mat2d& theMat2D) noexcept
{
  return theMat2D.Multiplied(theScalar);
}
