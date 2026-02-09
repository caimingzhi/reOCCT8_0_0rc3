#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Mat.hpp>
#include <gp_Trsf.hpp>
#include <gp_TrsfForm.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>

#ifdef SetForm
  #undef SetForm
#endif

class gp_GTrsf
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_GTrsf() noexcept
      : loc(0.0, 0.0, 0.0),
        shape(gp_Identity),
        scale(1.0)
  {
    matrix.SetScale(1.0);
  }

  gp_GTrsf(const gp_Trsf& theT)
  {
    shape  = theT.Form();
    matrix = theT.matrix;
    loc    = theT.TranslationPart();
    scale  = theT.ScaleFactor();
  }

  constexpr gp_GTrsf(const gp_Mat& theM, const gp_XYZ& theV) noexcept
      : matrix(theM),
        loc(theV),
        shape(gp_Other),
        scale(0.0)
  {
  }

  void SetAffinity(const gp_Ax1& theA1, const double theRatio);

  void SetAffinity(const gp_Ax2& theA2, const double theRatio);

  void SetValue(const int theRow, const int theCol, const double theValue);

  constexpr void SetVectorialPart(const gp_Mat& theMatrix) noexcept
  {
    matrix = theMatrix;
    shape  = gp_Other;
    scale  = 0.0;
  }

  Standard_EXPORT void SetTranslationPart(const gp_XYZ& theCoord);

  void SetTrsf(const gp_Trsf& theT)
  {
    shape  = theT.shape;
    matrix = theT.matrix;
    loc    = theT.loc;
    scale  = theT.scale;
  }

  constexpr bool IsNegative() const noexcept { return matrix.Determinant() < 0.0; }

  constexpr bool IsSingular() const noexcept { return matrix.IsSingular(); }

  constexpr gp_TrsfForm Form() const noexcept { return shape; }

  Standard_EXPORT void SetForm();

  constexpr const gp_XYZ& TranslationPart() const noexcept { return loc; }

  constexpr const gp_Mat& VectorialPart() const noexcept { return matrix; }

  constexpr double Value(const int theRow, const int theCol) const;

  double operator()(const int theRow, const int theCol) const { return Value(theRow, theCol); }

  Standard_EXPORT void Invert();

  [[nodiscard]] gp_GTrsf Inverted() const
  {
    gp_GTrsf aT = *this;
    aT.Invert();
    return aT;
  }

  [[nodiscard]] gp_GTrsf Multiplied(const gp_GTrsf& theT) const
  {
    gp_GTrsf aTres = *this;
    aTres.Multiply(theT);
    return aTres;
  }

  [[nodiscard]] gp_GTrsf operator*(const gp_GTrsf& theT) const { return Multiplied(theT); }

  Standard_EXPORT void Multiply(const gp_GTrsf& theT);

  void operator*=(const gp_GTrsf& theT) { Multiply(theT); }

  Standard_EXPORT void PreMultiply(const gp_GTrsf& theT);

  Standard_EXPORT void Power(const int theN);

  [[nodiscard]] gp_GTrsf Powered(const int theN) const
  {
    gp_GTrsf aT = *this;
    aT.Power(theN);
    return aT;
  }

  constexpr void Transforms(gp_XYZ& theCoord) const noexcept;

  constexpr void Transforms(double& theX, double& theY, double& theZ) const noexcept;

  gp_Trsf Trsf() const;

  template <class T>
  void GetMat4(NCollection_Mat4<T>& theMat) const
  {
    if (shape == gp_Identity)
    {
      theMat.InitIdentity();
      return;
    }

    theMat.SetValue(0, 0, static_cast<T>(Value(1, 1)));
    theMat.SetValue(0, 1, static_cast<T>(Value(1, 2)));
    theMat.SetValue(0, 2, static_cast<T>(Value(1, 3)));
    theMat.SetValue(0, 3, static_cast<T>(Value(1, 4)));
    theMat.SetValue(1, 0, static_cast<T>(Value(2, 1)));
    theMat.SetValue(1, 1, static_cast<T>(Value(2, 2)));
    theMat.SetValue(1, 2, static_cast<T>(Value(2, 3)));
    theMat.SetValue(1, 3, static_cast<T>(Value(2, 4)));
    theMat.SetValue(2, 0, static_cast<T>(Value(3, 1)));
    theMat.SetValue(2, 1, static_cast<T>(Value(3, 2)));
    theMat.SetValue(2, 2, static_cast<T>(Value(3, 3)));
    theMat.SetValue(2, 3, static_cast<T>(Value(3, 4)));
    theMat.SetValue(3, 0, static_cast<T>(0));
    theMat.SetValue(3, 1, static_cast<T>(0));
    theMat.SetValue(3, 2, static_cast<T>(0));
    theMat.SetValue(3, 3, static_cast<T>(1));
  }

  template <class T>
  void SetMat4(const NCollection_Mat4<T>& theMat)
  {
    shape = gp_Other;
    scale = 0.0;
    matrix.SetValue(1, 1, theMat.GetValue(0, 0));
    matrix.SetValue(1, 2, theMat.GetValue(0, 1));
    matrix.SetValue(1, 3, theMat.GetValue(0, 2));
    matrix.SetValue(2, 1, theMat.GetValue(1, 0));
    matrix.SetValue(2, 2, theMat.GetValue(1, 1));
    matrix.SetValue(2, 3, theMat.GetValue(1, 2));
    matrix.SetValue(3, 1, theMat.GetValue(2, 0));
    matrix.SetValue(3, 2, theMat.GetValue(2, 1));
    matrix.SetValue(3, 3, theMat.GetValue(2, 2));
    loc.SetCoord(theMat.GetValue(0, 3), theMat.GetValue(1, 3), theMat.GetValue(2, 3));
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Mat      matrix;
  gp_XYZ      loc;
  gp_TrsfForm shape;
  double      scale;
};

inline void gp_GTrsf::SetAffinity(const gp_Ax1& theA1, const double theRatio)
{
  shape = gp_Other;
  scale = 0.0;
  matrix.SetDot(theA1.Direction().XYZ());
  matrix.Multiply(1.0 - theRatio);
  matrix.SetDiagonal(matrix.Value(1, 1) + theRatio,
                     matrix.Value(2, 2) + theRatio,
                     matrix.Value(3, 3) + theRatio);
  loc = theA1.Location().XYZ();
  loc.Reverse();
  loc.Multiply(matrix);
  loc.Add(theA1.Location().XYZ());
}

inline void gp_GTrsf::SetAffinity(const gp_Ax2& theA2, const double theRatio)
{
  shape = gp_Other;
  scale = 0.0;
  matrix.SetDot(theA2.Direction().XYZ());
  matrix.Multiply(theRatio - 1.);
  loc = theA2.Location().XYZ();
  loc.Reverse();
  loc.Multiply(matrix);
  matrix.SetDiagonal(matrix.Value(1, 1) + 1., matrix.Value(2, 2) + 1., matrix.Value(3, 3) + 1.);
}

inline void gp_GTrsf::SetValue(const int theRow, const int theCol, const double theValue)
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 4, " ");
  if (theCol == 4)
  {
    loc.SetCoord(theRow, theValue);
    if (shape == gp_Identity)
    {
      shape = gp_Translation;
    }
    return;
  }
  else
  {
    if (!(shape == gp_Other) && !(scale == 1.0))
    {
      matrix.Multiply(scale);
    }
    matrix.SetValue(theRow, theCol, theValue);
    shape = gp_Other;
    scale = 0.0;
    return;
  }
}

inline constexpr double gp_GTrsf::Value(const int theRow, const int theCol) const
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 4, " ");
  if (theCol == 4)
  {
    return loc.Coord(theRow);
  }
  if (shape == gp_Other)
  {
    return matrix.myMat[theRow - 1][theCol - 1];
  }
  return scale * matrix.myMat[theRow - 1][theCol - 1];
}

inline constexpr void gp_GTrsf::Transforms(gp_XYZ& theCoord) const noexcept
{
  theCoord.Multiply(matrix);
  if (!(shape == gp_Other) && !(scale == 1.0))
  {
    theCoord.Multiply(scale);
  }
  theCoord.Add(loc);
}

inline constexpr void gp_GTrsf::Transforms(double& theX, double& theY, double& theZ) const noexcept
{
  gp_XYZ aTriplet(theX, theY, theZ);
  aTriplet.Multiply(matrix);
  if (!(shape == gp_Other) && !(scale == 1.0))
  {
    aTriplet.Multiply(scale);
  }
  aTriplet.Add(loc);
  aTriplet.Coord(theX, theY, theZ);
}

inline gp_Trsf gp_GTrsf::Trsf() const
{
  if (Form() == gp_Other)
  {
    throw Standard_ConstructionError("gp_GTrsf::Trsf() - non-orthogonal GTrsf");
  }
  gp_Trsf aT;
  aT.shape  = shape;
  aT.scale  = scale;
  aT.matrix = matrix;
  aT.loc    = loc;
  return aT;
}
