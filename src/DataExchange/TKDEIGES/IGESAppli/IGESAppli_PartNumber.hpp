#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_PartNumber : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PartNumber();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aGenName,
                            const occ::handle<TCollection_HAsciiString>& aMilName,
                            const occ::handle<TCollection_HAsciiString>& aVendName,
                            const occ::handle<TCollection_HAsciiString>& anIntName);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GenericNumber() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> MilitaryNumber() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> VendorNumber() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> InternalNumber() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PartNumber, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theGenericNumber;
  occ::handle<TCollection_HAsciiString> theMilitaryNumber;
  occ::handle<TCollection_HAsciiString> theVendorNumber;
  occ::handle<TCollection_HAsciiString> theInternalNumber;
};
