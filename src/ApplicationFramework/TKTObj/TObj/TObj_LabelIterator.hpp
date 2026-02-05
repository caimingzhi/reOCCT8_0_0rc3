#pragma once

#include <TObj_Object.hpp>

#include <TDF_Label.hpp>
#include <TDF_ChildIterator.hpp>
#include <TObj_ObjectIterator.hpp>

/**
 * This class is a basis for OCAF based iterators.
 */

class TObj_LabelIterator : public TObj_ObjectIterator
{

protected:
  /**
   * Constructor
   */

  //! Creates an Empty Iterator
  Standard_EXPORT TObj_LabelIterator();

public:
  /**
   * Constructor
   */

  //! Creates an iterator an initialize it by theLabel and recursive flag.
  //! If isRecursive is true make recursive iterations
  Standard_EXPORT TObj_LabelIterator(const TDF_Label& theLabel, const bool isRecursive = false);

public:
  /**
   * Redefined methods
   */

  //! Returns True if there is a current Item in the iteration.
  bool More() const override { return !myNode.IsNull(); }

  //! Move to the next Item
  Standard_EXPORT void Next() override;

  //! Returns the current item
  occ::handle<TObj_Object> Value() const override { return myObject; }

  //! Returns the label of the current item
  inline const TDF_Label& LabelValue() const { return myNode; }

protected:
  /**
   * Iterating methods
   */

  //! Shifts iterator to the next object
  virtual void MakeStep() = 0;

protected:
  /**
   * Internal methods
   */

  //! Initialize Iterator by the theLabel
  void Init(const TDF_Label& theLabel, const bool isRecursive = false)
  {
    myIterator.Initialize(theLabel, isRecursive);
  }

protected:
  /**
   * Fields
   */
  TDF_Label                myNode;     //!< Current node
  TDF_ChildIterator        myIterator; //!< OCAF Child iterator
  occ::handle<TObj_Object> myObject;   //!< Current Object

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_LabelIterator, TObj_ObjectIterator)
};

//! Define handle class for TObj_LabelIterator

#ifdef _MSC_VER
  #pragma once
#endif
