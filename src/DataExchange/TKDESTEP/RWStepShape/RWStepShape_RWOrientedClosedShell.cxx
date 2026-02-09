

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWOrientedClosedShell.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_OrientedClosedShell.hpp>

RWStepShape_RWOrientedClosedShell::RWStepShape_RWOrientedClosedShell() = default;

void RWStepShape_RWOrientedClosedShell::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepShape_OrientedClosedShell>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "oriented_closed_shell"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  data->CheckDerived(num, 2, "cfs_faces", ach, false);

  occ::handle<StepShape_ClosedShell> aClosedShellElement;

  data->ReadEntity(num,
                   3,
                   "closed_shell_element",
                   ach,
                   STANDARD_TYPE(StepShape_ClosedShell),
                   aClosedShellElement);

  bool aOrientation;

  data->ReadBoolean(num, 4, "orientation", ach, aOrientation);

  ent->Init(aName, aClosedShellElement, aOrientation);
}

void RWStepShape_RWOrientedClosedShell::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepShape_OrientedClosedShell>& ent) const
{

  SW.Send(ent->Name());

  SW.SendDerived();

  SW.Send(ent->ClosedShellElement());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWOrientedClosedShell::Share(const occ::handle<StepShape_OrientedClosedShell>& ent,
                                              Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->ClosedShellElement());
}
