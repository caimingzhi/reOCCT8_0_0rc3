#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWDraughtingCallout.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_DraughtingCallout.hpp>

RWStepVisual_RWDraughtingCallout::RWStepVisual_RWDraughtingCallout() = default;

void RWStepVisual_RWDraughtingCallout::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepVisual_DraughtingCallout>& ent) const
{
  if (!data->CheckNbParams(num, 2, ach, "draughting_callout"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>> aContents;
  StepVisual_DraughtingCalloutElement                                   anEnt;
  int                                                                   nbSub;
  if (data->ReadSubList(num, 2, "contents", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    aContents      = new NCollection_HArray1<StepVisual_DraughtingCalloutElement>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub, i, "content", ach, anEnt))
        aContents->SetValue(i, anEnt);
    }
  }

  ent->Init(aName, aContents);
}

void RWStepVisual_RWDraughtingCallout::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepVisual_DraughtingCallout>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbContents(); i++)
  {
    SW.Send(ent->ContentsValue(i).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWDraughtingCallout::Share(const occ::handle<StepVisual_DraughtingCallout>& ent,
                                             Interface_EntityIterator& iter) const
{

  int i, nb = ent->NbContents();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ContentsValue(i).Value());
}
