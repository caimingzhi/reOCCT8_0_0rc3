#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_ExternallyDefinedItem;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ExternallyDefinedItem
class RWStepBasic_RWExternallyDefinedItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWExternallyDefinedItem();

  //! Reads ExternallyDefinedItem
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&         data,
                                const int                                           num,
                                occ::handle<Interface_Check>&                       ach,
                                const occ::handle<StepBasic_ExternallyDefinedItem>& ent) const;

  //! Writes ExternallyDefinedItem
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                SW,
                                 const occ::handle<StepBasic_ExternallyDefinedItem>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_ExternallyDefinedItem>& ent,
                             Interface_EntityIterator&                           iter) const;
};
