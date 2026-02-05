#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class TCollection_HAsciiString;
class StepDimTol_GeometricToleranceTarget;

//! Representation of STEP entity GeometricToleranceWithModifiers
class StepDimTol_GeometricToleranceWithModifiers : public StepDimTol_GeometricTolerance
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_GeometricToleranceWithModifiers();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<TCollection_HAsciiString>& theDescription,
    const occ::handle<Standard_Transient>&       theMagnitude,
    const StepDimTol_GeometricToleranceTarget&   theTolerancedShapeAspect,
    const occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>>& theModifiers);

  //! Returns field Modifiers
  inline occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>> Modifiers() const
  {
    return myModifiers;
  }

  //! Set field Modifiers
  inline void SetModifiers(
    const occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>>& theModifiers)
  {
    myModifiers = theModifiers;
  }

  //! Returns number of modifiers
  inline int NbModifiers() const { return (myModifiers.IsNull() ? 0 : myModifiers->Length()); }

  //! Returns modifier with the given number
  inline StepDimTol_GeometricToleranceModifier ModifierValue(const int theNum) const
  {
    return myModifiers->Value(theNum);
  }

  //! Sets modifier with given number
  inline void SetModifierValue(const int                                   theNum,
                               const StepDimTol_GeometricToleranceModifier theItem)
  {
    myModifiers->SetValue(theNum, theItem);
  }
  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeometricToleranceWithModifiers, StepDimTol_GeometricTolerance)

private:
  occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>> myModifiers;
};
