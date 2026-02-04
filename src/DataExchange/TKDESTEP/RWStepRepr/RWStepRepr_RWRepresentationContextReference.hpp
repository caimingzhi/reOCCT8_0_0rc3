#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepRepr_RepresentationContextReference;

//! Read & Write tool for RepresentationContextReference
class RWStepRepr_RWRepresentationContextReference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWRepresentationContextReference();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                 theData,
    const int                                                   theNum,
    occ::handle<Interface_Check>&                               theAch,
    const occ::handle<StepRepr_RepresentationContextReference>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                        SW,
    const occ::handle<StepRepr_RepresentationContextReference>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepRepr_RepresentationContextReference>& theEnt,
                             Interface_EntityIterator& iter) const;
};
