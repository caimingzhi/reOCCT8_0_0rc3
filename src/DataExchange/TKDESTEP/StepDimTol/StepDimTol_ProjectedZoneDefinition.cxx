#include <StepDimTol_ProjectedZoneDefinition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_ProjectedZoneDefinition, StepDimTol_ToleranceZoneDefinition)

StepDimTol_ProjectedZoneDefinition::StepDimTol_ProjectedZoneDefinition() = default;

void StepDimTol_ProjectedZoneDefinition::Init(
  const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries,
  const occ::handle<StepRepr_ShapeAspect>&                                   theProjectionEnd,
  const occ::handle<StepBasic_LengthMeasureWithUnit>&                        theProjectionLength)
{
  StepDimTol_ToleranceZoneDefinition::Init(theZone, theBoundaries);
  myProjectionEnd    = theProjectionEnd;
  myProjectionLength = theProjectionLength;
}
