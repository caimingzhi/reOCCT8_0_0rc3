#include <IGESBasic_ExternalRefLibName.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalRefLibName, IGESData_IGESEntity)

IGESBasic_ExternalRefLibName::IGESBasic_ExternalRefLibName() = default;

void IGESBasic_ExternalRefLibName::Init(const occ::handle<TCollection_HAsciiString>& aLibName,
                                        const occ::handle<TCollection_HAsciiString>& anExtName)
{
  theLibName              = aLibName;
  theExtRefEntitySymbName = anExtName;
  InitTypeAndForm(416, 4);
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefLibName::LibraryName() const
{
  return theLibName;
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefLibName::ReferenceName() const
{
  return theExtRefEntitySymbName;
}
