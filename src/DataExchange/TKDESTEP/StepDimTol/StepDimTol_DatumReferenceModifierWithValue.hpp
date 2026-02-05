#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>

enum StepDimTol_DatumReferenceModifierType
{
  StepDimTol_CircularOrCylindrical,
  StepDimTol_Distance,
  StepDimTol_Projected,
  StepDimTol_Spherical
};

//! Representation of STEP entity DatumReferenceModifierWithValue
class StepDimTol_DatumReferenceModifierWithValue : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumReferenceModifierWithValue();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepDimTol_DatumReferenceModifierType&        theModifierType,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theModifierValue);

  //! Returns field ModifierType
  inline StepDimTol_DatumReferenceModifierType ModifierType() const { return myModifierType; }

  //! Set field ModifierType
  inline void SetModifierType(const StepDimTol_DatumReferenceModifierType& theModifierType)
  {
    myModifierType = theModifierType;
  }

  //! Returns field ModifierValue
  inline occ::handle<StepBasic_LengthMeasureWithUnit> ModifierValue() { return myModifierValue; }

  //! Set field ModifierValue
  inline void SetModifierValue(const occ::handle<StepBasic_LengthMeasureWithUnit>& theModifierValue)
  {
    myModifierValue = theModifierValue;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReferenceModifierWithValue, Standard_Transient)

private:
  StepDimTol_DatumReferenceModifierType        myModifierType;
  occ::handle<StepBasic_LengthMeasureWithUnit> myModifierValue;
};
