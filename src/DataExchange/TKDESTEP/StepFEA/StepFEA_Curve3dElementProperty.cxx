#include <StepFEA_Curve3dElementProperty.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_Curve3dElementProperty, Standard_Transient)

//=================================================================================================

StepFEA_Curve3dElementProperty::StepFEA_Curve3dElementProperty() = default;

//=================================================================================================

void StepFEA_Curve3dElementProperty::Init(
  const occ::handle<TCollection_HAsciiString>& aPropertyId,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>&
    aIntervalDefinitions,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>&  aEndOffsets,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>& aEndReleases)
{

  thePropertyId = aPropertyId;

  theDescription = aDescription;

  theIntervalDefinitions = aIntervalDefinitions;

  theEndOffsets = aEndOffsets;

  theEndReleases = aEndReleases;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepFEA_Curve3dElementProperty::PropertyId() const
{
  return thePropertyId;
}

//=================================================================================================

void StepFEA_Curve3dElementProperty::SetPropertyId(
  const occ::handle<TCollection_HAsciiString>& aPropertyId)
{
  thePropertyId = aPropertyId;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepFEA_Curve3dElementProperty::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepFEA_Curve3dElementProperty::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>
  StepFEA_Curve3dElementProperty::IntervalDefinitions() const
{
  return theIntervalDefinitions;
}

//=================================================================================================

void StepFEA_Curve3dElementProperty::SetIntervalDefinitions(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>>&
    aIntervalDefinitions)
{
  theIntervalDefinitions = aIntervalDefinitions;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>
  StepFEA_Curve3dElementProperty::EndOffsets() const
{
  return theEndOffsets;
}

//=================================================================================================

void StepFEA_Curve3dElementProperty::SetEndOffsets(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>>& aEndOffsets)
{
  theEndOffsets = aEndOffsets;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>
  StepFEA_Curve3dElementProperty::EndReleases() const
{
  return theEndReleases;
}

//=================================================================================================

void StepFEA_Curve3dElementProperty::SetEndReleases(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>>& aEndReleases)
{
  theEndReleases = aEndReleases;
}
