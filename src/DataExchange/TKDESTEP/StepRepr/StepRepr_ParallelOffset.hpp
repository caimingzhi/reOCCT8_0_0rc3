#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_DerivedShapeAspect.hpp>
#include <StepData_Logical.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

//! Added for Dimensional Tolerances
class StepRepr_ParallelOffset : public StepRepr_DerivedShapeAspect
{

public:
  Standard_EXPORT StepRepr_ParallelOffset();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        theName,
                            const occ::handle<TCollection_HAsciiString>&        theDescription,
                            const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
                            const StepData_Logical                 theProductDefinitional,
                            const occ::handle<Standard_Transient>& theOffset);

  //! Returns field Offset
  inline occ::handle<Standard_Transient> Offset() const { return offset; }

  //! Set field Offset
  inline void SetOffset(const occ::handle<Standard_Transient>& theOffset) { offset = theOffset; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_ParallelOffset, StepRepr_DerivedShapeAspect)

private:
  occ::handle<Standard_Transient> offset;
};
