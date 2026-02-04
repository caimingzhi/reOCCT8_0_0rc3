#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <Standard_Transient.hpp>

//! This class simply allows to access an Integer value through a
//! Handle, as a String can be (by using HString).
//! Hence, this value can be accessed : read and modified, without
//! passing through the specific object which detains it. Thus,
//! parameters of a Selection or a Dispatch (according its type)
//! can be controlled directly from the ShareOut which contains them
//!
//! Additionally, an IntParam can be bound to a Static.
//! Remember that for a String, binding is immediate, because the
//! string value of a Static is a HAsciiString, it then suffices
//! to get its Handle.
//! For an Integer, an IntParam can designate (by its name) a
//! Static : each time its value is required or set, the Static
//! is acknowledged
class IFSelect_IntParam : public Standard_Transient
{

public:
  //! Creates an IntParam. Initial value is set to zer
  Standard_EXPORT IFSelect_IntParam();

  //! Commands this IntParam to be bound to a Static
  //! Hence, Value will return the value if this Static if it is set
  //! Else, Value works on the locally stored value
  //! SetValue also will set the value of the Static
  //! This works only for a present static of type integer or enum
  //! Else, it is ignored
  //!
  //! If <statname> is empty, disconnects the IntParam from Static
  Standard_EXPORT void SetStaticName(const char* statname);

  //! Returns the name of static parameter to which this IntParam
  //! is bound, empty if none
  Standard_EXPORT const char* StaticName() const;

  //! Reads Integer Value of the IntParam. If a StaticName is
  //! defined and the Static is set, looks in priority the value
  //! of the static
  Standard_EXPORT int Value() const;

  //! Sets a new Integer Value for the IntParam. If a StaticName is
  //! defined and the Static is set, also sets the value of the static
  Standard_EXPORT void SetValue(const int val);

  DEFINE_STANDARD_RTTIEXT(IFSelect_IntParam, Standard_Transient)

private:
  int                     theval;
  TCollection_AsciiString thestn;
};

