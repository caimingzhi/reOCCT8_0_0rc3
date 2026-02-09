

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationContextElement.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApplicationContextElement, Standard_Transient)

StepBasic_ApplicationContextElement::StepBasic_ApplicationContextElement() = default;

void StepBasic_ApplicationContextElement::Init(
  const occ::handle<TCollection_HAsciiString>&     aName,
  const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference)
{

  name             = aName;
  frameOfReference = aFrameOfReference;
}

void StepBasic_ApplicationContextElement::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApplicationContextElement::Name() const
{
  return name;
}

void StepBasic_ApplicationContextElement::SetFrameOfReference(
  const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference)
{
  frameOfReference = aFrameOfReference;
}

occ::handle<StepBasic_ApplicationContext> StepBasic_ApplicationContextElement::FrameOfReference()
  const
{
  return frameOfReference;
}
