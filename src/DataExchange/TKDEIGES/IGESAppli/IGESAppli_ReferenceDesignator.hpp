#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines ReferenceDesignator, Type <406> Form <7>
//! in package IGESAppli
//! Used to attach a text string containing the value of
//! a component reference designator to an entity being
//! used to represent a component.
class IGESAppli_ReferenceDesignator : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_ReferenceDesignator();

  //! This method is used to set the fields of the class
  //! ReferenceDesignator
  //! - nbPropVal : Number of property values = 1
  //! - aText     : Reference designator text
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aText);

  //! returns the number of property values
  //! is always 1
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the Reference designator text
  Standard_EXPORT occ::handle<TCollection_HAsciiString> RefDesignatorText() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_ReferenceDesignator, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theRefDesigText;
};
