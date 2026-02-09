#pragma once

#include <NCollection_Vec4.hpp>

#include <NCollection_Vec3.hpp>
#include <Standard_ConstructionError.hpp>

template <typename Element_t>
class NCollection_Mat3
{
public:
  static constexpr NCollection_Mat3 Identity() { return NCollection_Mat3(); }

  static constexpr NCollection_Mat3 Zero()
  {
    NCollection_Mat3 aMat;
    aMat.InitZero();
    return aMat;
  }

public:
  constexpr NCollection_Mat3() { InitIdentity(); }

  template <typename OtherElement_t>
  explicit constexpr NCollection_Mat3(const NCollection_Mat3<OtherElement_t>& theOtherMat3) noexcept
  {
    ConvertFrom(theOtherMat3);
  }

  constexpr Element_t GetValue(const size_t theRow, const size_t theCol) const noexcept
  {
    return myMat[theCol * 3 + theRow];
  }

  constexpr Element_t& ChangeValue(const size_t theRow, const size_t theCol) noexcept
  {
    return myMat[theCol * 3 + theRow];
  }

  constexpr void SetValue(const size_t    theRow,
                          const size_t    theCol,
                          const Element_t theValue) noexcept
  {
    myMat[theCol * 3 + theRow] = theValue;
  }

  constexpr Element_t& operator()(const size_t theRow, const size_t theCol) noexcept
  {
    return ChangeValue(theRow, theCol);
  }

  constexpr Element_t operator()(const size_t theRow, const size_t theCol) const noexcept
  {
    return GetValue(theRow, theCol);
  }

  constexpr NCollection_Vec3<Element_t> GetRow(const size_t theRow) const noexcept
  {
    return NCollection_Vec3<Element_t>(GetValue(theRow, 0),
                                       GetValue(theRow, 1),
                                       GetValue(theRow, 2));
  }

  constexpr void SetRow(const size_t theRow, const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(theRow, 0, theVec.x());
    SetValue(theRow, 1, theVec.y());
    SetValue(theRow, 2, theVec.z());
  }

  constexpr NCollection_Vec3<Element_t> GetColumn(const size_t theCol) const noexcept
  {
    return NCollection_Vec3<Element_t>(GetValue(0, theCol),
                                       GetValue(1, theCol),
                                       GetValue(2, theCol));
  }

  constexpr void SetColumn(const size_t theCol, const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(0, theCol, theVec.x());
    SetValue(1, theCol, theVec.y());
    SetValue(2, theCol, theVec.z());
  }

  constexpr NCollection_Vec3<Element_t> GetDiagonal() const noexcept
  {
    return NCollection_Vec3<Element_t>(GetValue(0, 0), GetValue(1, 1), GetValue(2, 2));
  }

  constexpr void SetDiagonal(const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(0, 0, theVec.x());
    SetValue(1, 1, theVec.y());
    SetValue(2, 2, theVec.z());
  }

  constexpr void InitZero() noexcept
  {
    for (int i = 0; i < 9; ++i)
    {
      myMat[i] = MyZeroArray[i];
    }
  }

  constexpr bool IsZero() const noexcept
  {
    for (int i = 0; i < 9; ++i)
    {
      if (myMat[i] != MyZeroArray[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr void InitIdentity() noexcept
  {
    for (int i = 0; i < 9; ++i)
    {
      myMat[i] = MyIdentityArray[i];
    }
  }

  constexpr bool IsIdentity() const noexcept
  {
    for (int i = 0; i < 9; ++i)
    {
      if (myMat[i] != MyIdentityArray[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr bool IsEqual(const NCollection_Mat3& theOther) const noexcept
  {
    for (int i = 0; i < 9; ++i)
    {
      if (myMat[i] != theOther.myMat[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr bool operator==(const NCollection_Mat3& theMat) const noexcept
  {
    return IsEqual(theMat);
  }

  constexpr bool operator!=(const NCollection_Mat3& theOther) const noexcept
  {
    return !IsEqual(theOther);
  }

  constexpr const Element_t* GetData() const noexcept { return myMat; }

  constexpr Element_t* ChangeData() noexcept { return myMat; }

  constexpr NCollection_Vec3<Element_t> operator*(
    const NCollection_Vec3<Element_t>& theVec) const noexcept
  {
    return NCollection_Vec3<Element_t>(
      GetValue(0, 0) * theVec.x() + GetValue(0, 1) * theVec.y() + GetValue(0, 2) * theVec.z(),
      GetValue(1, 0) * theVec.x() + GetValue(1, 1) * theVec.y() + GetValue(1, 2) * theVec.z(),
      GetValue(2, 0) * theVec.x() + GetValue(2, 1) * theVec.y() + GetValue(2, 2) * theVec.z());
  }

  static constexpr NCollection_Mat3 Multiply(const NCollection_Mat3& theMatA,
                                             const NCollection_Mat3& theMatB) noexcept
  {
    NCollection_Mat3 aMatRes;

    for (size_t aResElem = 0; aResElem < 9; ++aResElem)
    {
      aMatRes.myMat[aResElem] = (Element_t)0;
      for (size_t aInputElem = 0; aInputElem < 3; ++aInputElem)
      {
        aMatRes.myMat[aResElem] +=
          theMatA.GetValue(aResElem % 3, aInputElem) * theMatB.GetValue(aInputElem, aResElem / 3);
      }
    }

    return aMatRes;
  }

  constexpr void Multiply(const NCollection_Mat3& theMat) noexcept
  {
    *this = Multiply(*this, theMat);
  }

  constexpr NCollection_Mat3& operator*=(const NCollection_Mat3& theMat) noexcept
  {
    Multiply(theMat);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator*(const NCollection_Mat3& theMat) const noexcept
  {
    return Multiplied(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat3 Multiplied(const NCollection_Mat3& theMat) const noexcept
  {
    NCollection_Mat3 aTempMat(*this);
    aTempMat *= theMat;
    return aTempMat;
  }

  constexpr void Multiply(const Element_t theFactor) noexcept
  {
    for (size_t i = 0; i < 9; ++i)
    {
      myMat[i] *= theFactor;
    }
  }

  constexpr NCollection_Mat3& operator*=(const Element_t theFactor) noexcept
  {
    Multiply(theFactor);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator*(const Element_t theFactor) const noexcept
  {
    return Multiplied(theFactor);
  }

  [[nodiscard]] constexpr NCollection_Mat3 Multiplied(const Element_t theFactor) const noexcept
  {
    NCollection_Mat3 aTempMat(*this);
    aTempMat *= theFactor;
    return aTempMat;
  }

  constexpr void Divide(const Element_t theFactor)
  {
    for (size_t i = 0; i < 9; ++i)
    {
      myMat[i] /= theFactor;
    }
  }

  constexpr NCollection_Mat3& operator/=(const Element_t theScalar)
  {
    Divide(theScalar);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat3 Divided(const Element_t theScalar) const
  {
    NCollection_Mat3 aTempMat(*this);
    aTempMat /= theScalar;
    return aTempMat;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator/(const Element_t theScalar) const
  {
    return Divided(theScalar);
  }

  constexpr void Add(const NCollection_Mat3& theMat) noexcept
  {
    for (size_t i = 0; i < 9; ++i)
    {
      myMat[i] += theMat.myMat[i];
    }
  }

  constexpr NCollection_Mat3& operator+=(const NCollection_Mat3& theMat) noexcept
  {
    Add(theMat);
    return *this;
  }

  constexpr void Subtract(const NCollection_Mat3& theMat) noexcept
  {
    for (size_t i = 0; i < 9; ++i)
    {
      myMat[i] -= theMat.myMat[i];
    }
  }

  constexpr NCollection_Mat3& operator-=(const NCollection_Mat3& theMat) noexcept
  {
    Subtract(theMat);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat3 Added(const NCollection_Mat3& theMat) const noexcept
  {
    NCollection_Mat3 aMat(*this);
    aMat += theMat;
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator+(const NCollection_Mat3& theMat) const noexcept
  {
    return Added(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat3 Subtracted(const NCollection_Mat3& theMat) const noexcept
  {
    NCollection_Mat3 aMat(*this);
    aMat -= theMat;
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator-(const NCollection_Mat3& theMat) const noexcept
  {
    return Subtracted(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat3 Negated() const noexcept
  {
    NCollection_Mat3 aMat;
    for (size_t i = 0; i < 9; ++i)
    {
      aMat.myMat[i] = -myMat[i];
    }
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat3 operator-() const noexcept { return Negated(); }

  [[nodiscard]] constexpr NCollection_Mat3 Transposed() const noexcept
  {
    NCollection_Mat3 aTempMat;
    aTempMat.SetRow(0, GetColumn(0));
    aTempMat.SetRow(1, GetColumn(1));
    aTempMat.SetRow(2, GetColumn(2));
    return aTempMat;
  }

  constexpr void Transpose() noexcept { *this = Transposed(); }

  constexpr Element_t Determinant() const noexcept
  {
    return (GetValue(0, 0) * GetValue(1, 1) * GetValue(2, 2)
            + GetValue(0, 1) * GetValue(1, 2) * GetValue(2, 0)
            + GetValue(0, 2) * GetValue(1, 0) * GetValue(2, 1))
           - (GetValue(0, 2) * GetValue(1, 1) * GetValue(2, 0)
              + GetValue(0, 0) * GetValue(1, 2) * GetValue(2, 1)
              + GetValue(0, 1) * GetValue(1, 0) * GetValue(2, 2));
  }

  [[nodiscard]] constexpr NCollection_Mat3 Adjoint() const noexcept
  {
    NCollection_Mat3 aMat;
    aMat.SetRow(0, NCollection_Vec3<Element_t>::Cross(GetRow(1), GetRow(2)));
    aMat.SetRow(1, NCollection_Vec3<Element_t>::Cross(GetRow(2), GetRow(0)));
    aMat.SetRow(2, NCollection_Vec3<Element_t>::Cross(GetRow(0), GetRow(1)));
    return aMat;
  }

  bool Inverted(NCollection_Mat3& theInv, Element_t& theDet) const
  {
    const NCollection_Mat3 aMat = Adjoint();
    theDet                      = aMat.GetRow(0).Dot(GetRow(0));
    if (theDet == Element_t(0))
    {
      return false;
    }

    theInv = aMat.Transposed() / theDet;
    return true;
  }

  bool Inverted(NCollection_Mat3& theInv) const
  {
    Element_t aDet;
    return Inverted(theInv, aDet);
  }

  NCollection_Mat3 Inverted() const
  {
    NCollection_Mat3 anInv;
    if (!Inverted(anInv))
    {
      throw Standard_ConstructionError(
        "NCollection_Mat3::Inverted() - matrix has zero determinant");
    }
    return anInv;
  }

  template <typename Other_t>
  constexpr void ConvertFrom(const NCollection_Mat3<Other_t>& theFrom) noexcept
  {
    for (int anIdx = 0; anIdx < 9; ++anIdx)
    {
      myMat[anIdx] = static_cast<Element_t>(theFrom.myMat[anIdx]);
    }
  }

  static NCollection_Mat3<Element_t>& Map(Element_t* theData) noexcept
  {
    return *reinterpret_cast<NCollection_Mat3<Element_t>*>(theData);
  }

  static const NCollection_Mat3<Element_t>& Map(const Element_t* theData) noexcept
  {
    return *reinterpret_cast<const NCollection_Mat3<Element_t>*>(theData);
  }

  void DumpJson(Standard_OStream& theOStream, int) const
  {
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                     "NCollection_Mat3",
                                     9,
                                     GetValue(0, 0),
                                     GetValue(0, 1),
                                     GetValue(0, 2),
                                     GetValue(1, 0),
                                     GetValue(1, 1),
                                     GetValue(1, 2),
                                     GetValue(2, 0),
                                     GetValue(2, 1),
                                     GetValue(2, 2))
  }

private:
  Element_t myMat[9];

private:
  static constexpr Element_t MyZeroArray[9]     = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  static constexpr Element_t MyIdentityArray[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

  template <class OtherType>
  friend class NCollection_Mat3;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
  #include <type_traits>

static_assert(std::is_trivially_copyable<NCollection_Mat3<float>>::value,
              "NCollection_Mat3 is not is_trivially_copyable() structure!");
static_assert(std::is_standard_layout<NCollection_Mat3<float>>::value,
              "NCollection_Mat3 is not is_standard_layout() structure!");
static_assert(sizeof(NCollection_Mat3<float>) == sizeof(float) * 9,
              "NCollection_Mat3 is not packed/aligned!");
#endif

template <typename Element_t>
class NCollection_Mat4
{
public:
  static constexpr size_t Rows() noexcept { return 4; }

  static constexpr size_t Cols() noexcept { return 4; }

  static constexpr NCollection_Mat4 Identity() { return NCollection_Mat4(); }

  static constexpr NCollection_Mat4 Zero()
  {
    NCollection_Mat4 aMat;
    aMat.InitZero();
    return aMat;
  }

public:
  constexpr NCollection_Mat4() { InitIdentity(); }

  template <typename OtherElement_t>
  explicit constexpr NCollection_Mat4(const NCollection_Mat4<OtherElement_t>& theOtherMat4) noexcept
  {
    ConvertFrom(theOtherMat4);
  }

  constexpr Element_t GetValue(const size_t theRow, const size_t theCol) const noexcept
  {
    return myMat[theCol * 4 + theRow];
  }

  constexpr Element_t& ChangeValue(const size_t theRow, const size_t theCol) noexcept
  {
    return myMat[theCol * 4 + theRow];
  }

  constexpr void SetValue(const size_t    theRow,
                          const size_t    theCol,
                          const Element_t theValue) noexcept
  {
    myMat[theCol * 4 + theRow] = theValue;
  }

  constexpr Element_t& operator()(const size_t theRow, const size_t theCol) noexcept
  {
    return ChangeValue(theRow, theCol);
  }

  constexpr Element_t operator()(const size_t theRow, const size_t theCol) const noexcept
  {
    return GetValue(theRow, theCol);
  }

  constexpr NCollection_Vec4<Element_t> GetRow(const size_t theRow) const noexcept
  {
    return NCollection_Vec4<Element_t>(GetValue(theRow, 0),
                                       GetValue(theRow, 1),
                                       GetValue(theRow, 2),
                                       GetValue(theRow, 3));
  }

  constexpr void SetRow(const size_t theRow, const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(theRow, 0, theVec.x());
    SetValue(theRow, 1, theVec.y());
    SetValue(theRow, 2, theVec.z());
  }

  constexpr void SetRow(const size_t theRow, const NCollection_Vec4<Element_t>& theVec) noexcept
  {
    SetValue(theRow, 0, theVec.x());
    SetValue(theRow, 1, theVec.y());
    SetValue(theRow, 2, theVec.z());
    SetValue(theRow, 3, theVec.w());
  }

  constexpr NCollection_Vec4<Element_t> GetColumn(const size_t theCol) const noexcept
  {
    return NCollection_Vec4<Element_t>(GetValue(0, theCol),
                                       GetValue(1, theCol),
                                       GetValue(2, theCol),
                                       GetValue(3, theCol));
  }

  constexpr void SetColumn(const size_t theCol, const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(0, theCol, theVec.x());
    SetValue(1, theCol, theVec.y());
    SetValue(2, theCol, theVec.z());
  }

  constexpr void SetColumn(const size_t theCol, const NCollection_Vec4<Element_t>& theVec) noexcept
  {
    SetValue(0, theCol, theVec.x());
    SetValue(1, theCol, theVec.y());
    SetValue(2, theCol, theVec.z());
    SetValue(3, theCol, theVec.w());
  }

  constexpr NCollection_Vec4<Element_t> GetDiagonal() const noexcept
  {
    return NCollection_Vec4<Element_t>(GetValue(0, 0),
                                       GetValue(1, 1),
                                       GetValue(2, 2),
                                       GetValue(3, 3));
  }

  constexpr void SetDiagonal(const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    SetValue(0, 0, theVec.x());
    SetValue(1, 1, theVec.y());
    SetValue(2, 2, theVec.z());
  }

  constexpr void SetDiagonal(const NCollection_Vec4<Element_t>& theVec) noexcept
  {
    SetValue(0, 0, theVec.x());
    SetValue(1, 1, theVec.y());
    SetValue(2, 2, theVec.z());
    SetValue(3, 3, theVec.w());
  }

  constexpr NCollection_Mat3<Element_t> GetMat3() const noexcept
  {
    NCollection_Mat3<Element_t> aMat;
    aMat.SetColumn(0, GetColumn(0).xyz());
    aMat.SetColumn(1, GetColumn(1).xyz());
    aMat.SetColumn(2, GetColumn(2).xyz());
    return aMat;
  }

  constexpr void InitZero() noexcept
  {
    for (int i = 0; i < 16; ++i)
    {
      myMat[i] = MyZeroArray[i];
    }
  }

  constexpr bool IsZero() const noexcept
  {
    for (int i = 0; i < 16; ++i)
    {
      if (myMat[i] != MyZeroArray[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr void InitIdentity() noexcept
  {
    for (int i = 0; i < 16; ++i)
    {
      myMat[i] = MyIdentityArray[i];
    }
  }

  constexpr bool IsIdentity() const noexcept
  {
    for (int i = 0; i < 16; ++i)
    {
      if (myMat[i] != MyIdentityArray[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr bool IsEqual(const NCollection_Mat4& theOther) const noexcept
  {
    for (int i = 0; i < 16; ++i)
    {
      if (myMat[i] != theOther.myMat[i])
      {
        return false;
      }
    }
    return true;
  }

  constexpr bool operator==(const NCollection_Mat4& theOther) const noexcept
  {
    return IsEqual(theOther);
  }

  constexpr bool operator!=(const NCollection_Mat4& theOther) const noexcept
  {
    return !IsEqual(theOther);
  }

  constexpr const Element_t* GetData() const noexcept { return myMat; }

  constexpr Element_t* ChangeData() noexcept { return myMat; }

  constexpr NCollection_Vec4<Element_t> operator*(
    const NCollection_Vec4<Element_t>& theVec) const noexcept
  {
    return NCollection_Vec4<Element_t>(
      GetValue(0, 0) * theVec.x() + GetValue(0, 1) * theVec.y() + GetValue(0, 2) * theVec.z()
        + GetValue(0, 3) * theVec.w(),
      GetValue(1, 0) * theVec.x() + GetValue(1, 1) * theVec.y() + GetValue(1, 2) * theVec.z()
        + GetValue(1, 3) * theVec.w(),
      GetValue(2, 0) * theVec.x() + GetValue(2, 1) * theVec.y() + GetValue(2, 2) * theVec.z()
        + GetValue(2, 3) * theVec.w(),
      GetValue(3, 0) * theVec.x() + GetValue(3, 1) * theVec.y() + GetValue(3, 2) * theVec.z()
        + GetValue(3, 3) * theVec.w());
  }

  static constexpr NCollection_Mat4 Multiply(const NCollection_Mat4& theMatA,
                                             const NCollection_Mat4& theMatB) noexcept
  {
    NCollection_Mat4 aMatRes;

    for (size_t aResElem = 0; aResElem < 16; ++aResElem)
    {
      aMatRes.myMat[aResElem] = (Element_t)0;
      for (size_t aInputElem = 0; aInputElem < 4; ++aInputElem)
      {
        aMatRes.myMat[aResElem] +=
          theMatA.GetValue(aResElem % 4, aInputElem) * theMatB.GetValue(aInputElem, aResElem / 4);
      }
    }

    return aMatRes;
  }

  constexpr void Multiply(const NCollection_Mat4& theMat) noexcept
  {
    *this = Multiply(*this, theMat);
  }

  constexpr NCollection_Mat4& operator*=(const NCollection_Mat4& theMat) noexcept
  {
    Multiply(theMat);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator*(const NCollection_Mat4& theMat) const noexcept
  {
    return Multiplied(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat4 Multiplied(const NCollection_Mat4& theMat) const noexcept
  {
    NCollection_Mat4 aTempMat(*this);
    aTempMat *= theMat;
    return aTempMat;
  }

  constexpr void Multiply(const Element_t theFactor) noexcept
  {
    for (size_t i = 0; i < 16; ++i)
    {
      myMat[i] *= theFactor;
    }
  }

  constexpr NCollection_Mat4& operator*=(const Element_t theFactor) noexcept
  {
    Multiply(theFactor);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator*(const Element_t theFactor) const noexcept
  {
    return Multiplied(theFactor);
  }

  [[nodiscard]] constexpr NCollection_Mat4 Multiplied(const Element_t theFactor) const noexcept
  {
    NCollection_Mat4 aTempMat(*this);
    aTempMat *= theFactor;
    return aTempMat;
  }

  constexpr void Divide(const Element_t theFactor)
  {
    for (size_t i = 0; i < 16; ++i)
    {
      myMat[i] /= theFactor;
    }
  }

  constexpr NCollection_Mat4& operator/=(const Element_t theScalar)
  {
    Divide(theScalar);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat4 Divided(const Element_t theScalar) const
  {
    NCollection_Mat4 aTempMat(*this);
    aTempMat /= theScalar;
    return aTempMat;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator/(const Element_t theScalar) const
  {
    return Divided(theScalar);
  }

  constexpr void Add(const NCollection_Mat4& theMat) noexcept
  {
    for (size_t i = 0; i < 16; ++i)
    {
      myMat[i] += theMat.myMat[i];
    }
  }

  constexpr NCollection_Mat4& operator+=(const NCollection_Mat4& theMat) noexcept
  {
    Add(theMat);
    return *this;
  }

  constexpr void Subtract(const NCollection_Mat4& theMat) noexcept
  {
    for (size_t i = 0; i < 16; ++i)
    {
      myMat[i] -= theMat.myMat[i];
    }
  }

  constexpr NCollection_Mat4& operator-=(const NCollection_Mat4& theMat) noexcept
  {
    Subtract(theMat);
    return *this;
  }

  [[nodiscard]] constexpr NCollection_Mat4 Added(const NCollection_Mat4& theMat) const noexcept
  {
    NCollection_Mat4 aMat(*this);
    aMat += theMat;
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator+(const NCollection_Mat4& theMat) const noexcept
  {
    return Added(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat4 Subtracted(const NCollection_Mat4& theMat) const noexcept
  {
    NCollection_Mat4 aMat(*this);
    aMat -= theMat;
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator-(const NCollection_Mat4& theMat) const noexcept
  {
    return Subtracted(theMat);
  }

  [[nodiscard]] constexpr NCollection_Mat4 Negated() const noexcept
  {
    NCollection_Mat4 aMat;
    for (size_t i = 0; i < 16; ++i)
    {
      aMat.myMat[i] = -myMat[i];
    }
    return aMat;
  }

  [[nodiscard]] constexpr NCollection_Mat4 operator-() const noexcept { return Negated(); }

  constexpr void Translate(const NCollection_Vec3<Element_t>& theVec) noexcept
  {
    NCollection_Mat4 aTempMat;
    aTempMat.SetColumn(3, theVec);
    this->Multiply(aTempMat);
  }

  [[nodiscard]] constexpr NCollection_Mat4 Transposed() const noexcept
  {
    NCollection_Mat4 aTempMat;
    aTempMat.SetRow(0, GetColumn(0));
    aTempMat.SetRow(1, GetColumn(1));
    aTempMat.SetRow(2, GetColumn(2));
    aTempMat.SetRow(3, GetColumn(3));
    return aTempMat;
  }

  constexpr void Transpose() noexcept { *this = Transposed(); }

  bool Inverted(NCollection_Mat4<Element_t>& theOutMx, Element_t& theDet) const
  {
    Element_t* inv = theOutMx.myMat;

    const Element_t* m = myMat;

    inv[0] = m[5] * (m[10] * m[15] - m[11] * m[14]) - m[9] * (m[6] * m[15] - m[7] * m[14])
             - m[13] * (m[7] * m[10] - m[6] * m[11]);

    inv[1] = m[1] * (m[11] * m[14] - m[10] * m[15]) - m[9] * (m[3] * m[14] - m[2] * m[15])
             - m[13] * (m[2] * m[11] - m[3] * m[10]);

    inv[2] = m[1] * (m[6] * m[15] - m[7] * m[14]) - m[5] * (m[2] * m[15] - m[3] * m[14])
             - m[13] * (m[3] * m[6] - m[2] * m[7]);

    inv[3] = m[1] * (m[7] * m[10] - m[6] * m[11]) - m[5] * (m[3] * m[10] - m[2] * m[11])
             - m[9] * (m[2] * m[7] - m[3] * m[6]);

    inv[4] = m[4] * (m[11] * m[14] - m[10] * m[15]) - m[8] * (m[7] * m[14] - m[6] * m[15])
             - m[12] * (m[6] * m[11] - m[7] * m[10]);

    inv[5] = m[0] * (m[10] * m[15] - m[11] * m[14]) - m[8] * (m[2] * m[15] - m[3] * m[14])
             - m[12] * (m[3] * m[10] - m[2] * m[11]);

    inv[6] = m[0] * (m[7] * m[14] - m[6] * m[15]) - m[4] * (m[3] * m[14] - m[2] * m[15])
             - m[12] * (m[2] * m[7] - m[3] * m[6]);

    inv[7] = m[0] * (m[6] * m[11] - m[7] * m[10]) - m[4] * (m[2] * m[11] - m[3] * m[10])
             - m[8] * (m[3] * m[6] - m[2] * m[7]);

    inv[8] = m[4] * (m[9] * m[15] - m[11] * m[13]) - m[8] * (m[5] * m[15] - m[7] * m[13])
             - m[12] * (m[7] * m[9] - m[5] * m[11]);

    inv[9] = m[0] * (m[11] * m[13] - m[9] * m[15]) - m[8] * (m[3] * m[13] - m[1] * m[15])
             - m[12] * (m[1] * m[11] - m[3] * m[9]);

    inv[10] = m[0] * (m[5] * m[15] - m[7] * m[13]) - m[4] * (m[1] * m[15] - m[3] * m[13])
              - m[12] * (m[3] * m[5] - m[1] * m[7]);

    inv[11] = m[0] * (m[7] * m[9] - m[5] * m[11]) - m[4] * (m[3] * m[9] - m[1] * m[11])
              - m[8] * (m[1] * m[7] - m[3] * m[5]);

    inv[12] = m[4] * (m[10] * m[13] - m[9] * m[14]) - m[8] * (m[6] * m[13] - m[5] * m[14])
              - m[12] * (m[5] * m[10] - m[6] * m[9]);

    inv[13] = m[0] * (m[9] * m[14] - m[10] * m[13]) - m[8] * (m[1] * m[14] - m[2] * m[13])
              - m[12] * (m[2] * m[9] - m[1] * m[10]);

    inv[14] = m[0] * (m[6] * m[13] - m[5] * m[14]) - m[4] * (m[2] * m[13] - m[1] * m[14])
              - m[12] * (m[1] * m[6] - m[2] * m[5]);

    inv[15] = m[0] * (m[5] * m[10] - m[6] * m[9]) - m[4] * (m[1] * m[10] - m[2] * m[9])
              - m[8] * (m[2] * m[5] - m[1] * m[6]);

    theDet = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (theDet == 0)
    {
      return false;
    }

    const Element_t aDiv = (Element_t)1. / theDet;
    for (int i = 0; i < 16; ++i)
    {
      inv[i] *= aDiv;
    }
    return true;
  }

  bool Inverted(NCollection_Mat4<Element_t>& theOutMx) const
  {
    Element_t aDet;
    return Inverted(theOutMx, aDet);
  }

  NCollection_Mat4 Inverted() const
  {
    NCollection_Mat4 anInv;
    if (!Inverted(anInv))
    {
      throw Standard_ConstructionError(
        "NCollection_Mat4::Inverted() - matrix has zero determinant");
    }
    return anInv;
  }

  constexpr Element_t DeterminantMat3() const noexcept
  {
    return (GetValue(0, 0) * GetValue(1, 1) * GetValue(2, 2)
            + GetValue(0, 1) * GetValue(1, 2) * GetValue(2, 0)
            + GetValue(0, 2) * GetValue(1, 0) * GetValue(2, 1))
           - (GetValue(0, 2) * GetValue(1, 1) * GetValue(2, 0)
              + GetValue(0, 0) * GetValue(1, 2) * GetValue(2, 1)
              + GetValue(0, 1) * GetValue(1, 0) * GetValue(2, 2));
  }

  [[nodiscard]] constexpr NCollection_Mat4<Element_t> Adjoint() const noexcept
  {
    NCollection_Mat4<Element_t> aMat;
    aMat.SetRow(0, crossVec4(GetRow(1), GetRow(2), GetRow(3)));
    aMat.SetRow(1, crossVec4(-GetRow(0), GetRow(2), GetRow(3)));
    aMat.SetRow(2, crossVec4(GetRow(0), GetRow(1), GetRow(3)));
    aMat.SetRow(3, crossVec4(-GetRow(0), GetRow(1), GetRow(2)));
    return aMat;
  }

  template <typename Other_t>
  constexpr void ConvertFrom(const NCollection_Mat4<Other_t>& theFrom) noexcept
  {
    for (int anIdx = 0; anIdx < 16; ++anIdx)
    {
      myMat[anIdx] = static_cast<Element_t>(theFrom.myMat[anIdx]);
    }
  }

  template <typename Other_t>
  constexpr void Convert(const NCollection_Mat4<Other_t>& theFrom) noexcept
  {
    ConvertFrom(theFrom);
  }

  static NCollection_Mat4<Element_t>& Map(Element_t* theData) noexcept
  {
    return *reinterpret_cast<NCollection_Mat4<Element_t>*>(theData);
  }

  static const NCollection_Mat4<Element_t>& Map(const Element_t* theData) noexcept
  {
    return *reinterpret_cast<const NCollection_Mat4<Element_t>*>(theData);
  }

  void DumpJson(Standard_OStream& theOStream, int) const
  {
    OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                     "NCollection_Mat4",
                                     16,
                                     GetValue(0, 0),
                                     GetValue(0, 1),
                                     GetValue(0, 2),
                                     GetValue(0, 3),
                                     GetValue(1, 0),
                                     GetValue(1, 1),
                                     GetValue(1, 2),
                                     GetValue(1, 3),
                                     GetValue(2, 0),
                                     GetValue(2, 1),
                                     GetValue(2, 2),
                                     GetValue(2, 3),
                                     GetValue(3, 0),
                                     GetValue(3, 1),
                                     GetValue(3, 2),
                                     GetValue(3, 3))
  }

private:
  static constexpr NCollection_Vec4<Element_t> crossVec4(
    const NCollection_Vec4<Element_t>& theA,
    const NCollection_Vec4<Element_t>& theB,
    const NCollection_Vec4<Element_t>& theC) noexcept
  {
    const Element_t aD1 = (theB.z() * theC.w()) - (theB.w() * theC.z());
    const Element_t aD2 = (theB.y() * theC.w()) - (theB.w() * theC.y());
    const Element_t aD3 = (theB.y() * theC.z()) - (theB.z() * theC.y());
    const Element_t aD4 = (theB.x() * theC.w()) - (theB.w() * theC.x());
    const Element_t aD5 = (theB.x() * theC.z()) - (theB.z() * theC.x());
    const Element_t aD6 = (theB.x() * theC.y()) - (theB.y() * theC.x());

    NCollection_Vec4<Element_t> aVec;
    aVec.x() = -theA.y() * aD1 + theA.z() * aD2 - theA.w() * aD3;
    aVec.y() = theA.x() * aD1 - theA.z() * aD4 + theA.w() * aD5;
    aVec.z() = -theA.x() * aD2 + theA.y() * aD4 - theA.w() * aD6;
    aVec.w() = theA.x() * aD3 - theA.y() * aD5 + theA.z() * aD6;
    return aVec;
  }

private:
  Element_t myMat[16];

private:
  static constexpr Element_t MyZeroArray[16]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static constexpr Element_t MyIdentityArray[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  template <class OtherType>
  friend class NCollection_Mat4;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
  #include <type_traits>

static_assert(std::is_trivially_copyable<NCollection_Mat4<float>>::value,
              "NCollection_Mat4 is not is_trivially_copyable() structure!");
static_assert(std::is_standard_layout<NCollection_Mat4<float>>::value,
              "NCollection_Mat4 is not is_standard_layout() structure!");
static_assert(sizeof(NCollection_Mat4<float>) == sizeof(float) * 16,
              "NCollection_Mat4 is not packed/aligned!");
#endif
