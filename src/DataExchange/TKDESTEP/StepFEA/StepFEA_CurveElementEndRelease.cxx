#include <StepFEA_CurveElementEndRelease.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_CurveElementEndRelease, Standard_Transient)

//=================================================================================================

StepFEA_CurveElementEndRelease::StepFEA_CurveElementEndRelease() = default;

//=================================================================================================

void StepFEA_CurveElementEndRelease::Init(
  const StepFEA_CurveElementEndCoordinateSystem& aCoordinateSystem,
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>&
    aReleases)
{

  theCoordinateSystem = aCoordinateSystem;

  theReleases = aReleases;
}

//=================================================================================================

StepFEA_CurveElementEndCoordinateSystem StepFEA_CurveElementEndRelease::CoordinateSystem() const
{
  return theCoordinateSystem;
}

//=================================================================================================

void StepFEA_CurveElementEndRelease::SetCoordinateSystem(
  const StepFEA_CurveElementEndCoordinateSystem& aCoordinateSystem)
{
  theCoordinateSystem = aCoordinateSystem;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>
  StepFEA_CurveElementEndRelease::Releases() const
{
  return theReleases;
}

//=================================================================================================

void StepFEA_CurveElementEndRelease::SetReleases(
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>&
    aReleases)
{
  theReleases = aReleases;
}
