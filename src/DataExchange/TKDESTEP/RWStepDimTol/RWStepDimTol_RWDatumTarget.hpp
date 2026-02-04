#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_DatumTarget;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DatumTarget
class RWStepDimTol_RWDatumTarget
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWDatumTarget();

  //! Reads DatumTarget
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepDimTol_DatumTarget>&  ent) const;

  //! Writes DatumTarget
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                       SW,
                                 const occ::handle<StepDimTol_DatumTarget>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_DatumTarget>& ent,
                             Interface_EntityIterator&                  iter) const;
};

