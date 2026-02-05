#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ContractType;

//! Representation of STEP entity Contract
class StepBasic_Contract : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_Contract();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aPurpose,
                            const occ::handle<StepBasic_ContractType>&   aKind);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Purpose
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  //! Set field Purpose
  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  //! Returns field Kind
  Standard_EXPORT occ::handle<StepBasic_ContractType> Kind() const;

  //! Set field Kind
  Standard_EXPORT void SetKind(const occ::handle<StepBasic_ContractType>& Kind);

  DEFINE_STANDARD_RTTIEXT(StepBasic_Contract, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> thePurpose;
  occ::handle<StepBasic_ContractType>   theKind;
};
