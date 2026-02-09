#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepVisual_PreDefinedItem;
class StepData_StepWriter;

class RWStepVisual_RWPreDefinedItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWPreDefinedItem();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&   data,
                                const int                                     num,
                                occ::handle<Interface_Check>&                 ach,
                                const occ::handle<StepVisual_PreDefinedItem>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                          SW,
                                 const occ::handle<StepVisual_PreDefinedItem>& ent) const;
};
