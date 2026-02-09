

#include <StepKinematics_RotationAboutDirection.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_RotationAboutDirection,
                           StepGeom_GeometricRepresentationItem)

StepKinematics_RotationAboutDirection::StepKinematics_RotationAboutDirection() = default;

void StepKinematics_RotationAboutDirection::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<StepGeom_Direction>&       theDirectionOfAxis,
  const double                                 theRotationAngle)
{
  StepGeom_GeometricRepresentationItem::Init(theRepresentationItem_Name);

  myDirectionOfAxis = theDirectionOfAxis;

  myRotationAngle = theRotationAngle;
}

occ::handle<StepGeom_Direction> StepKinematics_RotationAboutDirection::DirectionOfAxis() const
{
  return myDirectionOfAxis;
}

void StepKinematics_RotationAboutDirection::SetDirectionOfAxis(
  const occ::handle<StepGeom_Direction>& theDirectionOfAxis)
{
  myDirectionOfAxis = theDirectionOfAxis;
}

double StepKinematics_RotationAboutDirection::RotationAngle() const
{
  return myRotationAngle;
}

void StepKinematics_RotationAboutDirection::SetRotationAngle(const double theRotationAngle)
{
  myRotationAngle = theRotationAngle;
}
