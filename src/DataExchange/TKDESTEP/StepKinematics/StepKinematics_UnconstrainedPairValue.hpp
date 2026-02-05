#pragma once

#include <Standard.hpp>
#include <StepKinematics_PairValue.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

//! Representation of STEP entity UnconstrainedPairValue
class StepKinematics_UnconstrainedPairValue : public StepKinematics_PairValue
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_UnconstrainedPairValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theRepresentationItem_Name,
    const occ::handle<StepKinematics_KinematicPair>& thePairValue_AppliesToPair,
    const occ::handle<StepGeom_Axis2Placement3d>&    theActualPlacement);

  //! Returns field ActualPlacement
  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> ActualPlacement() const;
  //! Sets field ActualPlacement
  Standard_EXPORT void SetActualPlacement(
    const occ::handle<StepGeom_Axis2Placement3d>& theActualPlacement);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_UnconstrainedPairValue, StepKinematics_PairValue)

private:
  occ::handle<StepGeom_Axis2Placement3d> myActualPlacement;
};
