#include <StepDimTol_ToleranceZoneDefinition.hpp>

#include <StepRepr_ShapeAspect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_ToleranceZoneDefinition, Standard_Transient)

StepDimTol_ToleranceZoneDefinition::StepDimTol_ToleranceZoneDefinition() = default;

void StepDimTol_ToleranceZoneDefinition::Init(
  const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries)
{
  myBoundaries = theBoundaries;
  myZone       = theZone;
}
