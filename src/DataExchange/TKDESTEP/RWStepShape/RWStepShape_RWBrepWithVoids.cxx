

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepShape_RWBrepWithVoids.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWBrepWithVoids::RWStepShape_RWBrepWithVoids() = default;

void RWStepShape_RWBrepWithVoids::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepShape_BrepWithVoids>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "brep_with_voids"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_ClosedShell> aOuter;

  data->ReadEntity(num, 2, "outer", ach, STANDARD_TYPE(StepShape_ClosedShell), aOuter);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>> aVoids;
  occ::handle<StepShape_OrientedClosedShell>                                   anent3;
  int                                                                          nsub3;
  if (data->ReadSubList(num, 3, "voids", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aVoids  = new NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3,
                           i3,
                           "oriented_closed_shell",
                           ach,
                           STANDARD_TYPE(StepShape_OrientedClosedShell),
                           anent3))
        aVoids->SetValue(i3, anent3);
    }
  }

  ent->Init(aName, aOuter, aVoids);
}

void RWStepShape_RWBrepWithVoids::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepShape_BrepWithVoids>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Outer());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbVoids(); i3++)
  {
    SW.Send(ent->VoidsValue(i3));
  }
  SW.CloseSub();
}

void RWStepShape_RWBrepWithVoids::Share(const occ::handle<StepShape_BrepWithVoids>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->Outer());

  int nbElem2 = ent->NbVoids();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->VoidsValue(is2));
  }
}

void RWStepShape_RWBrepWithVoids::Check(const occ::handle<StepShape_BrepWithVoids>& ent,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>& ach) const
{
  for (int i = 1; i <= ent->NbVoids(); i++)
    if (ent->VoidsValue(i)->Orientation())
    {
      ach->AddWarning("Void has orientation .T. while .F. is required by API 214");
      break;
    }
}
