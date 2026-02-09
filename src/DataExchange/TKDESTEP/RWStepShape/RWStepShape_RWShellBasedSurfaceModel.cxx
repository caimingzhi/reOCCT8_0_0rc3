

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWShellBasedSurfaceModel.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Shell.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>

RWStepShape_RWShellBasedSurfaceModel::RWStepShape_RWShellBasedSurfaceModel() = default;

void RWStepShape_RWShellBasedSurfaceModel::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepShape_ShellBasedSurfaceModel>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "shell_based_surface_model"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepShape_Shell>> aSbsmBoundary;
  StepShape_Shell                                   aSbsmBoundaryItem;
  int                                               nsub2;
  if (data->ReadSubList(num, 2, "sbsm_boundary", ach, nsub2))
  {
    int nb2       = data->NbParams(nsub2);
    aSbsmBoundary = new NCollection_HArray1<StepShape_Shell>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "sbsm_boundary", ach, aSbsmBoundaryItem))
        aSbsmBoundary->SetValue(i2, aSbsmBoundaryItem);
    }
  }

  ent->Init(aName, aSbsmBoundary);
}

void RWStepShape_RWShellBasedSurfaceModel::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepShape_ShellBasedSurfaceModel>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbSbsmBoundary(); i2++)
  {
    SW.Send(ent->SbsmBoundaryValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepShape_RWShellBasedSurfaceModel::Share(
  const occ::handle<StepShape_ShellBasedSurfaceModel>& ent,
  Interface_EntityIterator&                            iter) const
{

  int nbElem1 = ent->NbSbsmBoundary();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->SbsmBoundaryValue(is1).Value());
  }
}
