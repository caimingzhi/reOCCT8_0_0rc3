#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_DimensionalExponents;

class StepBasic_NamedUnit : public Standard_Transient
{

public:
  //! Returns a NamedUnit
  Standard_EXPORT StepBasic_NamedUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_DimensionalExponents>& aDimensions);

  Standard_EXPORT virtual void SetDimensions(
    const occ::handle<StepBasic_DimensionalExponents>& aDimensions);

  Standard_EXPORT virtual occ::handle<StepBasic_DimensionalExponents> Dimensions() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_NamedUnit, Standard_Transient)

private:
  occ::handle<StepBasic_DimensionalExponents> dimensions;
};
