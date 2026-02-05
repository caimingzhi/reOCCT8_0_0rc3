#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines PinNumber, Type <406> Form <8>
//! in package IGESAppli
//! Used to attach a text string representing a component
//! pin number to an entity being used to represent an
//! electrical component's pin
class IGESAppli_PinNumber : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PinNumber();

  //! This method is used to set the fields of the class
  //! PinNumber
  //! - nbPropVal : Number of property values (always = 1)
  //! - aValue    : Pin Number value
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aValue);

  //! returns the number of property values
  //! is always 1
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the pin number value
  Standard_EXPORT occ::handle<TCollection_HAsciiString> PinNumberVal() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PinNumber, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> thePinNumber;
};
