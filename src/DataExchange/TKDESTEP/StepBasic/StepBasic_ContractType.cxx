#include <StepBasic_ContractType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ContractType, Standard_Transient)

//=================================================================================================

StepBasic_ContractType::StepBasic_ContractType() = default;

//=================================================================================================

void StepBasic_ContractType::Init(const occ::handle<TCollection_HAsciiString>& aDescription)
{

  theDescription = aDescription;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ContractType::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_ContractType::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}
