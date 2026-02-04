#pragma once


#include <Standard.hpp>

#include <StepShape_DimensionalCharacteristic.hpp>
#include <Standard_Transient.hpp>
class StepShape_ShapeDimensionRepresentation;

//! Representation of STEP entity DimensionalCharacteristicRepresentation
class StepShape_DimensionalCharacteristicRepresentation : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_DimensionalCharacteristicRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const StepShape_DimensionalCharacteristic&                 aDimension,
    const occ::handle<StepShape_ShapeDimensionRepresentation>& aRepresentation);

  //! Returns field Dimension
  Standard_EXPORT StepShape_DimensionalCharacteristic Dimension() const;

  //! Set field Dimension
  Standard_EXPORT void SetDimension(const StepShape_DimensionalCharacteristic& Dimension);

  //! Returns field Representation
  Standard_EXPORT occ::handle<StepShape_ShapeDimensionRepresentation> Representation() const;

  //! Set field Representation
  Standard_EXPORT void SetRepresentation(
    const occ::handle<StepShape_ShapeDimensionRepresentation>& Representation);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalCharacteristicRepresentation, Standard_Transient)

private:
  StepShape_DimensionalCharacteristic                 theDimension;
  occ::handle<StepShape_ShapeDimensionRepresentation> theRepresentation;
};

