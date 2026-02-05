#include <IGESBasic_ExternalRefName.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalRefName, IGESData_IGESEntity)

IGESBasic_ExternalRefName::IGESBasic_ExternalRefName() = default;

void IGESBasic_ExternalRefName::Init(const occ::handle<TCollection_HAsciiString>& anExtName)
{
  theExtRefEntitySymbName = anExtName;
  InitTypeAndForm(416, 3);
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefName::ReferenceName() const
{
  return theExtRefEntitySymbName;
}
