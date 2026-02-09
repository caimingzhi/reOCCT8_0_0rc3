#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepKinematics_SphericalPair;
class StepKinematics_SphericalPairWithPin;

class StepKinematics_SphericalPairSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepKinematics_SphericalPairSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepKinematics_SphericalPair> SphericalPair() const;

  Standard_EXPORT occ::handle<StepKinematics_SphericalPairWithPin> SphericalPairWithPin() const;
};
