

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCompositeTextWithExtent.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CompositeTextWithExtent.hpp>
#include <StepVisual_TextOrCharacter.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_PlanarExtent.hpp>

RWStepVisual_RWCompositeTextWithExtent::RWStepVisual_RWCompositeTextWithExtent() = default;

void RWStepVisual_RWCompositeTextWithExtent::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepVisual_CompositeTextWithExtent>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "composite_text_with_extent has not 3 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>> aCollectedText;
  StepVisual_TextOrCharacter                                   aCollectedTextItem;
  int                                                          nsub2;
  nsub2 = data->SubListNumber(num, 2, false);
  if (nsub2 != 0)
  {
    int nb2        = data->NbParams(nsub2);
    aCollectedText = new NCollection_HArray1<StepVisual_TextOrCharacter>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "collected_text", ach, aCollectedTextItem))
        aCollectedText->SetValue(i2, aCollectedTextItem);
    }
  }
  else
  {
    ach->AddFail("Parameter #2 (collected_text) is not a LIST");
  }

  occ::handle<StepVisual_PlanarExtent> aExtent;

  data->ReadEntity(num, 3, "extent", ach, STANDARD_TYPE(StepVisual_PlanarExtent), aExtent);

  ent->Init(aName, aCollectedText, aExtent);
}

void RWStepVisual_RWCompositeTextWithExtent::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepVisual_CompositeTextWithExtent>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbCollectedText(); i2++)
  {
    SW.Send(ent->CollectedTextValue(i2).Value());
  }
  SW.CloseSub();

  SW.Send(ent->Extent());
}

void RWStepVisual_RWCompositeTextWithExtent::Share(
  const occ::handle<StepVisual_CompositeTextWithExtent>& ent,
  Interface_EntityIterator&                              iter) const
{

  int nbElem1 = ent->NbCollectedText();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->CollectedTextValue(is1).Value());
  }

  iter.GetOneItem(ent->Extent());
}
