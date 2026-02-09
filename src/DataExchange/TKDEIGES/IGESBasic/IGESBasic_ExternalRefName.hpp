#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_ExternalRefName : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefName();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& anExtName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceName() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefName, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString> theExtRefEntitySymbName;
};
