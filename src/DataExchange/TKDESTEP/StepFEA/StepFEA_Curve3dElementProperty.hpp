#pragma once

#include <Standard.hpp>

#include <StepFEA_CurveElementInterval.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_CurveElementEndOffset.hpp>
#include <StepFEA_CurveElementEndRelease.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepFEA_Curve3dElementProperty : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_Curve3dElementProperty();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aPropertyId,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>&
      aIntervalDefinitions,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>& aEndOffsets,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>&
      aEndReleases);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PropertyId() const;

  Standard_EXPORT void SetPropertyId(const occ::handle<TCollection_HAsciiString>& PropertyId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>
                  IntervalDefinitions() const;

  Standard_EXPORT void SetIntervalDefinitions(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>&
      IntervalDefinitions);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>
                  EndOffsets() const;

  Standard_EXPORT void SetEndOffsets(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>& EndOffsets);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>
                  EndReleases() const;

  Standard_EXPORT void SetEndReleases(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>&
      EndReleases);

  DEFINE_STANDARD_RTTIEXT(StepFEA_Curve3dElementProperty, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> thePropertyId;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>
    theIntervalDefinitions;
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>  theEndOffsets;
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>> theEndReleases;
};
