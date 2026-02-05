#include <StepRepr_ParallelOffset.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ParallelOffset, StepRepr_DerivedShapeAspect)

StepRepr_ParallelOffset::StepRepr_ParallelOffset() = default;

//=================================================================================================

void StepRepr_ParallelOffset::Init(
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
  const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
  const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
  const StepData_Logical                              theShapeAspect_ProductDefinitional,
  const occ::handle<Standard_Transient>&              theOffset)
{
  StepRepr_ShapeAspect::Init(theShapeAspect_Name,
                             theShapeAspect_Description,
                             theShapeAspect_OfShape,
                             theShapeAspect_ProductDefinitional);

  offset = theOffset;
}
