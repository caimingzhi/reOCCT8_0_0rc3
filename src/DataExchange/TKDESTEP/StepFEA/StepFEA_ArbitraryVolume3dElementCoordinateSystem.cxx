#include <StepFEA_ArbitraryVolume3dElementCoordinateSystem.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ArbitraryVolume3dElementCoordinateSystem,
                           StepFEA_FeaRepresentationItem)

StepFEA_ArbitraryVolume3dElementCoordinateSystem::
  StepFEA_ArbitraryVolume3dElementCoordinateSystem() = default;

void StepFEA_ArbitraryVolume3dElementCoordinateSystem::Init(
  const occ::handle<TCollection_HAsciiString>&    aRepresentationItem_Name,
  const occ::handle<StepFEA_FeaAxis2Placement3d>& aCoordinateSystem)
{
  StepFEA_FeaRepresentationItem::Init(aRepresentationItem_Name);

  theCoordinateSystem = aCoordinateSystem;
}

occ::handle<StepFEA_FeaAxis2Placement3d> StepFEA_ArbitraryVolume3dElementCoordinateSystem::
  CoordinateSystem() const
{
  return theCoordinateSystem;
}

void StepFEA_ArbitraryVolume3dElementCoordinateSystem::SetCoordinateSystem(
  const occ::handle<StepFEA_FeaAxis2Placement3d>& aCoordinateSystem)
{
  theCoordinateSystem = aCoordinateSystem;
}
