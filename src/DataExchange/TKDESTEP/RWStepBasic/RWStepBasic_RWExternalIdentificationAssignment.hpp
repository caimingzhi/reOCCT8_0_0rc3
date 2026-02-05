#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_ExternalIdentificationAssignment;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ExternalIdentificationAssignment
class RWStepBasic_RWExternalIdentificationAssignment
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWExternalIdentificationAssignment();

  //! Reads ExternalIdentificationAssignment
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                    data,
    const int                                                      num,
    occ::handle<Interface_Check>&                                  ach,
    const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent) const;

  //! Writes ExternalIdentificationAssignment
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                           SW,
    const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_ExternalIdentificationAssignment>& ent,
                             Interface_EntityIterator& iter) const;
};
