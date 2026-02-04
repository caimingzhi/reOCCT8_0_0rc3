#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_StyledItem;
class StepVisual_PresentationLayerAssignment;
class StepVisual_PresentationRepresentation;

class StepVisual_InvisibleItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a InvisibleItem SelectType
  Standard_EXPORT StepVisual_InvisibleItem();

  //! Recognizes a InvisibleItem Kind Entity that is :
  //! 1 -> StyledItem
  //! 2 -> PresentationLayerAssignment
  //! 3 -> PresentationRepresentation
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a StyledItem (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_StyledItem> StyledItem() const;

  //! returns Value as a PresentationLayerAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationLayerAssignment> PresentationLayerAssignment()
    const;

  //! returns Value as a PresentationRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationRepresentation> PresentationRepresentation()
    const;
};

