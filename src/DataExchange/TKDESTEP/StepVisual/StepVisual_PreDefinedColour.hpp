#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_Colour.hpp>
class StepVisual_PreDefinedItem;

class StepVisual_PreDefinedColour : public StepVisual_Colour
{

public:
  //! Returns a PreDefinedColour
  Standard_EXPORT StepVisual_PreDefinedColour();

  //! set a pre_defined_item part
  Standard_EXPORT void SetPreDefinedItem(const occ::handle<StepVisual_PreDefinedItem>& item);

  //! return a pre_defined_item part
  Standard_EXPORT const occ::handle<StepVisual_PreDefinedItem>& GetPreDefinedItem() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PreDefinedColour, StepVisual_Colour)

private:
  occ::handle<StepVisual_PreDefinedItem> myItem;
};
