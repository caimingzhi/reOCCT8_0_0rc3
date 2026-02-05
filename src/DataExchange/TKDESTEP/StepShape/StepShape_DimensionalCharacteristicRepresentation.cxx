#include <StepShape_DimensionalCharacteristicRepresentation.hpp>
#include <StepShape_ShapeDimensionRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_DimensionalCharacteristicRepresentation, Standard_Transient)

//=================================================================================================

StepShape_DimensionalCharacteristicRepresentation::
  StepShape_DimensionalCharacteristicRepresentation() = default;

//=================================================================================================

void StepShape_DimensionalCharacteristicRepresentation::Init(
  const StepShape_DimensionalCharacteristic&                 aDimension,
  const occ::handle<StepShape_ShapeDimensionRepresentation>& aRepresentation)
{

  theDimension = aDimension;

  theRepresentation = aRepresentation;
}

//=================================================================================================

StepShape_DimensionalCharacteristic StepShape_DimensionalCharacteristicRepresentation::Dimension()
  const
{
  return theDimension;
}

//=================================================================================================

void StepShape_DimensionalCharacteristicRepresentation::SetDimension(
  const StepShape_DimensionalCharacteristic& aDimension)
{
  theDimension = aDimension;
}

//=================================================================================================

occ::handle<StepShape_ShapeDimensionRepresentation>
  StepShape_DimensionalCharacteristicRepresentation::Representation() const
{
  return theRepresentation;
}

//=================================================================================================

void StepShape_DimensionalCharacteristicRepresentation::SetRepresentation(
  const occ::handle<StepShape_ShapeDimensionRepresentation>& aRepresentation)
{
  theRepresentation = aRepresentation;
}
