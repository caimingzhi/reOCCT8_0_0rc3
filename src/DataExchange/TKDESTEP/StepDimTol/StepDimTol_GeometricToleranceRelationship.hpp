#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepDimTol_GeometricTolerance;

class StepDimTol_GeometricToleranceRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_GeometricToleranceRelationship();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theName,
    const occ::handle<TCollection_HAsciiString>&      theDescription,
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance,
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& theName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription);

  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> RelatingGeometricTolerance() const;

  Standard_EXPORT void SetRelatingGeometricTolerance(
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance);

  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> RelatedGeometricTolerance() const;

  Standard_EXPORT void SetRelatedGeometricTolerance(
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>      myName;
  occ::handle<TCollection_HAsciiString>      myDescription;
  occ::handle<StepDimTol_GeometricTolerance> myRelatingGeometricTolerance;
  occ::handle<StepDimTol_GeometricTolerance> myRelatedGeometricTolerance;
};
