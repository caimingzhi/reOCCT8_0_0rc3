#pragma once

enum gp_EulerSequence
{

  gp_EulerAngles,

  gp_YawPitchRoll,

  gp_Extrinsic_XYZ,
  gp_Extrinsic_XZY,
  gp_Extrinsic_YZX,
  gp_Extrinsic_YXZ,
  gp_Extrinsic_ZXY,
  gp_Extrinsic_ZYX,

  gp_Intrinsic_XYZ,
  gp_Intrinsic_XZY,
  gp_Intrinsic_YZX,
  gp_Intrinsic_YXZ,
  gp_Intrinsic_ZXY,
  gp_Intrinsic_ZYX,

  gp_Extrinsic_XYX,
  gp_Extrinsic_XZX,
  gp_Extrinsic_YZY,
  gp_Extrinsic_YXY,
  gp_Extrinsic_ZYZ,
  gp_Extrinsic_ZXZ,

  gp_Intrinsic_XYX,
  gp_Intrinsic_XZX,
  gp_Intrinsic_YZY,
  gp_Intrinsic_YXY,
  gp_Intrinsic_ZXZ,
  gp_Intrinsic_ZYZ
};

#include <gp_Mat.hpp>
#include <gp_Vec.hpp>

class gp_Quaternion
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Quaternion() noexcept
      : x(0.0),
        y(0.0),
        z(0.0),
        w(1.0)
  {
  }

  constexpr gp_Quaternion(const double theX,
                          const double theY,
                          const double theZ,
                          const double theW) noexcept
      : x(theX),
        y(theY),
        z(theZ),
        w(theW)
  {
  }

  gp_Quaternion(const gp_Vec& theVecFrom, const gp_Vec& theVecTo)
  {
    SetRotation(theVecFrom, theVecTo);
  }

  gp_Quaternion(const gp_Vec& theVecFrom, const gp_Vec& theVecTo, const gp_Vec& theHelpCrossVec)
  {
    SetRotation(theVecFrom, theVecTo, theHelpCrossVec);
  }

  gp_Quaternion(const gp_Vec& theAxis, const double theAngle)
  {
    SetVectorAndAngle(theAxis, theAngle);
  }

  gp_Quaternion(const gp_Mat& theMat) { SetMatrix(theMat); }

  Standard_EXPORT bool IsEqual(const gp_Quaternion& theOther) const;

  Standard_EXPORT void SetRotation(const gp_Vec& theVecFrom, const gp_Vec& theVecTo);

  Standard_EXPORT void SetRotation(const gp_Vec& theVecFrom,
                                   const gp_Vec& theVecTo,
                                   const gp_Vec& theHelpCrossVec);

  Standard_EXPORT void SetVectorAndAngle(const gp_Vec& theAxis, const double theAngle);

  Standard_EXPORT void GetVectorAndAngle(gp_Vec& theAxis, double& theAngle) const;

  Standard_EXPORT void SetMatrix(const gp_Mat& theMat);

  Standard_EXPORT gp_Mat GetMatrix() const;

  Standard_EXPORT void SetEulerAngles(const gp_EulerSequence theOrder,
                                      const double           theAlpha,
                                      const double           theBeta,
                                      const double           theGamma);

  Standard_EXPORT void GetEulerAngles(const gp_EulerSequence theOrder,
                                      double&                theAlpha,
                                      double&                theBeta,
                                      double&                theGamma) const;

  constexpr void Set(const double theX,
                     const double theY,
                     const double theZ,
                     const double theW) noexcept;

  constexpr void Set(const gp_Quaternion& theQuaternion) noexcept;

  constexpr double X() const noexcept { return x; }

  constexpr double Y() const noexcept { return y; }

  constexpr double Z() const noexcept { return z; }

  constexpr double W() const noexcept { return w; }

  constexpr void SetIdent() noexcept
  {
    x = y = z = 0.0;
    w         = 1.0;
  }

  constexpr void Reverse() noexcept
  {
    x = -x;
    y = -y;
    z = -z;
  }

  [[nodiscard]] constexpr gp_Quaternion Reversed() const noexcept
  {
    return gp_Quaternion(-x, -y, -z, w);
  }

  constexpr void Invert()
  {
    double anIn = 1.0 / SquareNorm();
    Set(-x * anIn, -y * anIn, -z * anIn, w * anIn);
  }

  [[nodiscard]] constexpr gp_Quaternion Inverted() const
  {
    double anIn = 1.0 / SquareNorm();
    return gp_Quaternion(-x * anIn, -y * anIn, -z * anIn, w * anIn);
  }

  constexpr double SquareNorm() const noexcept { return x * x + y * y + z * z + w * w; }

  double Norm() const { return std::sqrt(SquareNorm()); }

  constexpr void Scale(const double theScale) noexcept;

  void operator*=(const double theScale) { Scale(theScale); }

  [[nodiscard]] constexpr gp_Quaternion Scaled(const double theScale) const noexcept
  {
    return gp_Quaternion(x * theScale, y * theScale, z * theScale, w * theScale);
  }

  [[nodiscard]] constexpr gp_Quaternion operator*(const double theScale) const noexcept
  {
    return Scaled(theScale);
  }

  Standard_EXPORT void StabilizeLength();

  Standard_EXPORT void Normalize();

  [[nodiscard]] gp_Quaternion Normalized() const
  {
    gp_Quaternion aNormilizedQ(*this);
    aNormilizedQ.Normalize();
    return aNormilizedQ;
  }

  [[nodiscard]] constexpr gp_Quaternion Negated() const noexcept
  {
    return gp_Quaternion(-x, -y, -z, -w);
  }

  [[nodiscard]] constexpr gp_Quaternion operator-() const noexcept { return Negated(); }

  [[nodiscard]] constexpr gp_Quaternion Added(const gp_Quaternion& theOther) const noexcept
  {
    return gp_Quaternion(x + theOther.x, y + theOther.y, z + theOther.z, w + theOther.w);
  }

  [[nodiscard]] constexpr gp_Quaternion operator+(const gp_Quaternion& theOther) const noexcept
  {
    return Added(theOther);
  }

  [[nodiscard]] constexpr gp_Quaternion Subtracted(const gp_Quaternion& theOther) const noexcept
  {
    return gp_Quaternion(x - theOther.x, y - theOther.y, z - theOther.z, w - theOther.w);
  }

  [[nodiscard]] constexpr gp_Quaternion operator-(const gp_Quaternion& theOther) const noexcept
  {
    return Subtracted(theOther);
  }

  [[nodiscard]] constexpr gp_Quaternion Multiplied(const gp_Quaternion& theOther) const noexcept;

  [[nodiscard]] constexpr gp_Quaternion operator*(const gp_Quaternion& theOther) const noexcept
  {
    return Multiplied(theOther);
  }

  constexpr void Add(const gp_Quaternion& theOther) noexcept;

  void operator+=(const gp_Quaternion& theOther) { Add(theOther); }

  constexpr void Subtract(const gp_Quaternion& theOther) noexcept;

  void operator-=(const gp_Quaternion& theOther) { Subtract(theOther); }

  void Multiply(const gp_Quaternion& theOther) { (*this) = Multiplied(theOther); }

  void operator*=(const gp_Quaternion& theOther) { Multiply(theOther); }

  constexpr double Dot(const gp_Quaternion& theOther) const noexcept
  {
    return x * theOther.x + y * theOther.y + z * theOther.z + w * theOther.w;
  }

  Standard_EXPORT double GetRotationAngle() const;

  Standard_EXPORT gp_Vec Multiply(const gp_Vec& theVec) const;

  gp_Vec operator*(const gp_Vec& theVec) const { return Multiply(theVec); }

private:
  double x;
  double y;
  double z;
  double w;
};

inline constexpr void gp_Quaternion::Set(double theX,
                                         double theY,
                                         double theZ,
                                         double theW) noexcept
{
  this->x = theX;
  this->y = theY;
  this->z = theZ;
  this->w = theW;
}

inline constexpr void gp_Quaternion::Set(const gp_Quaternion& theQuaternion) noexcept
{
  x = theQuaternion.x;
  y = theQuaternion.y;
  z = theQuaternion.z;
  w = theQuaternion.w;
}

inline constexpr void gp_Quaternion::Scale(const double theScale) noexcept
{
  x *= theScale;
  y *= theScale;
  z *= theScale;
  w *= theScale;
}

inline constexpr gp_Quaternion gp_Quaternion::Multiplied(const gp_Quaternion& theQ) const noexcept
{
  return gp_Quaternion(w * theQ.x + x * theQ.w + y * theQ.z - z * theQ.y,
                       w * theQ.y + y * theQ.w + z * theQ.x - x * theQ.z,
                       w * theQ.z + z * theQ.w + x * theQ.y - y * theQ.x,
                       w * theQ.w - x * theQ.x - y * theQ.y - z * theQ.z);
}

inline constexpr void gp_Quaternion::Add(const gp_Quaternion& theQ) noexcept
{
  x += theQ.x;
  y += theQ.y;
  z += theQ.z;
  w += theQ.w;
}

inline constexpr void gp_Quaternion::Subtract(const gp_Quaternion& theQ) noexcept
{
  x -= theQ.x;
  y -= theQ.y;
  z -= theQ.z;
  w -= theQ.w;
}
