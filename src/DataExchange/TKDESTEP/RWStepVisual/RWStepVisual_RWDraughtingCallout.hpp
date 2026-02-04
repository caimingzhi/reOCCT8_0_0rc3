#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Interface_EntityIterator;
class StepData_StepReaderData;
class Interface_Check;
class StepVisual_DraughtingCallout;
class StepData_StepWriter;

//! Read & Write Module for DraughtingCallout
class RWStepVisual_RWDraughtingCallout
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWDraughtingCallout();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&      data,
                                const int                                        num,
                                occ::handle<Interface_Check>&                    ach,
                                const occ::handle<StepVisual_DraughtingCallout>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                             SW,
                                 const occ::handle<StepVisual_DraughtingCallout>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_DraughtingCallout>& ent,
                             Interface_EntityIterator&                        iter) const;
};
