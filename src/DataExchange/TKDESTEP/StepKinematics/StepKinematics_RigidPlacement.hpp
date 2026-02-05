#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepGeom_Axis2Placement3d;
class StepGeom_SuParameters;

//! Representation of STEP SELECT type RigidPlacement
class StepKinematics_RigidPlacement : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepKinematics_RigidPlacement();

  //! Recognizes a kind of RigidPlacement select type
  //! -- 1 -> Axis2Placement3d
  //! -- 2 -> SuParameters
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Axis2Placement3d (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> Axis2Placement3d() const;

  //! Returns Value as SuParameters (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_SuParameters> SuParameters() const;
};
