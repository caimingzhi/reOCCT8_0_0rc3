#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_ProductDefinitionReferenceWithLocalRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionReferenceWithLocalRepresentation,
                           StepBasic_ProductDefinition)

StepBasic_ProductDefinitionReferenceWithLocalRepresentation::
  StepBasic_ProductDefinitionReferenceWithLocalRepresentation() = default;

void StepBasic_ProductDefinitionReferenceWithLocalRepresentation::Init(
  const occ::handle<StepBasic_ExternalSource>&             theSource,
  const occ::handle<TCollection_HAsciiString>&             theId,
  const occ::handle<TCollection_HAsciiString>&             theDescription,
  const occ::handle<StepBasic_ProductDefinitionFormation>& theFormation,
  const occ::handle<StepBasic_ProductDefinitionContext>&   theFrameOfReference)
{
  StepBasic_ProductDefinition::Init(theId, theDescription, theFormation, theFrameOfReference);
  mySource = theSource;
}
