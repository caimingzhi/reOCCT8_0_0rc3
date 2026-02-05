#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_Element.hpp>
#include <Standard_CString.hpp>

//! an TransientElem defines an Element for a specific input class
//! its definition includes the value of the Key to be mapped,
//! and the HashCoder associated to the class of the Key
//!
//! Transient from Standard defines the class to be keyed
//! MapTransientHasher from TColStd is the associated Hasher
//! DataInfo from MoniTool is an additional class which helps to provide
//! information on the value (template : see DataInfo)
class MoniTool_TransientElem : public MoniTool_Element
{

public:
  //! Creates a TransientElem with a Value. This Value can then not be
  //! changed. It is used by the Hasher to compute the HashCode,
  //! which will then be stored for an immediate reading.
  Standard_EXPORT MoniTool_TransientElem(const occ::handle<Standard_Transient>& akey);

  //! Returns the contained value
  Standard_EXPORT const occ::handle<Standard_Transient>& Value() const;

  //! Specific testof equality : defined as False if <other> has
  //! not the same true Type, else contents are compared (by
  //! C++ operator ==)
  Standard_EXPORT bool Equates(const occ::handle<MoniTool_Element>& other) const override;

  //! Returns the Type of the Value. By default, returns the
  //! DynamicType of <me>, but can be redefined
  Standard_EXPORT occ::handle<Standard_Type> ValueType() const override;

  //! Returns the name of the Type of the Value. Default is name
  //! of ValueType, unless it is for a non-handled object
  Standard_EXPORT const char* ValueTypeName() const override;

  DEFINE_STANDARD_RTTIEXT(MoniTool_TransientElem, MoniTool_Element)

private:
  occ::handle<Standard_Transient> theval;
};
