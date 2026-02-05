#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepKinematics_SphericalPair;
class StepKinematics_SphericalPairWithPin;

//! Representation of STEP SELECT type SphericalPairSelect
class StepKinematics_SphericalPairSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepKinematics_SphericalPairSelect();

  //! Recognizes a kind of SphericalPairSelect select type
  //! -- 1 -> SphericalPair
  //! -- 2 -> SphericalPairWithPin
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as SphericalPair (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_SphericalPair> SphericalPair() const;

  //! Returns Value as SphericalPairWithPin (or Null if another type)
  Standard_EXPORT occ::handle<StepKinematics_SphericalPairWithPin> SphericalPairWithPin() const;
};
