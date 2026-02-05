#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_IdentificationRole;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for IdentificationRole
class RWStepBasic_RWIdentificationRole
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWIdentificationRole();

  //! Reads IdentificationRole
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&      data,
                                const int                                        num,
                                occ::handle<Interface_Check>&                    ach,
                                const occ::handle<StepBasic_IdentificationRole>& ent) const;

  //! Writes IdentificationRole
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                             SW,
                                 const occ::handle<StepBasic_IdentificationRole>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_IdentificationRole>& ent,
                             Interface_EntityIterator&                        iter) const;
};
