#pragma once


#include <TObj_LabelIterator.hpp>

/**
 * This class provides an iterator by references of the object
 * (implements TObj_ReferenceIterator interface)
 */

class TObj_ReferenceIterator : public TObj_LabelIterator
{
public:
  /*
   * Constructor
   */

  //! Creates the iterator on references in partition
  //! theType narrows a variety of iterated objects
  Standard_EXPORT TObj_ReferenceIterator(const TDF_Label&                  theLabel,
                                         const occ::handle<Standard_Type>& theType      = nullptr,
                                         const bool                        theRecursive = true);

protected:
  /**
   * Internal methods
   */

  //! Shift iterator to the next object
  Standard_EXPORT void MakeStep() override;

  occ::handle<Standard_Type> myType; //!< Type of objects to iterate on

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_ReferenceIterator, TObj_LabelIterator)
};

//! Define handle class for TObj_ReferenceIterator

#ifdef _MSC_VER
#pragma once
#endif
