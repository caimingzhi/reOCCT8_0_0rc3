#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaAxis2Placement3d, StepGeom_Axis2Placement3d)

StepFEA_FeaAxis2Placement3d::StepFEA_FeaAxis2Placement3d() = default;

void StepFEA_FeaAxis2Placement3d::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<StepGeom_CartesianPoint>&  aPlacement_Location,
  const bool                                   hasAxis2Placement3d_Axis,
  const occ::handle<StepGeom_Direction>&       aAxis2Placement3d_Axis,
  const bool                                   hasAxis2Placement3d_RefDirection,
  const occ::handle<StepGeom_Direction>&       aAxis2Placement3d_RefDirection,
  const StepFEA_CoordinateSystemType           aSystemType,
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  StepGeom_Axis2Placement3d::Init(aRepresentationItem_Name,
                                  aPlacement_Location,
                                  hasAxis2Placement3d_Axis,
                                  aAxis2Placement3d_Axis,
                                  hasAxis2Placement3d_RefDirection,
                                  aAxis2Placement3d_RefDirection);

  theSystemType = aSystemType;

  theDescription = aDescription;
}

StepFEA_CoordinateSystemType StepFEA_FeaAxis2Placement3d::SystemType() const
{
  return theSystemType;
}

void StepFEA_FeaAxis2Placement3d::SetSystemType(const StepFEA_CoordinateSystemType aSystemType)
{
  theSystemType = aSystemType;
}

occ::handle<TCollection_HAsciiString> StepFEA_FeaAxis2Placement3d::Description() const
{
  return theDescription;
}

void StepFEA_FeaAxis2Placement3d::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}
