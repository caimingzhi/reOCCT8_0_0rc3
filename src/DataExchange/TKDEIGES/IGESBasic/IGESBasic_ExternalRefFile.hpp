#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_ExternalRefFile : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefFile();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aFileIdent);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileId() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefFile, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefFileIdentifier;
};
