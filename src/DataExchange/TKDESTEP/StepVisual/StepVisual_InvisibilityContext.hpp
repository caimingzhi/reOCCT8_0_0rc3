#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_DraughtingModel;
class StepVisual_PresentationRepresentation;
class StepVisual_PresentationSet;

class StepVisual_InvisibilityContext : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_InvisibilityContext();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_PresentationRepresentation> PresentationRepresentation()
    const;

  Standard_EXPORT occ::handle<StepVisual_PresentationSet> PresentationSet() const;

  Standard_EXPORT occ::handle<StepVisual_DraughtingModel> DraughtingModel() const;
};
