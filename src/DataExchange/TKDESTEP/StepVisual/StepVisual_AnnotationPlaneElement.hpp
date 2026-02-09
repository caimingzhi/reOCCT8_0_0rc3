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

  Standard_EXPORT StepVisual_AnnotationPlaneElement();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_DraughtingCallout> DraughtingCallout() const;

  Standard_EXPORT occ::handle<StepVisual_StyledItem> StyledItem() const;
};
