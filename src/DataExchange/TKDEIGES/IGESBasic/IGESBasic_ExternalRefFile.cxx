#include <IGESBasic_ExternalRefFile.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalRefFile, IGESData_IGESEntity)

IGESBasic_ExternalRefFile::IGESBasic_ExternalRefFile() = default;

void IGESBasic_ExternalRefFile::Init(const occ::handle<TCollection_HAsciiString>& aFileIdent)
{
  theExtRefFileIdentifier = aFileIdent;
  InitTypeAndForm(416, 1);
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefFile::FileId() const
{
  return theExtRefFileIdentifier;
}
