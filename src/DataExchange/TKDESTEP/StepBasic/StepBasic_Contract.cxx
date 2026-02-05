#include <StepBasic_Contract.hpp>
#include <StepBasic_ContractType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Contract, Standard_Transient)

//=================================================================================================

StepBasic_Contract::StepBasic_Contract() = default;

//=================================================================================================

void StepBasic_Contract::Init(const occ::handle<TCollection_HAsciiString>& aName,
                              const occ::handle<TCollection_HAsciiString>& aPurpose,
                              const occ::handle<StepBasic_ContractType>&   aKind)
{

  theName = aName;

  thePurpose = aPurpose;

  theKind = aKind;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Contract::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_Contract::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Contract::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepBasic_Contract::SetPurpose(const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  thePurpose = aPurpose;
}

//=================================================================================================

occ::handle<StepBasic_ContractType> StepBasic_Contract::Kind() const
{
  return theKind;
}

//=================================================================================================

void StepBasic_Contract::SetKind(const occ::handle<StepBasic_ContractType>& aKind)
{
  theKind = aKind;
}
