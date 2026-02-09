#pragma once

#include <cmath>

#include <Standard_Dump.hpp>

#define NCOLLECTION_VEC_COMPONENTS_2D(theX, theY)                                                  \
  constexpr NCollection_Vec2<Element_t> theX##theY() const noexcept                                \
  {                                                                                                \
    return NCollection_Vec2<Element_t>(theX(), theY());                                            \
  }                                                                                                \
  constexpr NCollection_Vec2<Element_t> theY##theX() const noexcept                                \
  {                                                                                                \
    return NCollection_Vec2<Element_t>(theY(), theX());                                            \
  }

template <typename Element_t>
class NCollection_Vec2
{

public:
  static constexpr int Length() noexcept { return 2; }

  constexpr NCollection_Vec2() noexcept
      : v{Element_t(0), Element_t(0)}
  {
  }

  explicit constexpr NCollection_Vec2(const Element_t theXY) noexcept
      : v{theXY, theXY}
  {
  }

  explicit constexpr NCollection_Vec2(const Element_t theX, const Element_t theY) noexcept
      : v{theX, theY}
  {
  }

  template <typename OtherElement_t>
  explicit constexpr NCollection_Vec2(const NCollection_Vec2<OtherElement_t>& theOtherVec2) noexcept
      : v{static_cast<Element_t>(theOtherVec2[0]), static_cast<Element_t>(theOtherVec2[1])}
  {
  }

  constexpr void SetValues(const Element_t theX, const Element_t theY) noexcept
  {
    v[0] = theX;
    v[1] = theY;
  }

  constexpr Element_t x() const noexcept { return v[0]; }

  constexpr Element_t y() const noexcept { return v[1]; }

  NCOLLECTION_VEC_COMPONENTS_2D(x, y)

  constexpr Element_t& x() noexcept { return v[0]; }

  constexpr Element_t& y() noexcept { return v[1]; }

  constexpr bool IsEqual(const NCollection_Vec2& theOther) const noexcept
  {
    return v[0] == theOther.v[0] && v[1] == theOther.v[1];
  }

  constexpr bool operator==(const NCollection_Vec2& theOther) const noexcept
  {
    return IsEqual(theOther);
  }

  constexpr bool operator!=(const NCollection_Vec2& theOther) const noexcept
  {
    return !IsEqual(theOther);
  }

  constexpr const Element_t* GetData() const noexcept { return v; }

  constexpr Element_t* ChangeData() noexcept { return v; }

  constexpr operator const Element_t*() const noexcept { return v; }

  constexpr operator Element_t*() noexcept { return v; }

  constexpr NCollection_Vec2& operator+=(const NCollection_Vec2& theAdd) noexcept
  {
    v[0] += theAdd.v[0];
    v[1] += theAdd.v[1];
    return *this;
  }

  friend constexpr NCollection_Vec2 operator+(const NCollection_Vec2& theLeft,
                                              const NCollection_Vec2& theRight) noexcept
  {
    return NCollection_Vec2(theLeft.v[0] + theRight.v[0], theLeft.v[1] + theRight.v[1]);
  }

  constexpr NCollection_Vec2& operator-=(const NCollection_Vec2& theDec) noexcept
  {
    v[0] -= theDec.v[0];
    v[1] -= theDec.v[1];
    return *this;
  }

  friend constexpr NCollection_Vec2 operator-(const NCollection_Vec2& theLeft,
                                              const NCollection_Vec2& theRight) noexcept
  {
    return NCollection_Vec2(theLeft.v[0] - theRight.v[0], theLeft.v[1] - theRight.v[1]);
  }

  constexpr NCollection_Vec2 operator-() const noexcept { return NCollection_Vec2(-x(), -y()); }

  constexpr NCollection_Vec2& operator*=(const NCollection_Vec2& theRight) noexcept
  {
    v[0] *= theRight.v[0];
    v[1] *= theRight.v[1];
    return *this;
  }

  friend constexpr NCollection_Vec2 operator*(const NCollection_Vec2& theLeft,
                                              const NCollection_Vec2& theRight) noexcept
  {
    return NCollection_Vec2(theLeft.v[0] * theRight.v[0], theLeft.v[1] * theRight.v[1]);
  }

  constexpr void Multiply(const Element_t theFactor) noexcept
  {
    v[0] *= theFactor;
    v[1] *= theFactor;
  }

  constexpr NCollection_Vec2 Multiplied(const Element_t theFactor) const noexcept
  {
    return NCollection_Vec2(v[0] * theFactor, v[1] * theFactor);
  }

  constexpr NCollection_Vec2 cwiseMin(const NCollection_Vec2& theVec) const noexcept
  {
    return NCollection_Vec2(v[0] < theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] < theVec.v[1] ? v[1] : theVec.v[1]);
  }

  constexpr NCollection_Vec2 cwiseMax(const NCollection_Vec2& theVec) const noexcept
  {
    return NCollection_Vec2(v[0] > theVec.v[0] ? v[0] : theVec.v[0],
                            v[1] > theVec.v[1] ? v[1] : theVec.v[1]);
  }

  NCollection_Vec2 cwiseAbs() const noexcept
  {
    return NCollection_Vec2(std::abs(v[0]), std::abs(v[1]));
  }

  constexpr Element_t maxComp() const noexcept { return v[0] > v[1] ? v[0] : v[1]; }

  constexpr Element_t minComp() const noexcept { return v[0] < v[1] ? v[0] : v[1]; }

  constexpr NCollection_Vec2& operator*=(const Element_t theFactor) noexcept
  {
    Multiply(theFactor);
    return *this;
  }

  constexpr NCollection_Vec2& operator/=(const Element_t theInvFactor)
  {
    v[0] /= theInvFactor;
    v[1] /= theInvFactor;
    return *this;
  }

  constexpr NCollection_Vec2& operator/=(const NCollection_Vec2& theRight)
  {
    v[0] /= theRight.v[0];
    v[1] /= theRight.v[1];
    return *this;
  }

  constexpr NCollection_Vec2 operator*(const Element_t theFactor) const noexcept
  {
    return Multiplied(theFactor);
  }

  constexpr NCollection_Vec2 operator/(const Element_t theInvFactor) const
  {
    return NCollection_Vec2(v[0] / theInvFactor, v[1] / theInvFactor);
  }

  friend constexpr NCollection_Vec2 operator/(const NCollection_Vec2& theLeft,
                                              const NCollection_Vec2& theRight)
  {
    return NCollection_Vec2(theLeft.v[0] / theRight.v[0], theLeft.v[1] / theRight.v[1]);
  }

  constexpr Element_t Dot(const NCollection_Vec2& theOther) const noexcept
  {
    return x() * theOther.x() + y() * theOther.y();
  }

  Element_t Modulus() const noexcept { return std::sqrt(x() * x() + y() * y()); }

  constexpr Element_t SquareModulus() const noexcept { return x() * x() + y() * y(); }

  static constexpr NCollection_Vec2 DX() noexcept
  {
    return NCollection_Vec2(Element_t(1), Element_t(0));
  }

  static constexpr NCollection_Vec2 DY() noexcept
  {
    return NCollection_Vec2(Element_t(0), Element_t(1));
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theDepth;
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, "Vec2", 2, v[0], v[1])
  }

private:
  Element_t v[2];
};
