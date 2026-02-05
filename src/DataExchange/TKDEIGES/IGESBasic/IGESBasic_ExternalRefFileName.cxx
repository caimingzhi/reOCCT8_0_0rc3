#include <IGESBasic_ExternalRefFileName.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalRefFileName, IGESData_IGESEntity)

IGESBasic_ExternalRefFileName::IGESBasic_ExternalRefFileName() = default;

void IGESBasic_ExternalRefFileName::Init(const occ::handle<TCollection_HAsciiString>& aFileIdent,
                                         const occ::handle<TCollection_HAsciiString>& anExtName)
{
  theExtRefFileIdentifier = aFileIdent;
  theExtRefEntitySymbName = anExtName;
  InitTypeAndForm(416, FormNumber());
  //  FormNumber 0-2 : meaning not clear. Could be 0:Definition  2:Entity
}

void IGESBasic_ExternalRefFileName::SetForEntity(const bool F)
{
  InitTypeAndForm(416, (F ? 2 : 0));
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefFileName::FileId() const
{
  return theExtRefFileIdentifier;
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefFileName::ReferenceName() const
{
  return theExtRefEntitySymbName;
}
