#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_IntegerRepresentationItem;
class StepData_StepWriter;

class RWStepRepr_RWIntegerRepresentationItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWIntegerRepresentationItem();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&            data,
                                const int                                              num,
                                occ::handle<Interface_Check>&                          ach,
                                const occ::handle<StepRepr_IntegerRepresentationItem>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                   SW,
                                 const occ::handle<StepRepr_IntegerRepresentationItem>& ent) const;
};
