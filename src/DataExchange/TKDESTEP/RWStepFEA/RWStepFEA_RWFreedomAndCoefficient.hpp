#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_FreedomAndCoefficient;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for FreedomAndCoefficient
class RWStepFEA_RWFreedomAndCoefficient
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWFreedomAndCoefficient();

  //! Reads FreedomAndCoefficient
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&       data,
                                const int                                         num,
                                occ::handle<Interface_Check>&                     ach,
                                const occ::handle<StepFEA_FreedomAndCoefficient>& ent) const;

  //! Writes FreedomAndCoefficient
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                              SW,
                                 const occ::handle<StepFEA_FreedomAndCoefficient>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_FreedomAndCoefficient>& ent,
                             Interface_EntityIterator&                         iter) const;
};
