#pragma once

#include <gp_TrsfForm.hpp>
#include <gp_Mat2d.hpp>
#include <gp_XY.hpp>
#include <Standard_OutOfRange.hpp>

class gp_Trsf;
class gp_Pnt2d;
class gp_Ax2d;
class gp_Vec2d;

class gp_Trsf2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Trsf2d() noexcept;

  gp_Trsf2d(const gp_Trsf& theT);

  void SetMirror(const gp_Pnt2d& theP) noexcept;

  Standard_EXPORT void SetMirror(const gp_Ax2d& theA) noexcept;

  void SetRotation(const gp_Pnt2d& theP, const double theAng);

  void SetScale(const gp_Pnt2d& theP, const double theS);

  Standard_EXPORT void SetTransformation(const gp_Ax2d& theFromSystem1,
                                         const gp_Ax2d& theToSystem2);

  Standard_EXPORT void SetTransformation(const gp_Ax2d& theToSystem);

  void SetTranslation(const gp_Vec2d& theV);

  void SetTranslation(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2);

  Standard_EXPORT void SetTranslationPart(const gp_Vec2d& theV);

  Standard_EXPORT void SetScaleFactor(const double theS);

  constexpr bool IsNegative() const noexcept { return (matrix.Determinant() < 0.0); }

  constexpr gp_TrsfForm Form() const noexcept { return shape; }

  constexpr double ScaleFactor() const noexcept { return scale; }

  constexpr const gp_XY& TranslationPart() const noexcept { return loc; }

  Standard_EXPORT gp_Mat2d VectorialPart() const;

  constexpr const gp_Mat2d& HVectorialPart() const noexcept { return matrix; }

  Standard_EXPORT double RotationPart() const;

  constexpr double Value(const int theRow, const int theCol) const;

  Standard_EXPORT void Invert();

  [[nodiscard]] gp_Trsf2d Inverted() const
  {
    gp_Trsf2d aT = *this;
    aT.Invert();
    return aT;
  }

  [[nodiscard]] gp_Trsf2d Multiplied(const gp_Trsf2d& theT) const
  {
    gp_Trsf2d aTresult(*this);
    aTresult.Multiply(theT);
    return aTresult;
  }

  [[nodiscard]] gp_Trsf2d operator*(const gp_Trsf2d& theT) const { return Multiplied(theT); }

  Standard_EXPORT void Multiply(const gp_Trsf2d& theT);

  void operator*=(const gp_Trsf2d& theT) { Multiply(theT); }

  Standard_EXPORT void PreMultiply(const gp_Trsf2d& theT);

  Standard_EXPORT void Power(const int theN);

  gp_Trsf2d Powered(const int theN)
  {
    gp_Trsf2d aT = *this;
    aT.Power(theN);
    return aT;
  }

  constexpr void Transforms(double& theX, double& theY) const noexcept;

  constexpr void Transforms(gp_XY& theCoord) const noexcept;

  Standard_EXPORT void SetValues(const double a11,
                                 const double a12,
                                 const double a13,
                                 const double a21,
                                 const double a22,
                                 const double a23);

  friend class gp_GTrsf2d;

protected:
  Standard_EXPORT void Orthogonalize();

private:
  double      scale;
  gp_TrsfForm shape;
  gp_Mat2d    matrix;
  gp_XY       loc;
};

#include <gp_Trsf.hpp>
#include <gp_Pnt2d.hpp>

inline constexpr gp_Trsf2d::gp_Trsf2d() noexcept
    : scale(1.0),
      shape(gp_Identity),

      loc(0.0, 0.0)
{
  matrix.SetIdentity();
}

inline gp_Trsf2d::gp_Trsf2d(const gp_Trsf& theT)
    : scale(theT.ScaleFactor()),
      shape(theT.Form()),
      loc(theT.TranslationPart().X(), theT.TranslationPart().Y())
{
  const gp_Mat& M = theT.HVectorialPart();
  matrix(1, 1)    = M(1, 1);
  matrix(1, 2)    = M(1, 2);
  matrix(2, 1)    = M(2, 1);
  matrix(2, 2)    = M(2, 2);
}

inline void gp_Trsf2d::SetRotation(const gp_Pnt2d& theP, const double theAng)
{
  shape = gp_Rotation;
  scale = 1.0;
  loc   = theP.XY();
  loc.Reverse();
  matrix.SetRotation(theAng);
  loc.Multiply(matrix);
  loc.Add(theP.XY());
}

inline void gp_Trsf2d::SetMirror(const gp_Pnt2d& theP) noexcept
{
  shape = gp_PntMirror;
  scale = -1.0;
  matrix.SetIdentity();
  loc = theP.XY();
  loc.Multiply(2.0);
}

inline void gp_Trsf2d::SetScale(const gp_Pnt2d& theP, const double theS)
{
  shape = gp_Scale;
  scale = theS;
  matrix.SetIdentity();
  loc = theP.XY();
  loc.Multiply(1.0 - theS);
}

inline void gp_Trsf2d::SetTranslation(const gp_Vec2d& theV)
{
  shape = gp_Translation;
  scale = 1.0;
  matrix.SetIdentity();
  loc = theV.XY();
}

inline void gp_Trsf2d::SetTranslation(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2)
{
  shape = gp_Translation;
  scale = 1.0;
  matrix.SetIdentity();
  loc = (theP2.XY()).Subtracted(theP1.XY());
}

inline constexpr double gp_Trsf2d::Value(const int theRow, const int theCol) const
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 2 || theCol < 1 || theCol > 3, " ");
  if (theCol < 3)
  {
    return scale * matrix.myMat[theRow - 1][theCol - 1];
  }
  else
  {
    return loc.Coord(theRow);
  }
}

inline constexpr void gp_Trsf2d::Transforms(double& theX, double& theY) const noexcept
{
  gp_XY aDoublet(theX, theY);
  aDoublet.Multiply(matrix);
  if (scale != 1.0)
  {
    aDoublet.Multiply(scale);
  }
  aDoublet.Add(loc);
  aDoublet.Coord(theX, theY);
}

inline constexpr void gp_Trsf2d::Transforms(gp_XY& theCoord) const noexcept
{
  theCoord.Multiply(matrix);
  if (scale != 1.0)
  {
    theCoord.Multiply(scale);
  }
  theCoord.Add(loc);
}
