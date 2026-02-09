#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>
#include <StepData_Logical.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

class StepRepr_ParallelOffset : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_ParallelOffset();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        theName,
                            const occ::handle<TCollection_HAsciiString>&        theDescription,
                            const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
                            const StepData_Logical                 theProductDefinitional,
                            const occ::handle<Standard_Transient>& theOffset);

  inline occ::handle<Standard_Transient> Offset() const { return offset; }

  inline void SetOffset(const occ::handle<Standard_Transient>& theOffset) { offset = theOffset; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_ParallelOffset, StepRepr_DerivedShapeAspect)

private:
  occ::handle<Standard_Transient> offset;
};
