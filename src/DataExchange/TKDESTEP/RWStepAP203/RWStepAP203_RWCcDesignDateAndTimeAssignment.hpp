#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepAP203_CcDesignDateAndTimeAssignment;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CcDesignDateAndTimeAssignment
class RWStepAP203_RWCcDesignDateAndTimeAssignment
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepAP203_RWCcDesignDateAndTimeAssignment();

  //! Reads CcDesignDateAndTimeAssignment
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                 data,
    const int                                                   num,
    occ::handle<Interface_Check>&                               ach,
    const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent) const;

  //! Writes CcDesignDateAndTimeAssignment
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                        SW,
    const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepAP203_CcDesignDateAndTimeAssignment>& ent,
                             Interface_EntityIterator& iter) const;
};
