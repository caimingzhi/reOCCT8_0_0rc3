#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepGeom_Direction.hpp>

//! Representation of STEP entity RotationAboutDirection
class StepKinematics_RotationAboutDirection : public StepGeom_GeometricRepresentationItem
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RotationAboutDirection();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepGeom_Direction>&       theDirectionOfAxis,
                            const double                                 theRotationAngle);

  //! Returns field DirectionOfAxis
  Standard_EXPORT occ::handle<StepGeom_Direction> DirectionOfAxis() const;
  //! Sets field DirectionOfAxis
  Standard_EXPORT void SetDirectionOfAxis(
    const occ::handle<StepGeom_Direction>& theDirectionOfAxis);

  //! Returns field RotationAngle
  Standard_EXPORT double RotationAngle() const;
  //! Sets field RotationAngle
  Standard_EXPORT void SetRotationAngle(const double theRotationAngle);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RotationAboutDirection,
                          StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Direction> myDirectionOfAxis;
  double                          myRotationAngle;
};
