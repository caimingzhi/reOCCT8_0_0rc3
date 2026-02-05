#pragma once

#include <NCollection_Array1.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! Template class for Handle-managed 1D arrays.
//! Inherits from both NCollection_Array1<TheItemType> and Standard_Transient,
//! providing reference-counted array functionality.
template <typename TheItemType>
class NCollection_HArray1 : public NCollection_Array1<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Array1<TheItemType> Array1Type;
  typedef TheItemType                     value_type;

public:
  //! Default constructor.
  NCollection_HArray1()
      : Array1Type()
  {
  }

  //! Constructor with bounds.
  //! @param theLower lower bound of the array
  //! @param theUpper upper bound of the array
  NCollection_HArray1(const int theLower, const int theUpper)
      : Array1Type(theLower, theUpper)
  {
  }

  //! Constructor with bounds and initial value.
  //! @param theLower lower bound of the array
  //! @param theUpper upper bound of the array
  //! @param theValue initial value for all elements
  NCollection_HArray1(const int theLower, const int theUpper, const TheItemType& theValue)
      : Array1Type(theLower, theUpper)
  {
    Array1Type::Init(theValue);
  }

  //! Constructor from C array.
  //! @param theBegin reference to the first element of a C array
  //! @param theLower lower bound of the array
  //! @param theUpper upper bound of the array
  //! @param theUseBuffer flag indicating whether to use external buffer (must be explicit)
  explicit NCollection_HArray1(const TheItemType& theBegin,
                               const int          theLower,
                               const int          theUpper,
                               const bool         theUseBuffer)
      : Array1Type(theBegin, theLower, theUpper, theUseBuffer)
  {
  }

  //! Copy constructor from array.
  //! @param theOther the array to copy from
  NCollection_HArray1(const Array1Type& theOther)
      : Array1Type(theOther)
  {
  }

  //! Returns const reference to the underlying array.
  const Array1Type& Array1() const noexcept { return *this; }

  //! Returns mutable reference to the underlying array.
  Array1Type& ChangeArray1() noexcept { return *this; }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HArray1, Standard_Transient)
};
