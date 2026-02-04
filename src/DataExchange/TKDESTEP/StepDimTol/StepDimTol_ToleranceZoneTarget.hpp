#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepDimTol_GeometricTolerance;
class StepDimTol_GeneralDatumReference;
class StepShape_DimensionalLocation;
class StepShape_DimensionalSize;

class StepDimTol_ToleranceZoneTarget : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ToleranceZoneTarget select type
  Standard_EXPORT StepDimTol_ToleranceZoneTarget();

  //! Recognizes a ToleranceZoneTarget Kind Entity that is :
  //! 1 -> DimensionalLocation
  //! 2 -> DimensionalSize
  //! 3 -> GeometricTolerance
  //! 4 -> GeneralDatumReference
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a DimensionalLocation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalLocation> DimensionalLocation() const;

  //! returns Value as a DimensionalSize (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  //! returns Value as a GeometricTolerance (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  //! returns Value as a GeneralDatumReference (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_GeneralDatumReference> GeneralDatumReference() const;
};
