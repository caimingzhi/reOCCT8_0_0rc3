

#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinition, Standard_Transient)

StepBasic_ProductDefinition::StepBasic_ProductDefinition() = default;

void StepBasic_ProductDefinition::Init(
  const occ::handle<TCollection_HAsciiString>&             aId,
  const occ::handle<TCollection_HAsciiString>&             aDescription,
  const occ::handle<StepBasic_ProductDefinitionFormation>& aFormation,
  const occ::handle<StepBasic_ProductDefinitionContext>&   aFrameOfReference)
{

  id               = aId;
  description      = aDescription;
  formation        = aFormation;
  frameOfReference = aFrameOfReference;
}

void StepBasic_ProductDefinition::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  id = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinition::Id() const
{
  return id;
}

void StepBasic_ProductDefinition::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinition::Description() const
{
  return description;
}

void StepBasic_ProductDefinition::SetFormation(
  const occ::handle<StepBasic_ProductDefinitionFormation>& aFormation)
{
  formation = aFormation;
}

occ::handle<StepBasic_ProductDefinitionFormation> StepBasic_ProductDefinition::Formation() const
{
  return formation;
}

void StepBasic_ProductDefinition::SetFrameOfReference(
  const occ::handle<StepBasic_ProductDefinitionContext>& aFrameOfReference)
{
  frameOfReference = aFrameOfReference;
}

occ::handle<StepBasic_ProductDefinitionContext> StepBasic_ProductDefinition::FrameOfReference()
  const
{
  return frameOfReference;
}
