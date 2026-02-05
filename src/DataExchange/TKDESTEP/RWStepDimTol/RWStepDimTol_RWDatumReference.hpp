#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_DatumReference;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DatumReference
class RWStepDimTol_RWDatumReference
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWDatumReference();

  //! Reads DatumReference
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&   data,
                                const int                                     num,
                                occ::handle<Interface_Check>&                 ach,
                                const occ::handle<StepDimTol_DatumReference>& ent) const;

  //! Writes DatumReference
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                          SW,
                                 const occ::handle<StepDimTol_DatumReference>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_DatumReference>& ent,
                             Interface_EntityIterator&                     iter) const;
};
