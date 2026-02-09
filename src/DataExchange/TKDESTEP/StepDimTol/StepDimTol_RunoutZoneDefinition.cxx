#include <StepDimTol_RunoutZoneDefinition.hpp>

#include <StepRepr_ShapeAspect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepDimTol_RunoutZoneOrientation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_RunoutZoneDefinition, StepDimTol_ToleranceZoneDefinition)

StepDimTol_RunoutZoneDefinition::StepDimTol_RunoutZoneDefinition() = default;

void StepDimTol_RunoutZoneDefinition::Init(
  const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries,
  const occ::handle<StepDimTol_RunoutZoneOrientation>&                       theOrientation)
{
  StepDimTol_ToleranceZoneDefinition::Init(theZone, theBoundaries);
  myOrientation = theOrientation;
}
