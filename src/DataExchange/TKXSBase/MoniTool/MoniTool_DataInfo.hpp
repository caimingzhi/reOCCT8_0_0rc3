#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Type.hpp>
class Standard_Transient;

//! Gives information on an object
//! Used as template to instantiate Elem, etc
//! This class is for Transient
class MoniTool_DataInfo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the Type attached to an object
  //! Here, the Dynamic Type of a Transient. Null Type if unknown
  Standard_EXPORT static occ::handle<Standard_Type> Type(
    const occ::handle<Standard_Transient>& ent);

  //! Returns Type Name (string)
  //! Allows to name type of non-handled objects
  Standard_EXPORT static const char* TypeName(const occ::handle<Standard_Transient>& ent);
};
