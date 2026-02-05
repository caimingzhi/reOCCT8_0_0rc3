#include <IGESBasic_AssocGroupType.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_AssocGroupType, IGESData_IGESEntity)

IGESBasic_AssocGroupType::IGESBasic_AssocGroupType() = default;

void IGESBasic_AssocGroupType::Init(const int                                    nbDataFields,
                                    const int                                    aType,
                                    const occ::handle<TCollection_HAsciiString>& aName)
{
  theNbData = nbDataFields;
  theType   = aType;
  theName   = aName;
  InitTypeAndForm(406, 23);
}

int IGESBasic_AssocGroupType::NbData() const
{
  return theNbData;
}

int IGESBasic_AssocGroupType::AssocType() const
{
  return theType;
}

occ::handle<TCollection_HAsciiString> IGESBasic_AssocGroupType::Name() const
{
  return theName;
}
