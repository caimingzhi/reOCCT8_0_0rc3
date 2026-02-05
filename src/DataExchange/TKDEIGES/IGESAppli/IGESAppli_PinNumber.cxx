#include <IGESAppli_PinNumber.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_PinNumber, IGESData_IGESEntity)

IGESAppli_PinNumber::IGESAppli_PinNumber() = default;

void IGESAppli_PinNumber::Init(const int                                    nbPropVal,
                               const occ::handle<TCollection_HAsciiString>& aValue)
{
  thePinNumber        = aValue;
  theNbPropertyValues = nbPropVal;
  InitTypeAndForm(406, 8);
}

int IGESAppli_PinNumber::NbPropertyValues() const
{
  return theNbPropertyValues;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PinNumber::PinNumberVal() const
{
  return thePinNumber;
}
