#include <StepFEA_AlignedSurface3dElementCoordinateSystem.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_AlignedSurface3dElementCoordinateSystem,
                           StepFEA_FeaRepresentationItem)

//=================================================================================================

StepFEA_AlignedSurface3dElementCoordinateSystem::StepFEA_AlignedSurface3dElementCoordinateSystem() =
  default;

//=================================================================================================

void StepFEA_AlignedSurface3dElementCoordinateSystem::Init(
  const occ::handle<TCollection_HAsciiString>&    aRepresentationItem_Name,
  const occ::handle<StepFEA_FeaAxis2Placement3d>& aCoordinateSystem)
{
  StepFEA_FeaRepresentationItem::Init(aRepresentationItem_Name);

  theCoordinateSystem = aCoordinateSystem;
}

//=================================================================================================

occ::handle<StepFEA_FeaAxis2Placement3d> StepFEA_AlignedSurface3dElementCoordinateSystem::
  CoordinateSystem() const
{
  return theCoordinateSystem;
}

//=================================================================================================

void StepFEA_AlignedSurface3dElementCoordinateSystem::SetCoordinateSystem(
  const occ::handle<StepFEA_FeaAxis2Placement3d>& aCoordinateSystem)
{
  theCoordinateSystem = aCoordinateSystem;
}
