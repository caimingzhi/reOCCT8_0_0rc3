

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWGlobalUnitAssignedContext.hpp"
#include <StepBasic_NamedUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>

RWStepRepr_RWGlobalUnitAssignedContext::RWStepRepr_RWGlobalUnitAssignedContext() = default;

void RWStepRepr_RWGlobalUnitAssignedContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepRepr_GlobalUnitAssignedContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "global_unit_assigned_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> aUnits;
  occ::handle<StepBasic_NamedUnit>                                   anent3;
  int                                                                nsub3;
  if (data->ReadSubList(num, 3, "units", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aUnits  = new NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3, i3, "unit", ach, STANDARD_TYPE(StepBasic_NamedUnit), anent3))
        aUnits->SetValue(i3, anent3);
    }
  }

  ent->Init(aContextIdentifier, aContextType, aUnits);
}

void RWStepRepr_RWGlobalUnitAssignedContext::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepRepr_GlobalUnitAssignedContext>& ent) const
{

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbUnits(); i3++)
  {
    SW.Send(ent->UnitsValue(i3));
  }
  SW.CloseSub();
}

void RWStepRepr_RWGlobalUnitAssignedContext::Share(
  const occ::handle<StepRepr_GlobalUnitAssignedContext>& ent,
  Interface_EntityIterator&                              iter) const
{

  int nbElem1 = ent->NbUnits();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->UnitsValue(is1));
  }
}
