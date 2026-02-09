

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWQualifiedRepresentationItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_QualifiedRepresentationItem.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepShape_RWQualifiedRepresentationItem::RWStepShape_RWQualifiedRepresentationItem() = default;

void RWStepShape_RWQualifiedRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepShape_QualifiedRepresentationItem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "qualified_representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> quals;
  int                                                        nsub2;
  if (data->ReadSubList(num, 2, "qualifiers", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    quals   = new NCollection_HArray1<StepShape_ValueQualifier>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      StepShape_ValueQualifier VQ;
      if (data->ReadEntity(nsub2, i2, "qualifier", ach, VQ))
        quals->SetValue(i2, VQ);
    }
  }

  ent->Init(aName, quals);
}

void RWStepShape_RWQualifiedRepresentationItem::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepShape_QualifiedRepresentationItem>& ent) const
{

  SW.Send(ent->Name());

  int i, nbq = ent->NbQualifiers();
  SW.OpenSub();
  for (i = 1; i <= nbq; i++)
    SW.Send(ent->QualifiersValue(i).Value());
  SW.CloseSub();
}

void RWStepShape_RWQualifiedRepresentationItem::Share(
  const occ::handle<StepShape_QualifiedRepresentationItem>& ent,
  Interface_EntityIterator&                                 iter) const
{
  int i, nbq = ent->NbQualifiers();
  for (i = 1; i <= nbq; i++)
    iter.AddItem(ent->QualifiersValue(i).Value());
}
