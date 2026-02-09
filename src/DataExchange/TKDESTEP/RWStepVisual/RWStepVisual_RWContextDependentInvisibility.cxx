

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWContextDependentInvisibility.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_ContextDependentInvisibility.hpp>
#include <StepVisual_InvisibleItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_InvisibilityContext.hpp>

RWStepVisual_RWContextDependentInvisibility::RWStepVisual_RWContextDependentInvisibility() =
  default;

void RWStepVisual_RWContextDependentInvisibility::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepVisual_ContextDependentInvisibility>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "context_dependent_invisibility"))
    return;

  occ::handle<NCollection_HArray1<StepVisual_InvisibleItem>> aInvisibleItems;
  StepVisual_InvisibleItem                                   aInvisibleItemsItem;
  int                                                        nsub1;
  if (data->ReadSubList(num, 1, "invisible_items", ach, nsub1))
  {
    int nb1         = data->NbParams(nsub1);
    aInvisibleItems = new NCollection_HArray1<StepVisual_InvisibleItem>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {

      if (data->ReadEntity(nsub1, i1, "invisible_items", ach, aInvisibleItemsItem))
        aInvisibleItems->SetValue(i1, aInvisibleItemsItem);
    }
  }

  StepVisual_InvisibilityContext aPresentationContext;

  data->ReadEntity(num, 2, "presentation_context", ach, aPresentationContext);

  ent->Init(aInvisibleItems, aPresentationContext);
}

void RWStepVisual_RWContextDependentInvisibility::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepVisual_ContextDependentInvisibility>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbInvisibleItems(); i1++)
  {
    SW.Send(ent->InvisibleItemsValue(i1).Value());
  }
  SW.CloseSub();

  SW.Send(ent->PresentationContext().Value());
}

void RWStepVisual_RWContextDependentInvisibility::Share(
  const occ::handle<StepVisual_ContextDependentInvisibility>& ent,
  Interface_EntityIterator&                                   iter) const
{

  int nbElem1 = ent->NbInvisibleItems();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->InvisibleItemsValue(is1).Value());
  }

  iter.GetOneItem(ent->PresentationContext().Value());
}
