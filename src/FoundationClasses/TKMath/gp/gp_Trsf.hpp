#pragma once

#include <gp_TrsfForm.hpp>
#include <gp_Mat.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_OStream.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_SStream.hpp>

class gp_Pnt;
class gp_Trsf2d;
class gp_Ax1;
class gp_Ax2;
class gp_Quaternion;
class gp_Ax3;
class gp_Vec;

#ifdef SetForm
  #undef SetForm
#endif

class gp_Trsf
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Trsf() noexcept;

  Standard_EXPORT gp_Trsf(const gp_Trsf2d& theT);

  constexpr void SetMirror(const gp_Pnt& theP) noexcept;

  Standard_EXPORT void SetMirror(const gp_Ax1& theA1) noexcept;

  Standard_EXPORT void SetMirror(const gp_Ax2& theA2) noexcept;

  Standard_EXPORT void SetRotation(const gp_Ax1& theA1, const double theAng);

  Standard_EXPORT void SetRotation(const gp_Quaternion& theR);

  Standard_EXPORT void SetRotationPart(const gp_Quaternion& theR);

  Standard_EXPORT void SetScale(const gp_Pnt& theP, const double theS);

  Standard_EXPORT void SetDisplacement(const gp_Ax3& theFromSystem1, const gp_Ax3& theToSystem2);

  Standard_EXPORT void SetTransformation(const gp_Ax3& theFromSystem1, const gp_Ax3& theToSystem2);

  Standard_EXPORT void SetTransformation(const gp_Ax3& theToSystem);

  Standard_EXPORT void SetTransformation(const gp_Quaternion& R, const gp_Vec& theT);

  constexpr void SetTranslation(const gp_Vec& theV) noexcept;

  constexpr void SetTranslation(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept;

  Standard_EXPORT void SetTranslationPart(const gp_Vec& theV) noexcept;

  Standard_EXPORT void SetScaleFactor(const double theS);

  constexpr void SetForm(const gp_TrsfForm theP) noexcept { shape = theP; }

  Standard_EXPORT void SetValues(const double a11,
                                 const double a12,
                                 const double a13,
                                 const double a14,
                                 const double a21,
                                 const double a22,
                                 const double a23,
                                 const double a24,
                                 const double a31,
                                 const double a32,
                                 const double a33,
                                 const double a34);

  constexpr bool IsNegative() const noexcept { return (scale < 0.0); }

  constexpr gp_TrsfForm Form() const noexcept { return shape; }

  constexpr double ScaleFactor() const noexcept { return scale; }

  constexpr const gp_XYZ& TranslationPart() const noexcept { return loc; }

  Standard_EXPORT bool GetRotation(gp_XYZ& theAxis, double& theAngle) const;

  Standard_EXPORT gp_Quaternion GetRotation() const;

  constexpr gp_Mat VectorialPart() const noexcept;

  constexpr const gp_Mat& HVectorialPart() const noexcept { return matrix; }

  constexpr double Value(const int theRow, const int theCol) const;

  Standard_EXPORT void Invert();

  [[nodiscard]] gp_Trsf Inverted() const
  {
    gp_Trsf aT = *this;
    aT.Invert();
    return aT;
  }

  [[nodiscard]] gp_Trsf Multiplied(const gp_Trsf& theT) const
  {
    gp_Trsf aTresult(*this);
    aTresult.Multiply(theT);
    return aTresult;
  }

  [[nodiscard]] gp_Trsf operator*(const gp_Trsf& theT) const { return Multiplied(theT); }

  Standard_EXPORT void Multiply(const gp_Trsf& theT);

  void operator*=(const gp_Trsf& theT) { Multiply(theT); }

  Standard_EXPORT void PreMultiply(const gp_Trsf& theT);

  Standard_EXPORT void Power(const int theN);

  [[nodiscard]] gp_Trsf Powered(const int theN) const
  {
    gp_Trsf aT = *this;
    aT.Power(theN);
    return aT;
  }

  constexpr void Transforms(double& theX, double& theY, double& theZ) const noexcept;

  constexpr void Transforms(gp_XYZ& theCoord) const noexcept;

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

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

  friend class gp_GTrsf;

protected:
  Standard_EXPORT void Orthogonalize();

private:
  double      scale;
  gp_TrsfForm shape;
  gp_Mat      matrix;
  gp_XYZ      loc;
};

#include <gp_Trsf2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>

inline constexpr gp_Trsf::gp_Trsf() noexcept
    : scale(1.0),
      shape(gp_Identity),
      matrix(1, 0, 0, 0, 1, 0, 0, 0, 1),
      loc(0.0, 0.0, 0.0)
{
}

inline constexpr void gp_Trsf::SetMirror(const gp_Pnt& theP) noexcept
{
  shape = gp_PntMirror;
  scale = -1.0;
  loc   = theP.XYZ();
  matrix.SetIdentity();
  loc.Multiply(2.0);
}

inline constexpr void gp_Trsf::SetTranslation(const gp_Vec& theV) noexcept
{
  shape = gp_Translation;
  scale = 1.;
  matrix.SetIdentity();
  loc = theV.XYZ();
}

inline constexpr void gp_Trsf::SetTranslation(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
{
  shape = gp_Translation;
  scale = 1.0;
  matrix.SetIdentity();
  loc = (theP2.XYZ()).Subtracted(theP1.XYZ());
}

inline constexpr double gp_Trsf::Value(const int theRow, const int theCol) const
{
  Standard_OutOfRange_Raise_if(theRow < 1 || theRow > 3 || theCol < 1 || theCol > 4, " ");
  if (theCol < 4)
  {

    return scale * matrix.myMat[theRow - 1][theCol - 1];
  }
  else
  {
    return loc.Coord(theRow);
  }
}

inline constexpr void gp_Trsf::Transforms(double& theX, double& theY, double& theZ) const noexcept
{
  gp_XYZ aTriplet(theX, theY, theZ);
  aTriplet.Multiply(matrix);
  if (scale != 1.0)
  {
    aTriplet.Multiply(scale);
  }
  aTriplet.Add(loc);
  theX = aTriplet.X();
  theY = aTriplet.Y();
  theZ = aTriplet.Z();
}

inline constexpr void gp_Trsf::Transforms(gp_XYZ& theCoord) const noexcept
{
  theCoord.Multiply(matrix);
  if (scale != 1.0)
  {
    theCoord.Multiply(scale);
  }
  theCoord.Add(loc);
}

inline constexpr gp_Mat gp_Trsf::VectorialPart() const noexcept
{
  if (scale == 1.0)
  {
    return matrix;
  }
  gp_Mat M = matrix;
  if (shape == gp_Scale || shape == gp_PntMirror)
  {

    M.SetDiagonal(scale * M.myMat[0][0], scale * M.myMat[1][1], scale * M.myMat[2][2]);
  }
  else
  {
    M.Multiply(scale);
  }
  return M;
}
