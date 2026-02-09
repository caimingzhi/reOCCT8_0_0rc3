#pragma once

#include <NCollection_Vec3.hpp>

template <typename Element_t>
class NCollection_Vec4
{

public:
  static constexpr int Length() noexcept { return 4; }

  constexpr NCollection_Vec4() noexcept
      : v{Element_t(0), Element_t(0), Element_t(0), Element_t(0)}
  {
  }

  explicit constexpr NCollection_Vec4(const Element_t theValue) noexcept
      : v{theValue, theValue, theValue, theValue}
  {
  }

  explicit constexpr NCollection_Vec4(const Element_t theX,
                                      const Element_t theY,
                                      const Element_t theZ,
                                      const Element_t theW) noexcept
      : v{theX, theY, theZ, theW}
  {
  }

  explicit constexpr NCollection_Vec4(const NCollection_Vec2<Element_t>& theVec2) noexcept
      : v{theVec2[0], theVec2[1], Element_t(0), Element_t(0)}
  {
  }

  explicit NCollection_Vec4(const NCollection_Vec3<Element_t>& theVec3,
                            const Element_t                    theW = Element_t(0))
  {
    std::memcpy(this, &theVec3, sizeof(NCollection_Vec3<Element_t>));
    v[3] = theW;
  }

  template <typename OtherElement_t>
  explicit constexpr NCollection_Vec4(const NCollection_Vec4<OtherElement_t>& theOtherVec4) noexcept
      : v{static_cast<Element_t>(theOtherVec4[0]),
          static_cast<Element_t>(theOtherVec4[1]),
          static_cast<Element_t>(theOtherVec4[2]),
          static_cast<Element_t>(theOtherVec4[3])}
  {
  }

  constexpr void SetValues(const Element_t theX,
                           const Element_t theY,
                           const Element_t theZ,
                           const Element_t theW) noexcept
  {
    v[0] = theX;
    v[1] = theY;
    v[2] = theZ;
    v[3] = theW;
  }

  constexpr void SetValues(const NCollection_Vec3<Element_t>& theVec3,
                           const Element_t                    theW) noexcept
  {
    v[0] = theVec3.x();
    v[1] = theVec3.y();
    v[2] = theVec3.z();
    v[3] = theW;
  }

  constexpr Element_t x() const noexcept { return v[0]; }

  constexpr Element_t r() const noexcept { return v[0]; }

  constexpr Element_t y() const noexcept { return v[1]; }

  constexpr Element_t g() const noexcept { return v[1]; }

  constexpr Element_t z() const noexcept { return v[2]; }

  constexpr Element_t b() const noexcept { return v[2]; }

  constexpr Element_t w() const noexcept { return v[3]; }

  constexpr Element_t a() const noexcept { return v[3]; }

  NCOLLECTION_VEC_COMPONENTS_2D(x, y)
  NCOLLECTION_VEC_COMPONENTS_2D(x, z)
  NCOLLECTION_VEC_COMPONENTS_2D(x, w)
  NCOLLECTION_VEC_COMPONENTS_2D(y, z)
  NCOLLECTION_VEC_COMPONENTS_2D(y, w)
  NCOLLECTION_VEC_COMPONENTS_2D(z, w)

  NCOLLECTION_VEC_COMPONENTS_3D(x, y, z)
  NCOLLECTION_VEC_COMPONENTS_3D(x, y, w)
  NCOLLECTION_VEC_COMPONENTS_3D(x, z, w)
  NCOLLECTION_VEC_COMPONENTS_3D(y, z, w)

  NCOLLECTION_VEC_COMPONENTS_3D(r, g, b)

  constexpr Element_t& x() noexcept { return v[0]; }

  constexpr Element_t& r() noexcept { return v[0]; }

  constexpr Element_t& y() noexcept { return v[1]; }

  constexpr Element_t& g() noexcept { return v[1]; }

  constexpr Element_t& z() noexcept { return v[2]; }

  constexpr Element_t& b() noexcept { return v[2]; }

  constexpr Element_t& w() noexcept { return v[3]; }

  constexpr Element_t& a() noexcept { return v[3]; }

  constexpr bool IsEqual(const NCollection_Vec4& theOther) const noexcept
  {
    return v[0] == theOther.v[0] && v[1] == theOther.v[1] && v[2] == theOther.v[2]
           && v[3] == theOther.v[3];
  }

  constexpr bool operator==(const NCollection_Vec4& theOther) const noexcept
  {
    return IsEqual(theOther);
  }

  constexpr bool operator!=(const NCollection_Vec4& theOther) const noexcept
  {
    return !IsEqual(theOther);
  }

  constexpr const Element_t* GetData() const noexcept { return v; }

  constexpr Element_t* ChangeData() noexcept { return v; }

  constexpr operator const Element_t*() const noexcept { return v; }

  constexpr operator Element_t*() noexcept { return v; }

  constexpr NCollection_Vec4& operator+=(const NCollection_Vec4& theAdd) noexcept
  {
    v[0] += theAdd.v[0];
    v[1] += theAdd.v[1];
    v[2] += theAdd.v[2];
    v[3] += theAdd.v[3];
    return *this;
  }

  friend constexpr NCollection_Vec4 operator+(const NCollection_Vec4& theLeft,
                                              const NCollection_Vec4& theRight) noexcept
  {
    NCollection_Vec4 aSumm = NCollection_Vec4(theLeft);
    return aSumm += theRight;
  }

  constexpr NCollection_Vec4 operator-() const noexcept
  {
    return NCollection_Vec4(-x(), -y(), -z(), -w());
  }

  constexpr NCollection_Vec4& operator-=(const NCollection_Vec4& theDec) noexcept
  {
    v[0] -= theDec.v[0];
    v[1] -= theDec.v[1];
    v[2] -= theDec.v[2];
    v[3] -= theDec.v[3];
    return *this;
  }

  friend constexpr NCollection_Vec4 operator-(const NCollection_Vec4& theLeft,
                                              const NCollection_Vec4& theRight) noexcept
  {
    NCollection_Vec4 aSumm = NCollection_Vec4(theLeft);
    return aSumm -= theRight;
  }

  constexpr NCollection_Vec4& operator*=(const NCollection_Vec4& theRight) noexcept
  {
    v[0] *= theRight.v[0];
    v[1] *= theRight.v[1];
    v[2] *= theRight.v[2];
    v[3] *= theRight.v[3];
    return *this;
  }

  friend constexpr NCollection_Vec4 operator*(const NCollection_Vec4& theLeft,
                                              const NCollection_Vec4& theRight) noexcept
  {
    NCollection_Vec4 aResult = NCollection_Vec4(theLeft);
    return aResult *= theRight;
  }

  constexpr void Multiply(const Element_t theFactor) noexcept
  {
    v[0] *= theFactor;
    v[1] *= theFactor;
    v[2] *= theFactor;
    v[3] *= theFactor;
  }

  constexpr NCollection_Vec4& operator*=(const Element_t theFactor) noexcept
  {
    Multiply(theFactor);
    return *this;
  }

  constexpr NCollection_Vec4 operator*(const Element_t theFactor) const noexcept
  {
    return Multiplied(theFactor);
  }

  constexpr NCollection_Vec4 Multiplied(const Element_t theFactor) const noexcept
  {
    NCollection_Vec4 aCopyVec4(*this);
    aCopyVec4 *= theFactor;
    return aCopyVec4;
  }

  constexpr NCollection_Vec4 cwiseMin(const NCollection_Vec4& theVec) const noexcept
  {
    return NCollection_Vec4(v[0] < theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] < theVec.v[1] ? v[1] : theVec.v[1],
                            v[2] < theVec.v[2] ? v[2] : theVec.v[2],
                            v[3] < theVec.v[3] ? v[3] : theVec.v[3]);
  }

  constexpr NCollection_Vec4 cwiseMax(const NCollection_Vec4& theVec) const noexcept
  {
    return NCollection_Vec4(v[0] > theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] > theVec.v[1] ? v[1] : theVec.v[1],
                            v[2] > theVec.v[2] ? v[2] : theVec.v[2],
                            v[3] > theVec.v[3] ? v[3] : theVec.v[3]);
  }

  NCollection_Vec4 cwiseAbs() const noexcept
  {
    return NCollection_Vec4(std::abs(v[0]), std::abs(v[1]), std::abs(v[2]), std::abs(v[3]));
  }

  constexpr Element_t maxComp() const noexcept
  {
    const Element_t aMax1 = v[0] > v[1] ? v[0] : v[1];
    const Element_t aMax2 = v[2] > v[3] ? v[2] : v[3];

    return aMax1 > aMax2 ? aMax1 : aMax2;
  }

  constexpr Element_t minComp() const noexcept
  {
    const Element_t aMin1 = v[0] < v[1] ? v[0] : v[1];
    const Element_t aMin2 = v[2] < v[3] ? v[2] : v[3];

    return aMin1 < aMin2 ? aMin1 : aMin2;
  }

  constexpr Element_t Dot(const NCollection_Vec4& theOther) const noexcept
  {
    return x() * theOther.x() + y() * theOther.y() + z() * theOther.z() + w() * theOther.w();
  }

  constexpr NCollection_Vec4& operator/=(const Element_t theInvFactor)
  {
    v[0] /= theInvFactor;
    v[1] /= theInvFactor;
    v[2] /= theInvFactor;
    v[3] /= theInvFactor;
    return *this;
  }

  constexpr NCollection_Vec4& operator/=(const NCollection_Vec4& theRight)
  {
    v[0] /= theRight.v[0];
    v[1] /= theRight.v[1];
    v[2] /= theRight.v[2];
    v[3] /= theRight.v[3];
    return *this;
  }

  constexpr NCollection_Vec4 operator/(const Element_t theInvFactor) const
  {
    NCollection_Vec4 aResult(*this);
    return aResult /= theInvFactor;
  }

  friend constexpr NCollection_Vec4 operator/(const NCollection_Vec4& theLeft,
                                              const NCollection_Vec4& theRight)
  {
    NCollection_Vec4 aResult = NCollection_Vec4(theLeft);
    return aResult /= theRight;
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, "Vec4", 4, v[0], v[1], v[2], v[3])
  }

private:
  Element_t v[4];
};

template <>
inline constexpr NCollection_Vec4<float>& NCollection_Vec4<float>::operator/=(
  const float theInvFactor)
{
  Multiply(1.0f / theInvFactor);
  return *this;
}

template <>
inline constexpr NCollection_Vec4<double>& NCollection_Vec4<double>::operator/=(
  const double theInvFactor)
{
  Multiply(1.0 / theInvFactor);
  return *this;
}
