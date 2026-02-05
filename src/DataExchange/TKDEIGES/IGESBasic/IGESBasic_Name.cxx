#include <IGESBasic_Name.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_Name, IGESData_NameEntity)

IGESBasic_Name::IGESBasic_Name() = default;

void IGESBasic_Name::Init(const int nbPropVal, const occ::handle<TCollection_HAsciiString>& aName)
{
  theName             = aName;
  theNbPropertyValues = nbPropVal;
  InitTypeAndForm(406, 15);
}

int IGESBasic_Name::NbPropertyValues() const
{
  return theNbPropertyValues;
}

occ::handle<TCollection_HAsciiString> IGESBasic_Name::Value() const
{
  return theName;
}
