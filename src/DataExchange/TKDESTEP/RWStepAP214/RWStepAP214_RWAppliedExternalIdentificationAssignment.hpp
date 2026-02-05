#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepAP214_AppliedExternalIdentificationAssignment;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for AppliedExternalIdentificationAssignment
class RWStepAP214_RWAppliedExternalIdentificationAssignment
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepAP214_RWAppliedExternalIdentificationAssignment();

  //! Reads AppliedExternalIdentificationAssignment
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                           data,
    const int                                                             num,
    occ::handle<Interface_Check>&                                         ach,
    const occ::handle<StepAP214_AppliedExternalIdentificationAssignment>& ent) const;

  //! Writes AppliedExternalIdentificationAssignment
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                  SW,
    const occ::handle<StepAP214_AppliedExternalIdentificationAssignment>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepAP214_AppliedExternalIdentificationAssignment>& ent,
    Interface_EntityIterator&                                             iter) const;
};
