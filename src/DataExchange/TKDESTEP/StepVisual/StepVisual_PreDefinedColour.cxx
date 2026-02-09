

#include <Standard_Type.hpp>
#include <StepVisual_PreDefinedColour.hpp>
#include <StepVisual_PreDefinedItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PreDefinedColour, StepVisual_Colour)

StepVisual_PreDefinedColour::StepVisual_PreDefinedColour()
{
  myItem = new StepVisual_PreDefinedItem;
}

void StepVisual_PreDefinedColour::SetPreDefinedItem(
  const occ::handle<StepVisual_PreDefinedItem>& item)
{
  myItem = item;
}

const occ::handle<StepVisual_PreDefinedItem>& StepVisual_PreDefinedColour::GetPreDefinedItem() const
{
  return myItem;
}
