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

class StepDimTol_DatumReferenceModifierWithValue : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_DatumReferenceModifierWithValue();

  Standard_EXPORT void Init(const StepDimTol_DatumReferenceModifierType&        theModifierType,
                            const occ::handle<StepBasic_LengthMeasureWithUnit>& theModifierValue);

  inline StepDimTol_DatumReferenceModifierType ModifierType() const { return myModifierType; }

  inline void SetModifierType(const StepDimTol_DatumReferenceModifierType& theModifierType)
  {
    myModifierType = theModifierType;
  }

  inline occ::handle<StepBasic_LengthMeasureWithUnit> ModifierValue() { return myModifierValue; }

  inline void SetModifierValue(const occ::handle<StepBasic_LengthMeasureWithUnit>& theModifierValue)
  {
    myModifierValue = theModifierValue;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReferenceModifierWithValue, Standard_Transient)

private:
  StepDimTol_DatumReferenceModifierType        myModifierType;
  occ::handle<StepBasic_LengthMeasureWithUnit> myModifierValue;
};
