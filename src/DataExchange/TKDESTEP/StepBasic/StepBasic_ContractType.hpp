#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity ContractType
class StepBasic_ContractType : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ContractType();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aDescription);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ContractType, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theDescription;
};
