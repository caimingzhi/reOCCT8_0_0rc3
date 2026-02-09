

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWAssemblyComponentUsageSubstitute.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>

RWStepRepr_RWAssemblyComponentUsageSubstitute::RWStepRepr_RWAssemblyComponentUsageSubstitute() =
  default;

void RWStepRepr_RWAssemblyComponentUsageSubstitute::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepRepr_AssemblyComponentUsageSubstitute>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "assembly_component_usage_substitute"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDef;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "definition", ach, aDef);
  }

  occ::handle<StepRepr_AssemblyComponentUsage> aBase;

  data->ReadEntity(num, 3, "base", ach, STANDARD_TYPE(StepRepr_AssemblyComponentUsage), aBase);

  occ::handle<StepRepr_AssemblyComponentUsage> aSubs;

  data
    ->ReadEntity(num, 4, "substitute", ach, STANDARD_TYPE(StepRepr_AssemblyComponentUsage), aSubs);

  ent->Init(aName, aDef, aBase, aSubs);
}

void RWStepRepr_RWAssemblyComponentUsageSubstitute::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepRepr_AssemblyComponentUsageSubstitute>& ent) const
{

  SW.Send(ent->Name());
  SW.Send(ent->Definition());
  SW.Send(ent->Base());
  SW.Send(ent->Substitute());
}

void RWStepRepr_RWAssemblyComponentUsageSubstitute::Share(
  const occ::handle<StepRepr_AssemblyComponentUsageSubstitute>& ent,
  Interface_EntityIterator&                                     iter) const
{

  iter.GetOneItem(ent->Base());

  iter.GetOneItem(ent->Substitute());
}
