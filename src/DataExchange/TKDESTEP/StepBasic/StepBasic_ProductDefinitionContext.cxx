

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionContext, StepBasic_ApplicationContextElement)

StepBasic_ProductDefinitionContext::StepBasic_ProductDefinitionContext() = default;

void StepBasic_ProductDefinitionContext::Init(
  const occ::handle<TCollection_HAsciiString>&     aName,
  const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference,
  const occ::handle<TCollection_HAsciiString>&     aLifeCycleStage)
{

  lifeCycleStage = aLifeCycleStage;

  StepBasic_ApplicationContextElement::Init(aName, aFrameOfReference);
}

void StepBasic_ProductDefinitionContext::SetLifeCycleStage(
  const occ::handle<TCollection_HAsciiString>& aLifeCycleStage)
{
  lifeCycleStage = aLifeCycleStage;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionContext::LifeCycleStage() const
{
  return lifeCycleStage;
}
