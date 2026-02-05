#include <Standard_Transient.hpp>
#include <StepFEA_AlignedCurve3dElementCoordinateSystem.hpp>
#include <StepFEA_CurveElementEndCoordinateSystem.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateSystem.hpp>

//=================================================================================================

StepFEA_CurveElementEndCoordinateSystem::StepFEA_CurveElementEndCoordinateSystem() = default;

//=================================================================================================

int StepFEA_CurveElementEndCoordinateSystem::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepFEA_FeaAxis2Placement3d)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepFEA_AlignedCurve3dElementCoordinateSystem)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepFEA_ParametricCurve3dElementCoordinateSystem)))
    return 3;
  return 0;
}

//=================================================================================================

occ::handle<StepFEA_FeaAxis2Placement3d> StepFEA_CurveElementEndCoordinateSystem::
  FeaAxis2Placement3d() const
{
  return occ::down_cast<StepFEA_FeaAxis2Placement3d>(Value());
}

//=================================================================================================

occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem> StepFEA_CurveElementEndCoordinateSystem::
  AlignedCurve3dElementCoordinateSystem() const
{
  return occ::down_cast<StepFEA_AlignedCurve3dElementCoordinateSystem>(Value());
}

//=================================================================================================

occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>
  StepFEA_CurveElementEndCoordinateSystem::ParametricCurve3dElementCoordinateSystem() const
{
  return occ::down_cast<StepFEA_ParametricCurve3dElementCoordinateSystem>(Value());
}
