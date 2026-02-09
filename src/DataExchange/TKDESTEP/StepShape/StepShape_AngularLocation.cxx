#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_AngularLocation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_AngularLocation, StepShape_DimensionalLocation)

StepShape_AngularLocation::StepShape_AngularLocation() = default;

void StepShape_AngularLocation::Init(
  const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Name,
  const bool                                   hasShapeAspectRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Description,
  const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatingShapeAspect,
  const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatedShapeAspect,
  const StepShape_AngleRelator                 aAngleSelection)
{
  StepShape_DimensionalLocation::Init(aShapeAspectRelationship_Name,
                                      hasShapeAspectRelationship_Description,
                                      aShapeAspectRelationship_Description,
                                      aShapeAspectRelationship_RelatingShapeAspect,
                                      aShapeAspectRelationship_RelatedShapeAspect);

  theAngleSelection = aAngleSelection;
}

StepShape_AngleRelator StepShape_AngularLocation::AngleSelection() const
{
  return theAngleSelection;
}

void StepShape_AngularLocation::SetAngleSelection(const StepShape_AngleRelator aAngleSelection)
{
  theAngleSelection = aAngleSelection;
}
