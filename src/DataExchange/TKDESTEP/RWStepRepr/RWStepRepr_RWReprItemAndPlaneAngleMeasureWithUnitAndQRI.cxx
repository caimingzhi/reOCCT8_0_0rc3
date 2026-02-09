#include <Interface_Check.hpp>
#include "RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp>
#include <StepShape_QualifiedRepresentationItem.hpp>
#include <StepShape_ValueQualifier.hpp>

RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI::
  RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI() = default;

void RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI::ReadStep(
  const occ::handle<StepData_StepReaderData>&                             data,
  const int                                                               num0,
  occ::handle<Interface_Check>&                                           ach,
  const occ::handle<StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI>& ent) const
{
  int num = 0;
  data->NamedForComplex("MEASURE_WITH_UNIT", "MSWTUN", num0, num, ach);
  if (!data->CheckNbParams(num, 2, ach, "measure_with_unit"))
    return;

  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 1, "value_component", ach, mvc);

  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 2, "unit_component", ach, aUnitComponent);
  occ::handle<StepBasic_MeasureWithUnit> aMeasureWithUnit = new StepBasic_MeasureWithUnit;
  aMeasureWithUnit->Init(mvc, aUnitComponent);

  data->NamedForComplex("QUALIFIED_REPRESENTATION_ITEM", "QLRPIT", num0, num, ach);
  if (!data->CheckNbParams(num, 1, ach, "qualified_representation_item"))
    return;

  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> quals;
  int                                                        nsub;
  if (data->ReadSubList(num, 1, "qualifiers", ach, nsub))
  {
    int nb = data->NbParams(nsub);
    quals  = new NCollection_HArray1<StepShape_ValueQualifier>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      StepShape_ValueQualifier aVQ;
      if (data->ReadEntity(nsub, i, "qualifier", ach, aVQ))
        quals->SetValue(i, aVQ);
    }
  }
  occ::handle<StepShape_QualifiedRepresentationItem> aQRI =
    new StepShape_QualifiedRepresentationItem();
  aQRI->SetQualifiers(quals);

  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);
  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);
  occ::handle<StepRepr_RepresentationItem> aReprItem = new StepRepr_RepresentationItem;
  aReprItem->Init(aName);

  ent->Init(aMeasureWithUnit, aReprItem, aQRI);
}

void RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI::WriteStep(
  StepData_StepWriter&                                                    SW,
  const occ::handle<StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI>& ent) const
{
  SW.StartEntity("MEASURE_REPRESENTATION_ITEM");
  SW.StartEntity("MEASURE_WITH_UNIT");
  SW.Send(ent->GetMeasureWithUnit()->ValueComponentMember());
  SW.Send(ent->GetMeasureWithUnit()->UnitComponent().Value());
  SW.StartEntity("PLANE_ANGLE_MEASURE_WITH_UNIT");
  SW.StartEntity("QUALIFIED_REPRESENTATION_ITEM");
  occ::handle<StepShape_QualifiedRepresentationItem> aQRI = ent->GetQualifiedRepresentationItem();
  int                                                i, nbq = aQRI->NbQualifiers();
  SW.OpenSub();
  for (i = 1; i <= nbq; i++)
    SW.Send(aQRI->QualifiersValue(i).Value());
  SW.CloseSub();
  SW.StartEntity("REPRESENTATION_ITEM");
  SW.Send(ent->Name());
}
