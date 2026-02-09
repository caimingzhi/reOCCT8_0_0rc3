

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWMeasureQualification.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_MeasureQualification.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepShape_RWMeasureQualification::RWStepShape_RWMeasureQualification() = default;

void RWStepShape_RWMeasureQualification::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepShape_MeasureQualification>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "measure_qualification"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescr;
  data->ReadString(num, 2, "description", ach, aDescr);

  occ::handle<Standard_Transient> aQM;
  data->ReadEntity(num, 3, "qualified_measure", ach, STANDARD_TYPE(Standard_Transient), aQM);

  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> quals;
  int                                                        nsub4;
  if (data->ReadSubList(num, 4, "qualifiers", ach, nsub4))
  {
    int nb4 = data->NbParams(nsub4);
    quals   = new NCollection_HArray1<StepShape_ValueQualifier>(1, nb4);
    for (int i4 = 1; i4 <= nb4; i4++)
    {
      StepShape_ValueQualifier VQ;
      if (data->ReadEntity(nsub4, i4, "qualifier", ach, VQ))
        quals->SetValue(i4, VQ);
    }
  }

  ent->Init(aName, aDescr, aQM, quals);
}

void RWStepShape_RWMeasureQualification::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepShape_MeasureQualification>& ent) const
{
  SW.Send(ent->Name());
  SW.Send(ent->Description());
  SW.Send(ent->QualifiedMeasure());
  int i, nbq = ent->NbQualifiers();
  SW.OpenSub();
  for (i = 1; i <= nbq; i++)
    SW.Send(ent->QualifiersValue(i).Value());
  SW.CloseSub();
}

void RWStepShape_RWMeasureQualification::Share(
  const occ::handle<StepShape_MeasureQualification>& ent,
  Interface_EntityIterator&                          iter) const
{
  int i, nbq = ent->NbQualifiers();
  for (i = 1; i <= nbq; i++)
    iter.AddItem(ent->QualifiersValue(i).Value());
}
