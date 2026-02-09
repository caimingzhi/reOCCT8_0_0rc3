#pragma once

#include <Standard.hpp>

#include <StepFEA_CurveElementEndCoordinateSystem.hpp>
#include <StepElement_CurveElementEndReleasePacket.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class StepFEA_CurveElementEndRelease : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_CurveElementEndRelease();

  Standard_EXPORT void Init(
    const StepFEA_CurveElementEndCoordinateSystem& aCoordinateSystem,
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>&
      aReleases);

  Standard_EXPORT StepFEA_CurveElementEndCoordinateSystem CoordinateSystem() const;

  Standard_EXPORT void SetCoordinateSystem(
    const StepFEA_CurveElementEndCoordinateSystem& CoordinateSystem);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>
    Releases() const;

  Standard_EXPORT void SetReleases(
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>&
      Releases);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementEndRelease, Standard_Transient)

private:
  StepFEA_CurveElementEndCoordinateSystem theCoordinateSystem;
  occ::handle<NCollection_HArray1<occ::handle<StepElement_CurveElementEndReleasePacket>>>
    theReleases;
};
