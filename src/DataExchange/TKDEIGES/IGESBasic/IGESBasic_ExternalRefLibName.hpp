#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines ExternalRefLibName, Type <416> Form <4>
//! in package IGESBasic
//! Used when it is assumed that a copy of the subfigure
//! exists in native form in a library on the receiving
//! system
class IGESBasic_ExternalRefLibName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefLibName();

  //! This method is used to set the fields of the class
  //! ExternalRefLibName
  //! - aLibName  : Name of library in which ExtName resides
  //! - anExtName : External Reference Entity Symbolic Name
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aLibName,
                            const occ::handle<TCollection_HAsciiString>& anExtName);

  //! returns name of library in which External Reference Entity
  //! Symbolic Name resides
  Standard_EXPORT occ::handle<TCollection_HAsciiString> LibraryName() const;

  //! returns External Reference Entity Symbolic Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefLibName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theLibName;
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};
