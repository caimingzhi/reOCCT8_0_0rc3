#pragma once

#include <Standard.hpp>

#include <StepShape_DimensionalCharacteristic.hpp>
#include <Standard_Transient.hpp>
class StepShape_ShapeDimensionRepresentation;

class StepShape_DimensionalCharacteristicRepresentation : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_DimensionalCharacteristicRepresentation();

  Standard_EXPORT void Init(
    const StepShape_DimensionalCharacteristic&                 aDimension,
    const occ::handle<StepShape_ShapeDimensionRepresentation>& aRepresentation);

  Standard_EXPORT StepShape_DimensionalCharacteristic Dimension() const;

  Standard_EXPORT void SetDimension(const StepShape_DimensionalCharacteristic& Dimension);

  Standard_EXPORT occ::handle<StepShape_ShapeDimensionRepresentation> Representation() const;

  Standard_EXPORT void SetRepresentation(
    const occ::handle<StepShape_ShapeDimensionRepresentation>& Representation);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalCharacteristicRepresentation, Standard_Transient)

private:
  StepShape_DimensionalCharacteristic                 theDimension;
  occ::handle<StepShape_ShapeDimensionRepresentation> theRepresentation;
};
