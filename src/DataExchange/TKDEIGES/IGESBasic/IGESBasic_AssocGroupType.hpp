#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines AssocGroupType, Type <406> Form <23>
//! in package IGESBasic
//! Used to assign an unambiguous identification to a Group
//! Associativity.
class IGESBasic_AssocGroupType : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_AssocGroupType();

  //! This method is used to set the fields of the class
  //! AssocGroupType
  //! - nbDataFields : number of parameter data fields = 2
  //! - aType        : type of attached associativity
  //! - aName        : identifier of associativity of type AType
  Standard_EXPORT void Init(const int                                    nbDataFields,
                            const int                                    aType,
                            const occ::handle<TCollection_HAsciiString>& aName);

  //! returns the number of parameter data fields, always = 2
  Standard_EXPORT int NbData() const;

  //! returns the type of attached associativity
  Standard_EXPORT int AssocType() const;

  //! returns identifier of instance of specified associativity
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_AssocGroupType, IGESData_IGESEntity)

private:
  int                                   theNbData;
  int                                   theType;
  occ::handle<TCollection_HAsciiString> theName;
};
