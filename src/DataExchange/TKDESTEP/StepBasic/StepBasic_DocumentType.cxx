

#include <StepBasic_DocumentType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentType, Standard_Transient)

StepBasic_DocumentType::StepBasic_DocumentType() = default;

void StepBasic_DocumentType::Init(const occ::handle<TCollection_HAsciiString>& apdt)
{
  thepdt = apdt;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentType::ProductDataType() const
{
  return thepdt;
}

void StepBasic_DocumentType::SetProductDataType(const occ::handle<TCollection_HAsciiString>& apdt)
{
  thepdt = apdt;
}
