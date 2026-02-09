

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWCompoundRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_CompoundRepresentationItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWCompoundRepresentationItem::RWStepRepr_RWCompoundRepresentationItem() = default;

void RWStepRepr_RWCompoundRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepRepr_CompoundRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "compound_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems;
  occ::handle<StepRepr_RepresentationItem>                                   anent2;
  int                                                                        nsub2;
  if (data->ReadSubList(num, 2, "item_element", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aItems  = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      if (data->ReadEntity(nsub2,
                           i2,
                           "representation_item",
                           ach,
                           STANDARD_TYPE(StepRepr_RepresentationItem),
                           anent2))
        aItems->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aItems);
}

void RWStepRepr_RWCompoundRepresentationItem::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepRepr_CompoundRepresentationItem>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbItemElement(); i2++)
  {
    SW.Send(ent->ItemElementValue(i2));
  }
  SW.CloseSub();
}

void RWStepRepr_RWCompoundRepresentationItem::Share(
  const occ::handle<StepRepr_CompoundRepresentationItem>& ent,
  Interface_EntityIterator&                               iter) const
{
  int i, nb = ent->NbItemElement();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ItemElementValue(i));
}
