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

class StepKinematics_SpatialRotation : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepKinematics_SpatialRotation();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepKinematics_RotationAboutDirection> RotationAboutDirection() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> YprRotation() const;
};
