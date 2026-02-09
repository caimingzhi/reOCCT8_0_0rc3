#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_ExternalRefFileName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefFileName();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aFileIdent,
                            const occ::handle<TCollection_HAsciiString>& anExtName);

  Standard_EXPORT void SetForEntity(const bool mode);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileId() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefFileName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefFileIdentifier;
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};
