#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepDimTol_DatumOrCommonDatum.hpp>
#include <StepDimTol_DatumReferenceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepDimTol_GeneralDatumReference : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepDimTol_GeneralDatumReference();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theName,
    const occ::handle<TCollection_HAsciiString>&        theDescription,
    const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
    const StepData_Logical                              theProductDefinitional,
    const StepDimTol_DatumOrCommonDatum&                theBase,
    const bool                                          theHasModifiers,
    const occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>& theModifiers);

  inline StepDimTol_DatumOrCommonDatum Base() { return myBase; }

  inline void SetBase(const StepDimTol_DatumOrCommonDatum& theBase) { myBase = theBase; }

  inline bool HasModifiers() const { return !myModifiers.IsNull() && myModifiers->Length() != 0; }

  inline occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>> Modifiers()
  {
    return myModifiers;
  }

  inline void SetModifiers(
    const occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>& theModifiers)
  {
    myModifiers = theModifiers;
  }

  inline int NbModifiers() const { return (myModifiers.IsNull() ? 0 : myModifiers->Length()); }

  inline StepDimTol_DatumReferenceModifier ModifiersValue(const int theNum) const
  {
    return myModifiers->Value(theNum);
  }

  inline void ModifiersValue(const int theNum, const StepDimTol_DatumReferenceModifier& theItem)
  {
    myModifiers->SetValue(theNum, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeneralDatumReference, StepRepr_ShapeAspect)

private:
  StepDimTol_DatumOrCommonDatum                                       myBase;
  occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>> myModifiers;
};
