#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_BooleanRepresentationItem;
class StepData_StepWriter;

class RWStepRepr_RWBooleanRepresentationItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWBooleanRepresentationItem();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&            theData,
    const int                                              theNum,
    occ::handle<Interface_Check>&                          theAch,
    const occ::handle<StepRepr_BooleanRepresentationItem>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                   theSW,
    const occ::handle<StepRepr_BooleanRepresentationItem>& theEnt) const;
};
