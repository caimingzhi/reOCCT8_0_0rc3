#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_DimensionalLocationWithPath.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_DimensionalLocationWithPath, StepShape_DimensionalLocation)

//=================================================================================================

StepShape_DimensionalLocationWithPath::StepShape_DimensionalLocationWithPath() = default;

//=================================================================================================

void StepShape_DimensionalLocationWithPath::Init(
  const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Name,
  const bool                                   hasShapeAspectRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Description,
  const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatingShapeAspect,
  const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatedShapeAspect,
  const occ::handle<StepRepr_ShapeAspect>&     aPath)
{
  StepShape_DimensionalLocation::Init(aShapeAspectRelationship_Name,
                                      hasShapeAspectRelationship_Description,
                                      aShapeAspectRelationship_Description,
                                      aShapeAspectRelationship_RelatingShapeAspect,
                                      aShapeAspectRelationship_RelatedShapeAspect);

  thePath = aPath;
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepShape_DimensionalLocationWithPath::Path() const
{
  return thePath;
}

//=================================================================================================

void StepShape_DimensionalLocationWithPath::SetPath(const occ::handle<StepRepr_ShapeAspect>& aPath)
{
  thePath = aPath;
}
