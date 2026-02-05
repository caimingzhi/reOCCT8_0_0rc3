#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_CircularRunoutTolerance;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CircularRunoutTolerance
class RWStepDimTol_RWCircularRunoutTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWCircularRunoutTolerance();

  //! Reads CircularRunoutTolerance
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&            data,
                                const int                                              num,
                                occ::handle<Interface_Check>&                          ach,
                                const occ::handle<StepDimTol_CircularRunoutTolerance>& ent) const;

  //! Writes CircularRunoutTolerance
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                   SW,
                                 const occ::handle<StepDimTol_CircularRunoutTolerance>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_CircularRunoutTolerance>& ent,
                             Interface_EntityIterator&                              iter) const;
};
