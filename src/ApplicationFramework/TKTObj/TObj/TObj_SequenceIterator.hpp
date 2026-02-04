#pragma once


#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TObj_ObjectIterator.hpp>
class TObj_Object;

/**
 * This class is an iterator on sequence
 */

class TObj_SequenceIterator : public TObj_ObjectIterator
{

protected:
  /**
   * Constructor
   */

  //! Creates an Empty Iterator
  Standard_EXPORT TObj_SequenceIterator();

public:
  /**
   * Constructor
   */

  //! Creates an iterator an initialize it by sequence of objects.
  Standard_EXPORT TObj_SequenceIterator(
    const occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>>& theObjects,
    const occ::handle<Standard_Type>&                                   theType = nullptr);

public:
  /**
   * Redefined methods
   */

  //! Returns True if there is a current Item in the iteration.
  Standard_EXPORT bool More() const override;

  //! Move to the next Item
  Standard_EXPORT void Next() override;

  //! Returns the current item
  Standard_EXPORT occ::handle<TObj_Object> Value() const override;

protected:
  /**
   * Fields
   */
  int                        myIndex; //!< current index of object in sequence
  occ::handle<Standard_Type> myType;  //!< type of object
  occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>> myObjects; //!< sequence of objects

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_SequenceIterator, TObj_ObjectIterator)
};

//! Define handle class for TObj_SequenceIterator

#ifdef _MSC_VER
#pragma once
#endif
