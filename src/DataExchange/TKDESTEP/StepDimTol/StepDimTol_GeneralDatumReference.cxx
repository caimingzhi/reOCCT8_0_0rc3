#include <StepDimTol_GeneralDatumReference.hpp>

#include <StepDimTol_DatumReferenceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_GeneralDatumReference, StepRepr_ShapeAspect)

//=================================================================================================

StepDimTol_GeneralDatumReference::StepDimTol_GeneralDatumReference() = default;

//=================================================================================================

void StepDimTol_GeneralDatumReference::Init(
  const occ::handle<TCollection_HAsciiString>&                               theName,
  const occ::handle<TCollection_HAsciiString>&                               theDescription,
  const occ::handle<StepRepr_ProductDefinitionShape>&                        theOfShape,
  const StepData_Logical                                                     theProductDefinitional,
  const StepDimTol_DatumOrCommonDatum&                                       theBase,
  const bool                                                                 theHasModifiers,
  const occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>& theModifiers)
{
  StepRepr_ShapeAspect::Init(theName, theDescription, theOfShape, theProductDefinitional);
  myBase = theBase;
  if (theHasModifiers)
    myModifiers = theModifiers;
  else
    myModifiers.Nullify();
}
