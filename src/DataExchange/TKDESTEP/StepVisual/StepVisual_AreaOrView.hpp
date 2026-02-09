#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PresentationArea;
class StepVisual_PresentationView;

class StepVisual_AreaOrView : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_AreaOrView();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_PresentationArea> PresentationArea() const;

  Standard_EXPORT occ::handle<StepVisual_PresentationView> PresentationView() const;
};
