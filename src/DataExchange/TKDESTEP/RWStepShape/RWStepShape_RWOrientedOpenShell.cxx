

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWOrientedOpenShell.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_OrientedOpenShell.hpp>

RWStepShape_RWOrientedOpenShell::RWStepShape_RWOrientedOpenShell() = default;

void RWStepShape_RWOrientedOpenShell::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_OrientedOpenShell>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "oriented_open_shell"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  data->CheckDerived(num, 2, "cfs_faces", ach, false);

  occ::handle<StepShape_OpenShell> aOpenShellElement;

  data->ReadEntity(num,
                   3,
                   "open_shell_element",
                   ach,
                   STANDARD_TYPE(StepShape_OpenShell),
                   aOpenShellElement);

  bool aOrientation;

  data->ReadBoolean(num, 4, "orientation", ach, aOrientation);

  ent->Init(aName, aOpenShellElement, aOrientation);
}

void RWStepShape_RWOrientedOpenShell::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_OrientedOpenShell>& ent) const
{

  SW.Send(ent->Name());

  SW.SendDerived();

  SW.Send(ent->OpenShellElement());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWOrientedOpenShell::Share(const occ::handle<StepShape_OrientedOpenShell>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->OpenShellElement());
}
