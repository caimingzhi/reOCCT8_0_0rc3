#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_FeaRepresentationItem.hpp>
class StepFEA_ParametricCurve3dElementCoordinateDirection;
class TCollection_HAsciiString;

//! Representation of STEP entity ParametricCurve3dElementCoordinateSystem
class StepFEA_ParametricCurve3dElementCoordinateSystem : public StepFEA_FeaRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_ParametricCurve3dElementCoordinateSystem();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& aDirection);

  //! Returns field Direction
  Standard_EXPORT occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection> Direction()
    const;

  //! Set field Direction
  Standard_EXPORT void SetDirection(
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& Direction);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ParametricCurve3dElementCoordinateSystem,
                          StepFEA_FeaRepresentationItem)

private:
  occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection> theDirection;
};
