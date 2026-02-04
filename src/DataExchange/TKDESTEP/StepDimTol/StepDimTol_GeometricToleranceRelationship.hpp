#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepDimTol_GeometricTolerance;

//! Representation of STEP entity GeometricToleranceRelationship
class StepDimTol_GeometricToleranceRelationship : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_GeometricToleranceRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theName,
    const occ::handle<TCollection_HAsciiString>&      theDescription,
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance,
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& theName);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription);

  //! Returns field RelatingGeometricTolerance
  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> RelatingGeometricTolerance() const;

  //! Set field RelatingGeometricTolerance
  Standard_EXPORT void SetRelatingGeometricTolerance(
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatingGeometricTolerance);

  //! Returns field RelatedGeometricTolerance
  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> RelatedGeometricTolerance() const;

  //! Set field RelatedGeometricTolerance
  Standard_EXPORT void SetRelatedGeometricTolerance(
    const occ::handle<StepDimTol_GeometricTolerance>& theRelatedGeometricTolerance);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>      myName;
  occ::handle<TCollection_HAsciiString>      myDescription;
  occ::handle<StepDimTol_GeometricTolerance> myRelatingGeometricTolerance;
  occ::handle<StepDimTol_GeometricTolerance> myRelatedGeometricTolerance;
};

