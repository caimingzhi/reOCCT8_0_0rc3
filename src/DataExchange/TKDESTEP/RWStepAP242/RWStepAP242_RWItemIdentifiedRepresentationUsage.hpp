#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepAP242_ItemIdentifiedRepresentationUsage;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write Module for ItemIdentifiedRepresentationUsage
class RWStepAP242_RWItemIdentifiedRepresentationUsage
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepAP242_RWItemIdentifiedRepresentationUsage();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                     data,
    const int                                                       num,
    occ::handle<Interface_Check>&                                   ach,
    const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                            SW,
    const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepAP242_ItemIdentifiedRepresentationUsage>& ent,
                             Interface_EntityIterator& iter) const;
};
