

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWContextDependentOverRidingStyledItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_ContextDependentOverRidingStyledItem.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_StyleContextSelect.hpp>
#include <StepVisual_StyledItem.hpp>

RWStepVisual_RWContextDependentOverRidingStyledItem::
  RWStepVisual_RWContextDependentOverRidingStyledItem() = default;

void RWStepVisual_RWContextDependentOverRidingStyledItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                         data,
  const int                                                           num,
  occ::handle<Interface_Check>&                                       ach,
  const occ::handle<StepVisual_ContextDependentOverRidingStyledItem>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "context_dependent_over_riding_styled_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> aStyles;
  occ::handle<StepVisual_PresentationStyleAssignment>                                   anent2;
  int                                                                                   nsub2;
  if (data->ReadSubList(num, 2, "styles", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aStyles = new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "presentation_style_assignment",
                           ach,
                           STANDARD_TYPE(StepVisual_PresentationStyleAssignment),
                           anent2))
        aStyles->SetValue(i2, anent2);
    }
  }

  occ::handle<Standard_Transient> aItem;
  data->ReadEntity(num, 3, "item", ach, STANDARD_TYPE(Standard_Transient), aItem);

  occ::handle<StepVisual_StyledItem> aOverRiddenStyle;

  data->ReadEntity(num,
                   4,
                   "over_ridden_style",
                   ach,
                   STANDARD_TYPE(StepVisual_StyledItem),
                   aOverRiddenStyle);

  occ::handle<NCollection_HArray1<StepVisual_StyleContextSelect>> aStyleContext;
  StepVisual_StyleContextSelect                                   aStyleContextItem;
  int                                                             nsub5;
  if (data->ReadSubList(num, 5, "style_context", ach, nsub5))
  {
    int nb5       = data->NbParams(nsub5);
    aStyleContext = new NCollection_HArray1<StepVisual_StyleContextSelect>(1, nb5);
    for (int i5 = 1; i5 <= nb5; i5++)
    {

      if (data->ReadEntity(nsub5, i5, "style_context", ach, aStyleContextItem))
        aStyleContext->SetValue(i5, aStyleContextItem);
    }
  }
  else
  {
    aStyleContext = new NCollection_HArray1<StepVisual_StyleContextSelect>();
  }

  ent->Init(aName, aStyles, aItem, aOverRiddenStyle, aStyleContext);
}

void RWStepVisual_RWContextDependentOverRidingStyledItem::WriteStep(
  StepData_StepWriter&                                                SW,
  const occ::handle<StepVisual_ContextDependentOverRidingStyledItem>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbStyles(); i2++)
  {
    SW.Send(ent->StylesValue(i2));
  }
  SW.CloseSub();

  SW.Send(ent->Item());

  SW.Send(ent->OverRiddenStyle());

  SW.OpenSub();
  for (int i5 = 1; i5 <= ent->NbStyleContext(); i5++)
  {
    SW.Send(ent->StyleContextValue(i5).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWContextDependentOverRidingStyledItem::Share(
  const occ::handle<StepVisual_ContextDependentOverRidingStyledItem>& ent,
  Interface_EntityIterator&                                           iter) const
{

  int nbElem1 = ent->NbStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->StylesValue(is1));
  }

  iter.GetOneItem(ent->Item());

  iter.GetOneItem(ent->OverRiddenStyle());

  int nbElem4 = ent->NbStyleContext();
  for (int is4 = 1; is4 <= nbElem4; is4++)
  {
    iter.GetOneItem(ent->StyleContextValue(is4).Value());
  }
}
