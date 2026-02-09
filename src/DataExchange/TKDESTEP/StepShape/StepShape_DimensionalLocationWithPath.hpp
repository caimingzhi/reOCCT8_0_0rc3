#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_DimensionalLocation.hpp>
class StepRepr_ShapeAspect;
class TCollection_HAsciiString;

class StepShape_DimensionalLocationWithPath : public StepShape_DimensionalLocation
{

public:
  Standard_EXPORT StepShape_DimensionalLocationWithPath();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Name,
    const bool                                   hasShapeAspectRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Description,
    const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatingShapeAspect,
    const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatedShapeAspect,
    const occ::handle<StepRepr_ShapeAspect>&     aPath);

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> Path() const;

  Standard_EXPORT void SetPath(const occ::handle<StepRepr_ShapeAspect>& Path);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalLocationWithPath, StepShape_DimensionalLocation)

private:
  occ::handle<StepRepr_ShapeAspect> thePath;
};
