#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepAP214_RepItemGroup;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for RepItemGroup
class RWStepAP214_RWRepItemGroup
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepAP214_RWRepItemGroup();

  //! Reads RepItemGroup
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepAP214_RepItemGroup>&  ent) const;

  //! Writes RepItemGroup
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                       SW,
                                 const occ::handle<StepAP214_RepItemGroup>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepAP214_RepItemGroup>& ent,
                             Interface_EntityIterator&                  iter) const;
};
