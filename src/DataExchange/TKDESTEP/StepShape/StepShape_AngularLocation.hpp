#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_AngleRelator.hpp>
#include <StepShape_DimensionalLocation.hpp>
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepShape_AngularLocation : public StepShape_DimensionalLocation
{

public:
  Standard_EXPORT StepShape_AngularLocation();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Name,
    const bool                                   hasShapeAspectRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& aShapeAspectRelationship_Description,
    const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatingShapeAspect,
    const occ::handle<StepRepr_ShapeAspect>&     aShapeAspectRelationship_RelatedShapeAspect,
    const StepShape_AngleRelator                 aAngleSelection);

  Standard_EXPORT StepShape_AngleRelator AngleSelection() const;

  Standard_EXPORT void SetAngleSelection(const StepShape_AngleRelator AngleSelection);

  DEFINE_STANDARD_RTTIEXT(StepShape_AngularLocation, StepShape_DimensionalLocation)

private:
  StepShape_AngleRelator theAngleSelection;
};
