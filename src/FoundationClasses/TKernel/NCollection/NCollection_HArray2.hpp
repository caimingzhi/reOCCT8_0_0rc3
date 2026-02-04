#pragma once


#include <NCollection_Array2.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! Template class for Handle-managed 2D arrays.
//! Inherits from both NCollection_Array2<TheItemType> and Standard_Transient,
//! providing reference-counted 2D array functionality.
template <typename TheItemType>
class NCollection_HArray2 : public NCollection_Array2<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Array2<TheItemType> Array2Type;
  typedef TheItemType                     value_type;

public:
  //! Constructor with bounds.
  //! @param theRowLow lower row bound
  //! @param theRowUpp upper row bound
  //! @param theColLow lower column bound
  //! @param theColUpp upper column bound
  NCollection_HArray2(const int theRowLow,
                      const int theRowUpp,
                      const int theColLow,
                      const int theColUpp)
      : Array2Type(theRowLow, theRowUpp, theColLow, theColUpp)
  {
  }

  //! Constructor with bounds and initial value.
  //! @param theRowLow lower row bound
  //! @param theRowUpp upper row bound
  //! @param theColLow lower column bound
  //! @param theColUpp upper column bound
  //! @param theValue initial value for all elements
  NCollection_HArray2(const int          theRowLow,
                      const int          theRowUpp,
                      const int          theColLow,
                      const int          theColUpp,
                      const TheItemType& theValue)
      : Array2Type(theRowLow, theRowUpp, theColLow, theColUpp)
  {
    Array2Type::Init(theValue);
  }

  //! Copy constructor from array.
  //! @param theOther the array to copy from
  NCollection_HArray2(const Array2Type& theOther)
      : Array2Type(theOther)
  {
  }

  //! Returns const reference to the underlying array.
  const Array2Type& Array2() const noexcept { return *this; }

  //! Returns mutable reference to the underlying array.
  Array2Type& ChangeArray2() noexcept { return *this; }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HArray2, Standard_Transient)
};

