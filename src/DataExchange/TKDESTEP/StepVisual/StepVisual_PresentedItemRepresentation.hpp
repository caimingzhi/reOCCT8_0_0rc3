#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationRepresentationSelect.hpp>
#include <Standard_Transient.hpp>
class StepVisual_PresentedItem;

//! Added from StepVisual Rev2 to Rev4
class StepVisual_PresentedItemRepresentation : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_PresentedItemRepresentation();

  Standard_EXPORT void Init(const StepVisual_PresentationRepresentationSelect& aPresentation,
                            const occ::handle<StepVisual_PresentedItem>&       aItem);

  Standard_EXPORT void SetPresentation(
    const StepVisual_PresentationRepresentationSelect& aPresentation);

  Standard_EXPORT StepVisual_PresentationRepresentationSelect Presentation() const;

  Standard_EXPORT void SetItem(const occ::handle<StepVisual_PresentedItem>& aItem);

  Standard_EXPORT occ::handle<StepVisual_PresentedItem> Item() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentedItemRepresentation, Standard_Transient)

private:
  StepVisual_PresentationRepresentationSelect thePresentation;
  occ::handle<StepVisual_PresentedItem>       theItem;
};
