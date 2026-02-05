#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! a NameEntity is a kind of IGESEntity which can provide a Name
//! under alphanumeric (String) form, from Properties list
//! an effective Name entity must inherit it
class IGESData_NameEntity : public IGESData_IGESEntity
{

public:
  //! Retyrns the alphanumeric value of the Name, to be defined
  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> Value() const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_NameEntity, IGESData_IGESEntity)
};
