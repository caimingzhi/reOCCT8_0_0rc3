#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_FeaRepresentationItem.hpp>
class StepFEA_ParametricCurve3dElementCoordinateDirection;
class TCollection_HAsciiString;

class StepFEA_ParametricCurve3dElementCoordinateSystem : public StepFEA_FeaRepresentationItem
{

public:
  Standard_EXPORT StepFEA_ParametricCurve3dElementCoordinateSystem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& aDirection);

  Standard_EXPORT occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection> Direction()
    const;

  Standard_EXPORT void SetDirection(
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& Direction);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ParametricCurve3dElementCoordinateSystem,
                          StepFEA_FeaRepresentationItem)

private:
  occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection> theDirection;
};
