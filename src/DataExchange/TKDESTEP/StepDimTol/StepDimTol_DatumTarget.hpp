#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ShapeAspect.hpp>
#include <StepData_Logical.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

class StepDimTol_DatumTarget : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepDimTol_DatumTarget();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Name,
    const occ::handle<TCollection_HAsciiString>&        theShapeAspect_Description,
    const occ::handle<StepRepr_ProductDefinitionShape>& theShapeAspect_OfShape,
    const StepData_Logical                              theShapeAspect_ProductDefinitional,
    const occ::handle<TCollection_HAsciiString>&        theTargetId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TargetId() const;

  Standard_EXPORT void SetTargetId(const occ::handle<TCollection_HAsciiString>& theTargetId);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumTarget, StepRepr_ShapeAspect)

private:
  occ::handle<TCollection_HAsciiString> myTargetId;
};
