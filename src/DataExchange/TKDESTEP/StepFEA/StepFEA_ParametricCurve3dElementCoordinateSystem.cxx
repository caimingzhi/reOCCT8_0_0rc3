#include <StepFEA_ParametricCurve3dElementCoordinateDirection.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateSystem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ParametricCurve3dElementCoordinateSystem,
                           StepFEA_FeaRepresentationItem)

//=================================================================================================

StepFEA_ParametricCurve3dElementCoordinateSystem::
  StepFEA_ParametricCurve3dElementCoordinateSystem() = default;

//=================================================================================================

void StepFEA_ParametricCurve3dElementCoordinateSystem::Init(
  const occ::handle<TCollection_HAsciiString>&                            aRepresentationItem_Name,
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& aDirection)
{
  StepFEA_FeaRepresentationItem::Init(aRepresentationItem_Name);

  theDirection = aDirection;
}

//=================================================================================================

occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>
  StepFEA_ParametricCurve3dElementCoordinateSystem::Direction() const
{
  return theDirection;
}

//=================================================================================================

void StepFEA_ParametricCurve3dElementCoordinateSystem::SetDirection(
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& aDirection)
{
  theDirection = aDirection;
}
