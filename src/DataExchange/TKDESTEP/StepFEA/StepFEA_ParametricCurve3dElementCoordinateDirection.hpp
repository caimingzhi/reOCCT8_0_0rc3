#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_FeaRepresentationItem.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;

//! Representation of STEP entity ParametricCurve3dElementCoordinateDirection
class StepFEA_ParametricCurve3dElementCoordinateDirection : public StepFEA_FeaRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_ParametricCurve3dElementCoordinateDirection();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<StepGeom_Direction>&       aOrientation);

  //! Returns field Orientation
  Standard_EXPORT occ::handle<StepGeom_Direction> Orientation() const;

  //! Set field Orientation
  Standard_EXPORT void SetOrientation(const occ::handle<StepGeom_Direction>& Orientation);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ParametricCurve3dElementCoordinateDirection,
                          StepFEA_FeaRepresentationItem)

private:
  occ::handle<StepGeom_Direction> theOrientation;
};
