#include <Standard_Transient.hpp>
#include <StepShape_DimensionalCharacteristic.hpp>
#include <StepShape_DimensionalLocation.hpp>
#include <StepShape_DimensionalSize.hpp>

//=================================================================================================

StepShape_DimensionalCharacteristic::StepShape_DimensionalCharacteristic() = default;

//=================================================================================================

int StepShape_DimensionalCharacteristic::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalLocation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalSize)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepShape_DimensionalLocation> StepShape_DimensionalCharacteristic::
  DimensionalLocation() const
{
  return occ::down_cast<StepShape_DimensionalLocation>(Value());
}

//=================================================================================================

occ::handle<StepShape_DimensionalSize> StepShape_DimensionalCharacteristic::DimensionalSize() const
{
  return occ::down_cast<StepShape_DimensionalSize>(Value());
}
