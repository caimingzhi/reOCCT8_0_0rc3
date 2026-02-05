#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_ParallelismTolerance;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ParallelismTolerance
class RWStepDimTol_RWParallelismTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWParallelismTolerance();

  //! Reads ParallelismTolerance
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&         data,
                                const int                                           num,
                                occ::handle<Interface_Check>&                       ach,
                                const occ::handle<StepDimTol_ParallelismTolerance>& ent) const;

  //! Writes ParallelismTolerance
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                SW,
                                 const occ::handle<StepDimTol_ParallelismTolerance>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_ParallelismTolerance>& ent,
                             Interface_EntityIterator&                           iter) const;
};
