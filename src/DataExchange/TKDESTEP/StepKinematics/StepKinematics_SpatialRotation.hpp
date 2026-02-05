#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Standard_Transient;
class StepKinematics_RotationAboutDirection;

//! Representation of STEP SELECT type SpatialRotation
class StepKinematics_SpatialRotation : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepKinematics_SpatialRotation();

  //! Recognizes a kind of SpatialRotation select type
  //! -- 1 -> RotationAboutDirection
  //! -- 2 -> YprRotation
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as RotationAboutDirection (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_RotationAboutDirection> RotationAboutDirection() const;

  //! Returns Value as YprRotation (or Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> YprRotation() const;
};
