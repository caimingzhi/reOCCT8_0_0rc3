#pragma once

#include <Standard.hpp>

#include <StepShape_ToleranceMethodDefinition.hpp>
#include <StepShape_DimensionalCharacteristic.hpp>
#include <Standard_Transient.hpp>

class StepShape_PlusMinusTolerance : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_PlusMinusTolerance();

  Standard_EXPORT void Init(const StepShape_ToleranceMethodDefinition& range,
                            const StepShape_DimensionalCharacteristic& toleranced_dimension);

  Standard_EXPORT StepShape_ToleranceMethodDefinition Range() const;

  Standard_EXPORT void SetRange(const StepShape_ToleranceMethodDefinition& range);

  Standard_EXPORT StepShape_DimensionalCharacteristic TolerancedDimension() const;

  Standard_EXPORT void SetTolerancedDimension(
    const StepShape_DimensionalCharacteristic& toleranced_dimension);

  DEFINE_STANDARD_RTTIEXT(StepShape_PlusMinusTolerance, Standard_Transient)

private:
  StepShape_ToleranceMethodDefinition theRange;
  StepShape_DimensionalCharacteristic theTolerancedDimension;
};
