

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFacetedBrep.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_FacetedBrep.hpp>

RWStepShape_RWFacetedBrep::RWStepShape_RWFacetedBrep() = default;

void RWStepShape_RWFacetedBrep::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepShape_FacetedBrep>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "faceted_brep"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_ClosedShell> aOuter;

  data->ReadEntity(num, 2, "outer", ach, STANDARD_TYPE(StepShape_ClosedShell), aOuter);

  ent->Init(aName, aOuter);
}

void RWStepShape_RWFacetedBrep::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepShape_FacetedBrep>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Outer());
}

void RWStepShape_RWFacetedBrep::Share(const occ::handle<StepShape_FacetedBrep>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->Outer());
}
