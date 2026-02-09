#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_TopologicalRepresentationItem;
class StepData_StepWriter;

class RWStepShape_RWTopologicalRepresentationItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepShape_RWTopologicalRepresentationItem();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                 data,
    const int                                                   num,
    occ::handle<Interface_Check>&                               ach,
    const occ::handle<StepShape_TopologicalRepresentationItem>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                        SW,
    const occ::handle<StepShape_TopologicalRepresentationItem>& ent) const;
};
