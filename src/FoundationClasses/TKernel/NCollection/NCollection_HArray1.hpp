#pragma once

#include <NCollection_Array1.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

template <typename TheItemType>
class NCollection_HArray1 : public NCollection_Array1<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Array1<TheItemType> Array1Type;
  typedef TheItemType                     value_type;

public:
  NCollection_HArray1()
      : Array1Type()
  {
  }

  NCollection_HArray1(const int theLower, const int theUpper)
      : Array1Type(theLower, theUpper)
  {
  }

  NCollection_HArray1(const int theLower, const int theUpper, const TheItemType& theValue)
      : Array1Type(theLower, theUpper)
  {
    Array1Type::Init(theValue);
  }

  explicit NCollection_HArray1(const TheItemType& theBegin,
                               const int          theLower,
                               const int          theUpper,
                               const bool         theUseBuffer)
      : Array1Type(theBegin, theLower, theUpper, theUseBuffer)
  {
  }

  NCollection_HArray1(const Array1Type& theOther)
      : Array1Type(theOther)
  {
  }

  const Array1Type& Array1() const noexcept { return *this; }

  Array1Type& ChangeArray1() noexcept { return *this; }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HArray1, Standard_Transient)
};
