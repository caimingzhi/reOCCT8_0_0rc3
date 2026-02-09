#include <StepDimTol_DatumTarget.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_DatumTarget, StepRepr_ShapeAspect)

StepDimTol_DatumTarget::StepDimTol_DatumTarget() = default;

void StepDimTol_DatumTarget::Init(
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
  const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
  const StepData_Logical                              theShapeAspect_ProductDefinitional,
  const occ::handle<TCollection_HAsciiString>&        theTargetId)
{
  StepRepr_ShapeAspect::Init(theShapeAspect_Name,
                             theShapeAspect_Description,
                             theShapeAspect_OfShape,
                             theShapeAspect_ProductDefinitional);
  myTargetId = theTargetId;
}

occ::handle<TCollection_HAsciiString> StepDimTol_DatumTarget::TargetId() const
{
  return myTargetId;
}

void StepDimTol_DatumTarget::SetTargetId(const occ::handle<TCollection_HAsciiString>& theTargetId)
{
  myTargetId = theTargetId;
}
