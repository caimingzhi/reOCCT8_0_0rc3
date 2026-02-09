

#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationLayerUsage.hpp>
#include <StepVisual_PresentationRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentationLayerUsage, Standard_Transient)

StepVisual_PresentationLayerUsage::StepVisual_PresentationLayerUsage() = default;

void StepVisual_PresentationLayerUsage::Init(
  const occ::handle<StepVisual_PresentationLayerAssignment>& aAssignment,
  const occ::handle<StepVisual_PresentationRepresentation>&  aPresentation)
{
  theAssignment   = aAssignment;
  thePresentation = aPresentation;
}

void StepVisual_PresentationLayerUsage::SetAssignment(
  const occ::handle<StepVisual_PresentationLayerAssignment>& aAssignment)
{
  theAssignment = aAssignment;
}

occ::handle<StepVisual_PresentationLayerAssignment> StepVisual_PresentationLayerUsage::Assignment()
  const
{
  return theAssignment;
}

void StepVisual_PresentationLayerUsage::SetPresentation(
  const occ::handle<StepVisual_PresentationRepresentation>& aPresentation)
{
  thePresentation = aPresentation;
}

occ::handle<StepVisual_PresentationRepresentation> StepVisual_PresentationLayerUsage::Presentation()
  const
{
  return thePresentation;
}
