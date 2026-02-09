#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepGeom_Direction.hpp>

class StepKinematics_RotationAboutDirection : public StepGeom_GeometricRepresentationItem
{
public:
  Standard_EXPORT StepKinematics_RotationAboutDirection();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepGeom_Direction>&       theDirectionOfAxis,
                            const double                                 theRotationAngle);

  Standard_EXPORT occ::handle<StepGeom_Direction> DirectionOfAxis() const;

  Standard_EXPORT void SetDirectionOfAxis(
    const occ::handle<StepGeom_Direction>& theDirectionOfAxis);

  Standard_EXPORT double RotationAngle() const;

  Standard_EXPORT void SetRotationAngle(const double theRotationAngle);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RotationAboutDirection,
                          StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Direction> myDirectionOfAxis;
  double                          myRotationAngle;
};
