#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines ExternalRefFile, Type <416> Form <1>
//! in package IGESBasic
//! Used when entire reference file is to be instanced
class IGESBasic_ExternalRefFile : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefFile();

  //! This method is used to set the field of the class
  //! ExternalRefFile
  //! - aFileIdent : External Reference File Identifier
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aFileIdent);

  //! returns External Reference File Identifier
  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileId() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefFile, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefFileIdentifier;
};
