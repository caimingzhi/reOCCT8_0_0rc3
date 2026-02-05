#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepDimTol_DatumOrCommonDatum.hpp>
#include <StepDimTol_DatumReferenceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity GeneralDatumReference
class StepDimTol_GeneralDatumReference : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_GeneralDatumReference();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theName,
    const occ::handle<TCollection_HAsciiString>&        theDescription,
    const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
    const StepData_Logical                              theProductDefinitional,
    const StepDimTol_DatumOrCommonDatum&                theBase,
    const bool                                          theHasModifiers,
    const occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>& theModifiers);

  //! Returns field Base
  inline StepDimTol_DatumOrCommonDatum Base() { return myBase; }

  //! Set field Base
  inline void SetBase(const StepDimTol_DatumOrCommonDatum& theBase) { myBase = theBase; }

  //! Indicates is field Modifiers exist
  inline bool HasModifiers() const { return !myModifiers.IsNull() && myModifiers->Length() != 0; }

  //! Returns field Modifiers
  inline occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>> Modifiers()
  {
    return myModifiers;
  }

  //! Set field Modifiers
  inline void SetModifiers(
    const occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>& theModifiers)
  {
    myModifiers = theModifiers;
  }

  //! Returns number of Modifiers
  inline int NbModifiers() const { return (myModifiers.IsNull() ? 0 : myModifiers->Length()); }

  //! Returns Modifiers with the given number
  inline StepDimTol_DatumReferenceModifier ModifiersValue(const int theNum) const
  {
    return myModifiers->Value(theNum);
  }

  //! Sets Modifiers with given number
  inline void ModifiersValue(const int theNum, const StepDimTol_DatumReferenceModifier& theItem)
  {
    myModifiers->SetValue(theNum, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_GeneralDatumReference, StepRepr_ShapeAspect)

private:
  StepDimTol_DatumOrCommonDatum                                       myBase;
  occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>> myModifiers;
};
