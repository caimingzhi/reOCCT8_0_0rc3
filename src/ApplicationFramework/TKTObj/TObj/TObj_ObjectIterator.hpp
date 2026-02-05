#pragma once

#include <Standard_Handle.hpp>
#include <Standard_DefineHandle.hpp>

class TObj_Object;

/**
 * This class provides an iterator by objects in a partition.
 * (implements TObj_ObjectIterator interface)
 */

class TObj_ObjectIterator : public Standard_Transient
{
public:
  /*
   * Methods to iterate on a objects
   */

  //! Returns True if iteration is not finished and method Current()
  //! will give the object.
  //! Default implementation returns False
  virtual Standard_EXPORT bool More() const;

  //! Iterates to the next object
  //! Default implementation does nothing
  virtual Standard_EXPORT void Next();

  //! Returns current object (or null if iteration has finished)
  //! Default implementation returns null handle
  virtual Standard_EXPORT occ::handle<TObj_Object> Value() const;

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_ObjectIterator, Standard_Transient)
};

//! Define handle class for TObj_ObjectIterator

#ifdef _MSC_VER
  #pragma once
#endif
