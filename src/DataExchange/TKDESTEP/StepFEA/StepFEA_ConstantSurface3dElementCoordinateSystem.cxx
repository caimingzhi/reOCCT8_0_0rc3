#include <StepFEA_ConstantSurface3dElementCoordinateSystem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ConstantSurface3dElementCoordinateSystem,
                           StepFEA_FeaRepresentationItem)

//=================================================================================================

StepFEA_ConstantSurface3dElementCoordinateSystem::
  StepFEA_ConstantSurface3dElementCoordinateSystem() = default;

//=================================================================================================

void StepFEA_ConstantSurface3dElementCoordinateSystem::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const int                                    aAxis,
  const double                                 aAngle)
{
  StepFEA_FeaRepresentationItem::Init(aRepresentationItem_Name);

  theAxis = aAxis;

  theAngle = aAngle;
}

//=================================================================================================

int StepFEA_ConstantSurface3dElementCoordinateSystem::Axis() const
{
  return theAxis;
}

//=================================================================================================

void StepFEA_ConstantSurface3dElementCoordinateSystem::SetAxis(const int aAxis)
{
  theAxis = aAxis;
}

//=================================================================================================

double StepFEA_ConstantSurface3dElementCoordinateSystem::Angle() const
{
  return theAngle;
}

//=================================================================================================

void StepFEA_ConstantSurface3dElementCoordinateSystem::SetAngle(const double aAngle)
{
  theAngle = aAngle;
}
