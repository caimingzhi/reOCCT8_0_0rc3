#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PresentationRepresentation;
class StepRepr_RepresentationItem;

class StepVisual_LayeredItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a LayeredItem SelectType
  Standard_EXPORT StepVisual_LayeredItem();

  //! Recognizes a LayeredItem Kind Entity that is :
  //! 1 -> PresentationRepresentation
  //! 2 -> RepresentationItem
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a PresentationRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationRepresentation> PresentationRepresentation()
    const;

  //! returns Value as a RepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;
};

