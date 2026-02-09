#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepDimTol_GeometricTolerance : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_GeometricTolerance();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const occ::handle<StepRepr_ShapeAspect>&     theTolerancedShapeAspect);

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const occ::handle<TCollection_HAsciiString>& theDescription,
                            const occ::handle<Standard_Transient>&       theMagnitude,
                            const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& theName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription);

  Standard_EXPORT occ::handle<Standard_Transient> Magnitude() const;

  Standard_EXPORT void SetMagnitude(const occ::handle<Standard_Transient>& theMagnitude);

  Standard_EXPORT StepDimTol_GeometricToleranceTarget TolerancedShapeAspect() const;

  Standard_EXPORT void SetTolerancedShapeAspect(
    const occ::handle<StepRepr_ShapeAspect>& theTolerancedShapeAspect);

  Standard_EXPORT void SetTolerancedShapeAspect(
    const StepDimTol_GeometricToleranceTarget& theTolerancedShapeAspect);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricTolerance, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myName;
  occ::handle<TCollection_HAsciiString> myDescription;
  occ::handle<Standard_Transient>       myMagnitude;
  StepDimTol_GeometricToleranceTarget   myTolerancedShapeAspect;
};
