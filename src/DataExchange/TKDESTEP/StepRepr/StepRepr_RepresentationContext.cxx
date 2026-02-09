

#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationContext, Standard_Transient)

StepRepr_RepresentationContext::StepRepr_RepresentationContext() = default;

void StepRepr_RepresentationContext::Init(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
  const occ::handle<TCollection_HAsciiString>& aContextType)
{

  contextIdentifier = aContextIdentifier;
  contextType       = aContextType;
}

void StepRepr_RepresentationContext::SetContextIdentifier(
  const occ::handle<TCollection_HAsciiString>& aContextIdentifier)
{
  contextIdentifier = aContextIdentifier;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationContext::ContextIdentifier() const
{
  return contextIdentifier;
}

void StepRepr_RepresentationContext::SetContextType(
  const occ::handle<TCollection_HAsciiString>& aContextType)
{
  contextType = aContextType;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationContext::ContextType() const
{
  return contextType;
}
