#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_BrepWithVoids;
class StepData_StepWriter;
class Interface_EntityIterator;
class Interface_ShareTool;

class RWStepShape_RWBrepWithVoids
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepShape_RWBrepWithVoids();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepShape_BrepWithVoids>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                        SW,
                                 const occ::handle<StepShape_BrepWithVoids>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepShape_BrepWithVoids>& ent,
                             Interface_EntityIterator&                   iter) const;

  Standard_HIDDEN void Check(const occ::handle<StepShape_BrepWithVoids>& ent,
                             const Interface_ShareTool&                  shares,
                             occ::handle<Interface_Check>&               ach) const;
};
