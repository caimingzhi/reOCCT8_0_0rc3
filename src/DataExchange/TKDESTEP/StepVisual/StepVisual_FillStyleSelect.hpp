#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_FillAreaStyleColour;

class StepVisual_FillStyleSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a FillStyleSelect SelectType
  Standard_EXPORT StepVisual_FillStyleSelect();

  //! Recognizes a FillStyleSelect Kind Entity that is :
  //! 1 -> FillAreaStyleColour
  //! 2 -> ExternallyDefinedTileStyle
  //! 3 -> FillAreaStyleTiles
  //! 4 -> ExternallyDefinedHatchStyle
  //! 5 -> FillAreaStyleHatching
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a FillAreaStyleColour (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_FillAreaStyleColour> FillAreaStyleColour() const;
};
