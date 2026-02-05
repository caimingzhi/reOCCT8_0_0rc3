#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_DraughtingCallout;
class StepVisual_StyledItem;

class StepVisual_AnnotationPlaneElement : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a AnnotationPlaneElement select type
  Standard_EXPORT StepVisual_AnnotationPlaneElement();

  //! Recognizes a IdAttributeSelect Kind Entity that is :
  //! 1 -> DraughtingCallout
  //! 2 -> StyledItem
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a DraughtingCallout (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_DraughtingCallout> DraughtingCallout() const;

  //! returns Value as a StyledItem (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_StyledItem> StyledItem() const;
};
