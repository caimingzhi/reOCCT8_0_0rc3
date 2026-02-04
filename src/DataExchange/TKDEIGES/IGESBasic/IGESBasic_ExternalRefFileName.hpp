#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines ExternalRefFileName, Type <416> Form <0-2>
//! in package IGESBasic
//! Used when single definition from the reference file is
//! required or for external logical references where an
//! entity in one file relates to an entity in another file
class IGESBasic_ExternalRefFileName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefFileName();

  //! This method is used to set the fields of the class
  //! ExternalRefFileName
  //! - aFileIdent : External Reference File Identifier
  //! - anExtName  : External Reference Entity Symbolic Name
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aFileIdent,
                            const occ::handle<TCollection_HAsciiString>& anExtName);

  //! Changes FormNumber to be 2 if <mode> is True (For Entity)
  //! or 0 if <mode> is False (For Definition)
  Standard_EXPORT void SetForEntity(const bool mode);

  //! returns External Reference File Identifier
  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileId() const;

  //! returns External Reference Entity Symbolic Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefFileName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefFileIdentifier;
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};

