#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_Subedge;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for Subedge
class RWStepShape_RWSubedge
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepShape_RWSubedge();

  //! Reads Subedge
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepShape_Subedge>&       ent) const;

  //! Writes Subedge
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                  SW,
                                 const occ::handle<StepShape_Subedge>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepShape_Subedge>& ent,
                             Interface_EntityIterator&             iter) const;
};
