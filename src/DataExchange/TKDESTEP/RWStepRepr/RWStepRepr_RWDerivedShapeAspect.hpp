#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_DerivedShapeAspect;
class StepData_StepWriter;
class Interface_EntityIterator;

class RWStepRepr_RWDerivedShapeAspect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWDerivedShapeAspect();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&     data,
                                const int                                       num,
                                occ::handle<Interface_Check>&                   ach,
                                const occ::handle<StepRepr_DerivedShapeAspect>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                            SW,
                                 const occ::handle<StepRepr_DerivedShapeAspect>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepRepr_DerivedShapeAspect>& ent,
                             Interface_EntityIterator&                       iter) const;
};
