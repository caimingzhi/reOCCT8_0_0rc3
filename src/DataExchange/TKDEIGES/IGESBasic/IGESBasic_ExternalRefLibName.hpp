#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_ExternalRefLibName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefLibName();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aLibName,
                            const occ::handle<TCollection_HAsciiString>& anExtName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LibraryName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefLibName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theLibName;
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};
