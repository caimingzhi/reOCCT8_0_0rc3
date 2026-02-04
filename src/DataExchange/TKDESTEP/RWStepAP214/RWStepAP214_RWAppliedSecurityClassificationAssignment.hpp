#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepAP214_AppliedSecurityClassificationAssignment;
class StepData_StepWriter;
class Interface_EntityIterator;

class RWStepAP214_RWAppliedSecurityClassificationAssignment
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepAP214_RWAppliedSecurityClassificationAssignment();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                           data,
    const int                                                             num,
    occ::handle<Interface_Check>&                                         ach,
    const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                  SW,
    const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent) const;

  Standard_HIDDEN void Share(
    const occ::handle<StepAP214_AppliedSecurityClassificationAssignment>& ent,
    Interface_EntityIterator&                                             iter) const;
};

