

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWGlobalUncertaintyAssignedContext.hpp"
#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_GlobalUncertaintyAssignedContext.hpp>

RWStepRepr_RWGlobalUncertaintyAssignedContext::RWStepRepr_RWGlobalUncertaintyAssignedContext() =
  default;

void RWStepRepr_RWGlobalUncertaintyAssignedContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "global_uncertainty_assigned_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>> aUncertainty;
  occ::handle<StepBasic_UncertaintyMeasureWithUnit>                                   anent3;
  int                                                                                 nsub3;
  if (data->ReadSubList(num, 3, "uncertainty", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aUncertainty =
      new NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3,
                           i3,
                           "uncertainty_measure_with_unit",
                           ach,
                           STANDARD_TYPE(StepBasic_UncertaintyMeasureWithUnit),
                           anent3))
        aUncertainty->SetValue(i3, anent3);
    }
  }

  ent->Init(aContextIdentifier, aContextType, aUncertainty);
}

void RWStepRepr_RWGlobalUncertaintyAssignedContext::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& ent) const
{

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbUncertainty(); i3++)
  {
    SW.Send(ent->UncertaintyValue(i3));
  }
  SW.CloseSub();
}

void RWStepRepr_RWGlobalUncertaintyAssignedContext::Share(
  const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& ent,
  Interface_EntityIterator&                                     iter) const
{

  int nbElem1 = ent->NbUncertainty();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->UncertaintyValue(is1));
  }
}
