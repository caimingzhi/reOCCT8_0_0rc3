#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceRelationship, Standard_Transient)

//=================================================================================================

StepDimTol_GeometricToleranceRelationship::StepDimTol_GeometricToleranceRelationship() = default;

//=================================================================================================

void StepDimTol_GeometricToleranceRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&      theName,
  const occ::handle<TCollection_HAsciiString>&      theDescription,
  const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance,
  const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance)
{

  myName = theName;

  myDescription = theDescription;

  myRelatingGeometricTolerance = theRelatingGeometricTolerance;

  myRelatedGeometricTolerance = theRelatedGeometricTolerance;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepDimTol_GeometricToleranceRelationship::Name() const
{
  return myName;
}

//=================================================================================================

void StepDimTol_GeometricToleranceRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& theName)
{
  myName = theName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepDimTol_GeometricToleranceRelationship::Description() const
{
  return myDescription;
}

//=================================================================================================

void StepDimTol_GeometricToleranceRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& theDescription)
{
  myDescription = theDescription;
}

//=================================================================================================

occ::handle<StepDimTol_GeometricTolerance> StepDimTol_GeometricToleranceRelationship::
  RelatingGeometricTolerance() const
{
  return myRelatingGeometricTolerance;
}

//=================================================================================================

void StepDimTol_GeometricToleranceRelationship::SetRelatingGeometricTolerance(
  const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance)
{
  myRelatingGeometricTolerance = theRelatingGeometricTolerance;
}

//=================================================================================================

occ::handle<StepDimTol_GeometricTolerance> StepDimTol_GeometricToleranceRelationship::
  RelatedGeometricTolerance() const
{
  return myRelatedGeometricTolerance;
}

//=================================================================================================

void StepDimTol_GeometricToleranceRelationship::SetRelatedGeometricTolerance(
  const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance)
{
  myRelatedGeometricTolerance = theRelatedGeometricTolerance;
}
