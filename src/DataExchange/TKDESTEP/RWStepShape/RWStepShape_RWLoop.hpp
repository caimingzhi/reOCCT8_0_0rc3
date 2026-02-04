#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_Loop;
class StepData_StepWriter;

//! Read & Write Module for Loop
class RWStepShape_RWLoop
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepShape_RWLoop();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepShape_Loop>&          ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&               SW,
                                 const occ::handle<StepShape_Loop>& ent) const;
};

