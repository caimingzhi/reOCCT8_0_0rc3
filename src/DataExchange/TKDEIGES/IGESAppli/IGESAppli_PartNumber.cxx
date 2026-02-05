#include <IGESAppli_PartNumber.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_PartNumber, IGESData_IGESEntity)

IGESAppli_PartNumber::IGESAppli_PartNumber() = default;

void IGESAppli_PartNumber::Init(const int                                    nbPropVal,
                                const occ::handle<TCollection_HAsciiString>& aGenName,
                                const occ::handle<TCollection_HAsciiString>& aMilName,
                                const occ::handle<TCollection_HAsciiString>& aVendName,
                                const occ::handle<TCollection_HAsciiString>& anIntName)
{
  theNbPropertyValues = nbPropVal;
  theGenericNumber    = aGenName;
  theMilitaryNumber   = aMilName;
  theVendorNumber     = aVendName;
  theInternalNumber   = anIntName;
  InitTypeAndForm(406, 9);
}

int IGESAppli_PartNumber::NbPropertyValues() const
{
  return theNbPropertyValues;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PartNumber::GenericNumber() const
{
  return theGenericNumber;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PartNumber::MilitaryNumber() const
{
  return theMilitaryNumber;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PartNumber::VendorNumber() const
{
  return theVendorNumber;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PartNumber::InternalNumber() const
{
  return theInternalNumber;
}
