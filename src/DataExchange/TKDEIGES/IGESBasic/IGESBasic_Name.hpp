#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_NameEntity.hpp>
class TCollection_HAsciiString;

//! defines Name, Type <406> Form <15>
//! in package IGESBasic
//! Used to specify a user defined name
class IGESBasic_Name : public IGESData_NameEntity
{

public:
  Standard_EXPORT IGESBasic_Name();

  //! This method is used to set the fields of the class Name
  //! - nbPropVal  : Number of property values, always = 1
  //! - aName      : Stores the Name
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aName);

  //! returns the number of property values, which should be 1
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the user defined Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Value() const override;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Name, IGESData_NameEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theName;
};
