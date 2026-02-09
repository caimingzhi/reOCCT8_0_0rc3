#pragma once

#include <cstring>
#include <cmath>
#include <NCollection_Vec2.hpp>

#define NCOLLECTION_VEC_COMPONENTS_3D(theX, theY, theZ)                                            \
  constexpr NCollection_Vec3<Element_t> theX##theY##theZ() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theX(), theY(), theZ());                                    \
  }                                                                                                \
  constexpr NCollection_Vec3<Element_t> theX##theZ##theY() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theX(), theZ(), theY());                                    \
  }                                                                                                \
  constexpr NCollection_Vec3<Element_t> theY##theX##theZ() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theY(), theX(), theZ());                                    \
  }                                                                                                \
  constexpr NCollection_Vec3<Element_t> theY##theZ##theX() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theY(), theZ(), theX());                                    \
  }                                                                                                \
  constexpr NCollection_Vec3<Element_t> theZ##theY##theX() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theZ(), theY(), theX());                                    \
  }                                                                                                \
  constexpr NCollection_Vec3<Element_t> theZ##theX##theY() const noexcept                          \
  {                                                                                                \
    return NCollection_Vec3<Element_t>(theZ(), theX(), theY());                                    \
  }

template <typename Element_t>
class NCollection_Vec3
{

public:
  static constexpr int Length() noexcept { return 3; }

  constexpr NCollection_Vec3() noexcept
      : v{Element_t(0), Element_t(0), Element_t(0)}
  {
  }

  explicit constexpr NCollection_Vec3(Element_t theValue) noexcept
      : v{theValue, theValue, theValue}
  {
  }

  explicit constexpr NCollection_Vec3(const Element_t theX,
                                      const Element_t theY,
                                      const Element_t theZ) noexcept
      : v{theX, theY, theZ}
  {
  }

  explicit constexpr NCollection_Vec3(const NCollection_Vec2<Element_t>& theVec2,
                                      Element_t theZ = Element_t(0)) noexcept
      : v{theVec2[0], theVec2[1], theZ}
  {
  }

  template <typename OtherElement_t>
  explicit constexpr NCollection_Vec3(const NCollection_Vec3<OtherElement_t>& theOtherVec3) noexcept
      : v{static_cast<Element_t>(theOtherVec3[0]),
          static_cast<Element_t>(theOtherVec3[1]),
          static_cast<Element_t>(theOtherVec3[2])}
  {
  }

  constexpr void SetValues(const Element_t theX,
                           const Element_t theY,
                           const Element_t theZ) noexcept
  {
    v[0] = theX;
    v[1] = theY;
    v[2] = theZ;
  }

  constexpr void SetValues(const NCollection_Vec2<Element_t>& theVec2, Element_t theZ) noexcept
  {
    v[0] = theVec2.x();
    v[1] = theVec2.y();
    v[2] = theZ;
  }

  constexpr Element_t x() const noexcept { return v[0]; }

  constexpr Element_t r() const noexcept { return v[0]; }

  constexpr Element_t y() const noexcept { return v[1]; }

  constexpr Element_t g() const noexcept { return v[1]; }

  constexpr Element_t z() const noexcept { return v[2]; }

  constexpr Element_t b() const noexcept { return v[2]; }

  NCOLLECTION_VEC_COMPONENTS_2D(x, y)
  NCOLLECTION_VEC_COMPONENTS_2D(x, z)
  NCOLLECTION_VEC_COMPONENTS_2D(y, z)

  NCOLLECTION_VEC_COMPONENTS_3D(x, y, z)

  constexpr Element_t& x() noexcept { return v[0]; }

  constexpr Element_t& r() noexcept { return v[0]; }

  constexpr Element_t& y() noexcept { return v[1]; }

  constexpr Element_t& g() noexcept { return v[1]; }

  constexpr Element_t& z() noexcept { return v[2]; }

  constexpr Element_t& b() noexcept { return v[2]; }

  constexpr bool IsEqual(const NCollection_Vec3& theOther) const noexcept
  {
    return v[0] == theOther.v[0] && v[1] == theOther.v[1] && v[2] == theOther.v[2];
  }

  constexpr bool operator==(const NCollection_Vec3& theOther) const noexcept
  {
    return IsEqual(theOther);
  }

  constexpr bool operator!=(const NCollection_Vec3& theOther) const noexcept
  {
    return !IsEqual(theOther);
  }

  constexpr const Element_t* GetData() const noexcept { return v; }

  constexpr Element_t* ChangeData() noexcept { return v; }

  constexpr operator const Element_t*() const noexcept { return v; }

  constexpr operator Element_t*() noexcept { return v; }

  constexpr NCollection_Vec3& operator+=(const NCollection_Vec3& theAdd) noexcept
  {
    v[0] += theAdd.v[0];
    v[1] += theAdd.v[1];
    v[2] += theAdd.v[2];
    return *this;
  }

  friend constexpr NCollection_Vec3 operator+(const NCollection_Vec3& theLeft,
                                              const NCollection_Vec3& theRight) noexcept
  {
    NCollection_Vec3 aSumm = NCollection_Vec3(theLeft);
    return aSumm += theRight;
  }

  constexpr NCollection_Vec3 operator-() const noexcept
  {
    return NCollection_Vec3(-x(), -y(), -z());
  }

  constexpr NCollection_Vec3& operator-=(const NCollection_Vec3& theDec) noexcept
  {
    v[0] -= theDec.v[0];
    v[1] -= theDec.v[1];
    v[2] -= theDec.v[2];
    return *this;
  }

  friend constexpr NCollection_Vec3 operator-(const NCollection_Vec3& theLeft,
                                              const NCollection_Vec3& theRight) noexcept
  {
    NCollection_Vec3 aSumm = NCollection_Vec3(theLeft);
    return aSumm -= theRight;
  }

  constexpr void Multiply(const Element_t theFactor) noexcept
  {
    v[0] *= theFactor;
    v[1] *= theFactor;
    v[2] *= theFactor;
  }

  constexpr NCollection_Vec3& operator*=(const NCollection_Vec3& theRight) noexcept
  {
    v[0] *= theRight.v[0];
    v[1] *= theRight.v[1];
    v[2] *= theRight.v[2];
    return *this;
  }

  friend constexpr NCollection_Vec3 operator*(const NCollection_Vec3& theLeft,
                                              const NCollection_Vec3& theRight) noexcept
  {
    NCollection_Vec3 aResult = NCollection_Vec3(theLeft);
    return aResult *= theRight;
  }

  constexpr NCollection_Vec3& operator*=(const Element_t theFactor) noexcept
  {
    Multiply(theFactor);
    return *this;
  }

  constexpr NCollection_Vec3 operator*(const Element_t theFactor) const noexcept
  {
    return Multiplied(theFactor);
  }

  constexpr NCollection_Vec3 Multiplied(const Element_t theFactor) const noexcept
  {
    NCollection_Vec3 aCopyVec3(*this);
    aCopyVec3 *= theFactor;
    return aCopyVec3;
  }

  constexpr NCollection_Vec3 cwiseMin(const NCollection_Vec3& theVec) const noexcept
  {
    return NCollection_Vec3(v[0] < theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] < theVec.v[1] ? v[1] : theVec.v[1],
                            v[2] < theVec.v[2] ? v[2] : theVec.v[2]);
  }

  constexpr NCollection_Vec3 cwiseMax(const NCollection_Vec3& theVec) const noexcept
  {
    return NCollection_Vec3(v[0] > theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] > theVec.v[1] ? v[1] : theVec.v[1],
                            v[2] > theVec.v[2] ? v[2] : theVec.v[2]);
  }

  NCollection_Vec3 cwiseAbs() const noexcept
  {
    return NCollection_Vec3(std::abs(v[0]), std::abs(v[1]), std::abs(v[2]));
  }

  constexpr Element_t maxComp() const noexcept
  {
    return v[0] > v[1] ? (v[0] > v[2] ? v[0] : v[2]) : (v[1] > v[2] ? v[1] : v[2]);
  }

  constexpr Element_t minComp() const noexcept
  {
    return v[0] < v[1] ? (v[0] < v[2] ? v[0] : v[2]) : (v[1] < v[2] ? v[1] : v[2]);
  }

  constexpr NCollection_Vec3& operator/=(const Element_t theInvFactor)
  {
    v[0] /= theInvFactor;
    v[1] /= theInvFactor;
    v[2] /= theInvFactor;
    return *this;
  }

  constexpr NCollection_Vec3& operator/=(const NCollection_Vec3& theRight)
  {
    v[0] /= theRight.v[0];
    v[1] /= theRight.v[1];
    v[2] /= theRight.v[2];
    return *this;
  }

  constexpr NCollection_Vec3 operator/(const Element_t theInvFactor) const
  {
    NCollection_Vec3 aResult(*this);
    return aResult /= theInvFactor;
  }

  friend constexpr NCollection_Vec3 operator/(const NCollection_Vec3& theLeft,
                                              const NCollection_Vec3& theRight)
  {
    NCollection_Vec3 aResult = NCollection_Vec3(theLeft);
    return aResult /= theRight;
  }

  constexpr Element_t Dot(const NCollection_Vec3& theOther) const noexcept
  {
    return x() * theOther.x() + y() * theOther.y() + z() * theOther.z();
  }

  Element_t Modulus() const noexcept { return std::sqrt(x() * x() + y() * y() + z() * z()); }

  constexpr Element_t SquareModulus() const noexcept { return x() * x() + y() * y() + z() * z(); }

  void Normalize()
  {
    Element_t aModulus = Modulus();
    if (aModulus != Element_t(0))
    {
      x() = x() / aModulus;
      y() = y() / aModulus;
      z() = z() / aModulus;
    }
  }

  NCollection_Vec3 Normalized() const
  {
    NCollection_Vec3 aCopy(*this);
    aCopy.Normalize();
    return aCopy;
  }

  static constexpr NCollection_Vec3 Cross(const NCollection_Vec3& theVec1,
                                          const NCollection_Vec3& theVec2) noexcept
  {
    return NCollection_Vec3(theVec1.y() * theVec2.z() - theVec1.z() * theVec2.y(),
                            theVec1.z() * theVec2.x() - theVec1.x() * theVec2.z(),
                            theVec1.x() * theVec2.y() - theVec1.y() * theVec2.x());
  }

  static constexpr NCollection_Vec3 GetLERP(const NCollection_Vec3& theFrom,
                                            const NCollection_Vec3& theTo,
                                            const Element_t         theT) noexcept
  {
    return theFrom * (Element_t(1) - theT) + theTo * theT;
  }

  static constexpr NCollection_Vec3 DX() noexcept
  {
    return NCollection_Vec3(Element_t(1), Element_t(0), Element_t(0));
  }

  static constexpr NCollection_Vec3 DY() noexcept
  {
    return NCollection_Vec3(Element_t(0), Element_t(1), Element_t(0));
  }

  static constexpr NCollection_Vec3 DZ() noexcept
  {
    return NCollection_Vec3(Element_t(0), Element_t(0), Element_t(1));
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, "Vec3", 3, v[0], v[1], v[2])
  }

private:
  Element_t v[3];
};

template <>
inline constexpr NCollection_Vec3<float>& NCollection_Vec3<float>::operator/=(
  const float theInvFactor)
{
  Multiply(1.0f / theInvFactor);
  return *this;
}

template <>
inline constexpr NCollection_Vec3<double>& NCollection_Vec3<double>::operator/=(
  const double theInvFactor)
{
  Multiply(1.0 / theInvFactor);
  return *this;
}
