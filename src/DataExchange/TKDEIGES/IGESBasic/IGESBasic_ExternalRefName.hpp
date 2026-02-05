#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines ExternalRefName, Type <416> Form <3>
//! in package IGESBasic
//! Used when it is assumed that a copy of the subfigure
//! exists in native form on the receiving system
class IGESBasic_ExternalRefName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefName();

  //! This method is used to set the fields of the class
  //! ExternalRefName
  //! - anExtName : External Reference Entity Symbolic Name
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& anExtName);

  //! returns External Reference Entity Symbolic Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};
