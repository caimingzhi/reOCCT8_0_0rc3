#include <StepDimTol_DatumSystem.hpp>

#include <StepDimTol_DatumReferenceCompartment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_DatumSystem, StepRepr_ShapeAspect)

//=================================================================================================

StepDimTol_DatumSystem::StepDimTol_DatumSystem() = default;

//=================================================================================================

void StepDimTol_DatumSystem::Init(
  const occ::handle<TCollection_HAsciiString>&        theName,
  const occ::handle<TCollection_HAsciiString>&        theDescription,
  const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
  const StepData_Logical                              theProductDefinitional,
  const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>&
    theConstituents)
{
  StepRepr_ShapeAspect::Init(theName, theDescription, theOfShape, theProductDefinitional);
  myConstituents = theConstituents;
}
