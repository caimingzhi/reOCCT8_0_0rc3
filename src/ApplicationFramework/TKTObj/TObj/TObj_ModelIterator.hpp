#pragma once

#include <TObj_Object.hpp>
#include <NCollection_Sequence.hpp>
#include <TObj_ObjectIterator.hpp>

/**
 * This class provides an iterator by all objects in the model.
 */

class TObj_ModelIterator : public TObj_ObjectIterator
{
public:
  /**
   * Constructor
   */
  //! Creates Iterator and initialize it by Model`s label
  Standard_EXPORT TObj_ModelIterator(const occ::handle<TObj_Model>& theModel);

public:
  /**
   * Methods to iterate on objects.
   */

  //! Returns True if iteration is not finished and method Value()
  //! will give the object
  Standard_EXPORT bool More() const override;

  //! Iterates to the next object
  Standard_EXPORT void Next() override;

  //! Returns current object (or MainObj of Model if iteration has finished)
  Standard_EXPORT occ::handle<TObj_Object> Value() const override;

protected:
  /**
   * private methods
   */

  //! Add iterator on children of indicated object recursively.
  virtual Standard_EXPORT void addIterator(const occ::handle<TObj_Object>& theObj);

protected:
  /**
   * Fields
   */
  occ::handle<TObj_Object> myObject; //!< Current object
  NCollection_Sequence<occ::handle<TObj_ObjectIterator>>
    myIterSeq; //!< Sequence of iterators in model

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_ModelIterator, TObj_ObjectIterator)
};

//! Define handle class for TObj_ObjectIterator

#ifdef _MSC_VER
  #pragma once
#endif
