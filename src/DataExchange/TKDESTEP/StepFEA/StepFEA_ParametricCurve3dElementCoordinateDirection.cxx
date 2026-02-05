#include <StepFEA_ParametricCurve3dElementCoordinateDirection.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ParametricCurve3dElementCoordinateDirection,
                           StepFEA_FeaRepresentationItem)

//=================================================================================================

StepFEA_ParametricCurve3dElementCoordinateDirection::
  StepFEA_ParametricCurve3dElementCoordinateDirection() = default;

//=================================================================================================

void StepFEA_ParametricCurve3dElementCoordinateDirection::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<StepGeom_Direction>&       aOrientation)
{
  StepFEA_FeaRepresentationItem::Init(aRepresentationItem_Name);

  theOrientation = aOrientation;
}

//=================================================================================================

occ::handle<StepGeom_Direction> StepFEA_ParametricCurve3dElementCoordinateDirection::Orientation()
  const
{
  return theOrientation;
}

//=================================================================================================

void StepFEA_ParametricCurve3dElementCoordinateDirection::SetOrientation(
  const occ::handle<StepGeom_Direction>& aOrientation)
{
  theOrientation = aOrientation;
}
