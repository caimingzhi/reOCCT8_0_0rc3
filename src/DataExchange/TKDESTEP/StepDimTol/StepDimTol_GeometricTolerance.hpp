#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

//! Representation of STEP entity GeometricTolerance
class StepDimTol_GeometricTolerance : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_GeometricTolerance();

  //! Initialize all fields (own and inherited) AP214
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const occ::handle<StepRepr_ShapeAspect>&     theTolerancedShapeAspect);

  //! Initialize all fields (own and inherited) AP242
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& theName);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription);

  //! Returns field Magnitude
  Standard_EXPORT occ::handle<Standard_Transient> Magnitude() const;

  //! Set field Magnitude
  Standard_EXPORT void SetMagnitude(const occ::handle<Standard_Transient>& theMagnitude);

  //! Returns field TolerancedShapeAspect
  //! Note: in AP214(203) type of this attribute can be only StepRepr_ShapeAspect
  Standard_EXPORT StepDimTol_GeometricToleranceTarget TolerancedShapeAspect() const;

  //! Set field TolerancedShapeAspect AP214
  Standard_EXPORT void SetTolerancedShapeAspect(
    const occ::handle<StepRepr_ShapeAspect>& theTolerancedShapeAspect);

  //! Set field TolerancedShapeAspect AP242
  Standard_EXPORT void SetTolerancedShapeAspect(
    const StepDimTol_GeometricToleranceTarget& theTolerancedShapeAspect);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricTolerance, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myName;
  occ::handle<TCollection_HAsciiString> myDescription;
  occ::handle<Standard_Transient>       myMagnitude;
  StepDimTol_GeometricToleranceTarget   myTolerancedShapeAspect;
};
