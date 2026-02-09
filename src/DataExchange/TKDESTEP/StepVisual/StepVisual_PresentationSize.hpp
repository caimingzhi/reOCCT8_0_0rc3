#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_PresentationSizeAssignmentSelect.hpp>
#include <Standard_Transient.hpp>
class StepVisual_PlanarBox;

class StepVisual_PresentationSize : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_PresentationSize();

  Standard_EXPORT void Init(const StepVisual_PresentationSizeAssignmentSelect& aUnit,
                            const occ::handle<StepVisual_PlanarBox>&           aSize);

  Standard_EXPORT void SetUnit(const StepVisual_PresentationSizeAssignmentSelect& aUnit);

  Standard_EXPORT StepVisual_PresentationSizeAssignmentSelect Unit() const;

  Standard_EXPORT void SetSize(const occ::handle<StepVisual_PlanarBox>& aSize);

  Standard_EXPORT occ::handle<StepVisual_PlanarBox> Size() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationSize, Standard_Transient)

private:
  StepVisual_PresentationSizeAssignmentSelect unit;
  occ::handle<StepVisual_PlanarBox>           size;
};
