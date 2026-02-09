#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_DimensionalLocation;
class StepShape_DimensionalSize;

class StepShape_DimensionalCharacteristic : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_DimensionalCharacteristic();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_DimensionalLocation> DimensionalLocation() const;

  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;
};
