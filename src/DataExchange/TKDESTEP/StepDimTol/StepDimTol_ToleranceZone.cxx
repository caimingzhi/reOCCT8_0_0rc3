#include <StepDimTol_ToleranceZone.hpp>

#include <StepDimTol_ToleranceZoneTarget.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_ToleranceZone, StepRepr_ShapeAspect)

StepDimTol_ToleranceZone::StepDimTol_ToleranceZone() = default;

void StepDimTol_ToleranceZone::Init(
  const occ::handle<TCollection_HAsciiString>&                            theName,
  const occ::handle<TCollection_HAsciiString>&                            theDescription,
  const occ::handle<StepRepr_ProductDefinitionShape>&                     theOfShape,
  const StepData_Logical                                                  theProductDefinitional,
  const occ::handle<NCollection_HArray1<StepDimTol_ToleranceZoneTarget>>& theDefiningTolerance,
  const occ::handle<StepDimTol_ToleranceZoneForm>&                        theForm)
{
  StepRepr_ShapeAspect::Init(theName, theDescription, theOfShape, theProductDefinitional);
  myDefiningTolerance = theDefiningTolerance;
  myForm              = theForm;
}
