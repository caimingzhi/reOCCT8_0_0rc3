#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>

//! This type of Binder allows to attach as result, besides a
//! Transient Object, an Integer Value, which can be an Index
//! in the Object if it defines a List, for instance
//!
//! This Binder is otherwise a kind of SimpleBinderOfTransient,
//! i.e. its basic result (for iterators, etc) is the Transient
class Transfer_BinderOfTransientInteger : public Transfer_SimpleBinderOfTransient
{

public:
  //! Creates an empty BinderOfTransientInteger; Default value for
  //! the integer part is zero
  Standard_EXPORT Transfer_BinderOfTransientInteger();

  //! Sets a value for the integer part
  Standard_EXPORT void SetInteger(const int value);

  //! Returns the value set for the integer part
  Standard_EXPORT int Integer() const;

  DEFINE_STANDARD_RTTIEXT(Transfer_BinderOfTransientInteger, Transfer_SimpleBinderOfTransient)

private:
  int theintval;
};
