#pragma once

#include <NCollection_Array2.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

template <typename TheItemType>
class NCollection_HArray2 : public NCollection_Array2<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Array2<TheItemType> Array2Type;
  typedef TheItemType                     value_type;

public:
  NCollection_HArray2(const int theRowLow,
                      const int theRowUpp,
                      const int theColLow,
                      const int theColUpp)
      : Array2Type(theRowLow, theRowUpp, theColLow, theColUpp)
  {
  }

  NCollection_HArray2(const int          theRowLow,
                      const int          theRowUpp,
                      const int          theColLow,
                      const int          theColUpp,
                      const TheItemType& theValue)
      : Array2Type(theRowLow, theRowUpp, theColLow, theColUpp)
  {
    Array2Type::Init(theValue);
  }

  NCollection_HArray2(const Array2Type& theOther)
      : Array2Type(theOther)
  {
  }

  const Array2Type& Array2() const noexcept { return *this; }

  Array2Type& ChangeArray2() noexcept { return *this; }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HArray2, Standard_Transient)
};
