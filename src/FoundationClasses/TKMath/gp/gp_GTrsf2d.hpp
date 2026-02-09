#pragma once

#include <gp_Ax2d.hpp>
#include <gp_Mat2d.hpp>
#include <gp_TrsfForm.hpp>
#include <gp_XY.hpp>
#include <Standard_OutOfRange.hpp>

class gp_GTrsf2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_GTrsf2d() noexcept
      : loc(0.0, 0.0),
        shape(gp_Identity),
        scale(1.0)
  {
    matrix.SetScale(1.0);
  }

  gp_GTrsf2d(const gp_Trsf2d& theT);

  constexpr gp_GTrsf2d(const gp_Mat2d& theM, const gp_XY& theV) noexcept
      : matrix(theM),
        loc(theV),
        shape(gp_Other),
        scale(0.0)
  {
  }

  Standard_EXPORT void SetAffinity(const gp_Ax2d& theA, const double theRatio);

  void SetValue(const int theRow, const int theCol, const double theValue);

  Standard_EXPORT void SetTranslationPart(const gp_XY& theCoord);

  void SetTrsf2d(const gp_Trsf2d& theT);

  constexpr void SetVectorialPart(const gp_Mat2d& theMatrix) noexcept
  {
    matrix = theMatrix;
    shape  = gp_Other;
    scale  = 0.0;
  }

  constexpr bool IsNegative() const noexcept { return matrix.Determinant() < 0.0; }

  constexpr bool IsSingular() const noexcept { return matrix.IsSingular(); }

  constexpr gp_TrsfForm Form() const noexcept { return shape; }

  constexpr const gp_XY& TranslationPart() const noexcept { return loc; }

  constexpr const gp_Mat2d& VectorialPart() const noexcept { return matrix; }

  constexpr double Value(const int theRow, const int theCol) const;

  double operator()(const int theRow, const int theCol) const { return Value(theRow, theCol); }

  Standard_EXPORT void Invert();

  [[nodiscard]] gp_GTrsf2d Inverted() const
  {
    gp_GTrsf2d aT = *this;
    aT.Invert();
    return aT;
  }

  [[nodiscard]] gp_GTrsf2d Multiplied(const gp_GTrsf2d& theT) const
  {
    gp_GTrsf2d aTres = *this;
    aTres.Multiply(theT);
    return aTres;
  }

  [[nodiscard]] gp_GTrsf2d operator*(const gp_GTrsf2d& theT) const { return Multiplied(theT); }

  Standard_EXPORT void Multiply(const gp_GTrsf2d& theT);

  void operator*=(const gp_GTrsf2d& theT) { Multiply(theT); }

  Standard_EXPORT void PreMultiply(const gp_GTrsf2d& theT);

  Standard_EXPORT void Power(const int theN);

  [[nodiscard]] gp_GTrsf2d Powered(const int theN) const
  {
    gp_GTrsf2d aT = *this;
    aT.Power(theN);
    return aT;
  }

  constexpr void Transforms(gp_XY& theCoord) const noexcept;

  [[nodiscard]] constexpr gp_XY Transformed(const gp_XY& theCoord) const noexcept
  {
    gp_XY aNewCoord = theCoord;
    Transforms(aNewCoord);
    return aNewCoord;
  }

  constexpr void Transforms(double& theX, double& theY) const noexcept;

  Standard_EXPORT gp_Trsf2d Trsf2d() const;

private:
  gp_Mat2d    matrix;
  gp_XY       loc;
  gp_TrsfForm shape;
  double      scale;
};

#include <gp_Trsf2d.hpp>

inline void gp_GTrsf2d::SetTrsf2d(const gp_Trsf2d& theT)
{
  shape  = theT.shape;
  matrix = theT.matrix;
  loc    = theT.loc;
  scale  = theT.scale;
}

inline gp_GTrsf2d::gp_GTrsf2d(const gp_Trsf2d& theT)
{
  shape  = theT.shape;
  matrix = theT.matrix;
  loc    = theT.loc;
  scale  = theT.scale;
}

inline void gp_GTrsf2d::SetValue(const int theRow, const int theCol, const double theValue)
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 3, " ");
  if (theCol == 3)
  {
    loc.SetCoord(theRow, theValue);
  }
  else
  {
    matrix.SetValue(theRow, theCol, theValue);
  }
  shape = gp_Other;
}

inline constexpr double gp_GTrsf2d::Value(const int theRow, const int theCol) const
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 3, " ");
  if (theCol == 3)
  {
    return loc.Coord(theRow);
  }
  if (shape == gp_Other)
  {
    return matrix.myMat[theRow - 1][theCol - 1];
  }
  return scale * matrix.myMat[theRow - 1][theCol - 1];
}

inline constexpr void gp_GTrsf2d::Transforms(gp_XY& theCoord) const noexcept
{
  theCoord.Multiply(matrix);
  if (!(shape == gp_Other) && !(scale == 1.0))
  {
    theCoord.Multiply(scale);
  }
  theCoord.Add(loc);
}

inline constexpr void gp_GTrsf2d::Transforms(double& theX, double& theY) const noexcept
{
  gp_XY aDoublet(theX, theY);
  aDoublet.Multiply(matrix);
  if (!(shape == gp_Other) && !(scale == 1.0))
  {
    aDoublet.Multiply(scale);
  }
  aDoublet.Add(loc);
  aDoublet.Coord(theX, theY);
}
