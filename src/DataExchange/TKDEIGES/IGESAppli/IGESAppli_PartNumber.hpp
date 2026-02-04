#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines PartNumber, Type <406> Form <9>
//! in package IGESAppli
//! Attaches a set of text strings that define the common
//! part numbers to an entity being used to represent a
//! physical component
class IGESAppli_PartNumber : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PartNumber();

  //! This method is used to set the fields of the class
  //! PartNumber
  //! - nbPropVal : number of property values, always = 4
  //! - aGenName  : Generic part number or name
  //! - aMilName  : Military Standard (MIL-STD) part number
  //! - aVendName : Vendor part number or name
  //! - anIntName : Internal part number
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aGenName,
                            const occ::handle<TCollection_HAsciiString>& aMilName,
                            const occ::handle<TCollection_HAsciiString>& aVendName,
                            const occ::handle<TCollection_HAsciiString>& anIntName);

  //! returns number of property values, always = 4
  Standard_EXPORT int NbPropertyValues() const;

  //! returns Generic part number or name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> GenericNumber() const;

  //! returns Military Standard (MIL-STD) part number
  Standard_EXPORT occ::handle<TCollection_HAsciiString> MilitaryNumber() const;

  //! returns Vendor part number or name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> VendorNumber() const;

  //! returns Internal part number
  Standard_EXPORT occ::handle<TCollection_HAsciiString> InternalNumber() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PartNumber, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theGenericNumber;
  occ::handle<TCollection_HAsciiString> theMilitaryNumber;
  occ::handle<TCollection_HAsciiString> theVendorNumber;
  occ::handle<TCollection_HAsciiString> theInternalNumber;
};

