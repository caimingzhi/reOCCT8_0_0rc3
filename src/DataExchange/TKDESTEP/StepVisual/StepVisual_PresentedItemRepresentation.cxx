

#include <StepVisual_PresentedItem.hpp>
#include <StepVisual_PresentedItemRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PresentedItemRepresentation, Standard_Transient)

StepVisual_PresentedItemRepresentation::StepVisual_PresentedItemRepresentation() = default;

void StepVisual_PresentedItemRepresentation::Init(
  const StepVisual_PresentationRepresentationSelect& aPresentation,
  const occ::handle<StepVisual_PresentedItem>&       aItem)
{
  thePresentation = aPresentation;
  theItem         = aItem;
}

void StepVisual_PresentedItemRepresentation::SetPresentation(
  const StepVisual_PresentationRepresentationSelect& aPresentation)
{
  thePresentation = aPresentation;
}

StepVisual_PresentationRepresentationSelect StepVisual_PresentedItemRepresentation::Presentation()
  const
{
  return thePresentation;
}

void StepVisual_PresentedItemRepresentation::SetItem(
  const occ::handle<StepVisual_PresentedItem>& aItem)
{
  theItem = aItem;
}

occ::handle<StepVisual_PresentedItem> StepVisual_PresentedItemRepresentation::Item() const
{
  return theItem;
}
