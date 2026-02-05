#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_DimensionalLocation;
class StepShape_DimensionalSize;

//! Representation of STEP SELECT type DimensionalCharacteristic
class StepShape_DimensionalCharacteristic : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepShape_DimensionalCharacteristic();

  //! Recognizes a kind of DimensionalCharacteristic select type
  //! 1 -> DimensionalLocation from StepShape
  //! 2 -> DimensionalSize from StepShape
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as DimensionalLocation (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalLocation> DimensionalLocation() const;

  //! Returns Value as DimensionalSize (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;
};
