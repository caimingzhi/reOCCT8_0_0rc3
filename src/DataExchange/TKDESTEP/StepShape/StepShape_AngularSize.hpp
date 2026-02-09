#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_AngleRelator.hpp>
#include <StepShape_DimensionalSize.hpp>
class StepRepr_ShapeAspect;
class TCollection_HAsciiString;

class StepShape_AngularSize : public StepShape_DimensionalSize
{

public:
  Standard_EXPORT StepShape_AngularSize();

  Standard_EXPORT void Init(const occ::handle<StepRepr_ShapeAspect>&     aDimensionalSize_AppliesTo,
                            const occ::handle<TCollection_HAsciiString>& aDimensionalSize_Name,
                            const StepShape_AngleRelator                 aAngleSelection);

  Standard_EXPORT StepShape_AngleRelator AngleSelection() const;

  Standard_EXPORT void SetAngleSelection(const StepShape_AngleRelator AngleSelection);

  DEFINE_STANDARD_RTTIEXT(StepShape_AngularSize, StepShape_DimensionalSize)

private:
  StepShape_AngleRelator theAngleSelection;
};
