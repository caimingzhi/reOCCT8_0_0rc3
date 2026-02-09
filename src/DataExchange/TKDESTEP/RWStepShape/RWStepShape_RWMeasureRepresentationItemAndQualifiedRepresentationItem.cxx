

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem.hpp>
#include <StepShape_ValueQualifier.hpp>

RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem::
  RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem() = default;

void RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                           data,
  const int                                                                             num0,
  occ::handle<Interface_Check>&                                                         ach,
  const occ::handle<StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem>& ent) const
{

  int num = 0;
  data->NamedForComplex("MEASURE_REPRESENTATION_ITEM", "MSRPIT", num0, num, ach);

  if (!data->CheckNbParams(num, 2, ach, "measure_representation_item"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);

  data->NamedForComplex("QUALIFIED_REPRESENTATION_ITEM", "QLRPIT", num0, num, ach);

  if (!data->CheckNbParams(num, 1, ach, "qualified_representation_item"))
    return;

  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> quals;
  int                                                        nsub1;
  if (data->ReadSubList(num, 1, "qualifiers", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    quals   = new NCollection_HArray1<StepShape_ValueQualifier>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {
      StepShape_ValueQualifier VQ;
      if (data->ReadEntity(nsub1, i1, "qualifier", ach, VQ))
        quals->SetValue(i1, VQ);
    }
  }

  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName, mvc, aUnitComponent, quals);
}

void RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem::WriteStep(
  StepData_StepWriter&                                                                  SW,
  const occ::handle<StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem>& ent) const
{

  SW.StartEntity("MEASURE_REPRESENTATION_ITEM");

  SW.Send(ent->Measure()->ValueComponentMember());

  SW.Send(ent->Measure()->UnitComponent().Value());

  SW.StartEntity("QUALIFIED_REPRESENTATION_ITEM");

  int i, nbq = ent->NbQualifiers();
  SW.OpenSub();
  for (i = 1; i <= nbq; i++)
    SW.Send(ent->QualifiersValue(i).Value());
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());
}

void RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem::Share(
  const occ::handle<StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem>& ent,
  Interface_EntityIterator&                                                             iter) const
{
  iter.AddItem(ent->Measure()->UnitComponent().Value());

  int i, nbq = ent->NbQualifiers();
  for (i = 1; i <= nbq; i++)
    iter.AddItem(ent->QualifiersValue(i).Value());
}
