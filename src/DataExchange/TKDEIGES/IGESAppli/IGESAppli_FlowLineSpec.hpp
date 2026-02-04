#pragma once


#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

//! defines FlowLineSpec, Type <406> Form <14>
//! in package IGESAppli
//! Attaches one or more text strings to entities being
//! used to represent a flow line
class IGESAppli_FlowLineSpec : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_FlowLineSpec();

  //! This method is used to set the fields of the class
  //! FlowLineSpec
  //! - allProperties : primary flow line specification and modifiers
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allProperties);

  //! returns the number of property values
  Standard_EXPORT int NbPropertyValues() const;

  //! returns primary flow line specification name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> FlowLineName() const;

  //! returns specified modifier element
  //! raises exception if Index <= 1 or Index > NbPropertyValues
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Modifier(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_FlowLineSpec, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNameAndModifiers;
};

