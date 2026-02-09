

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWTrimmedCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_TrimmedCurve.hpp>
#include <StepGeom_TrimmingPreference.hpp>
#include <StepGeom_TrimmingSelect.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepGeom_RWTrimmingPreference.hpp"

RWStepGeom_RWTrimmedCurve::RWStepGeom_RWTrimmedCurve() = default;

void RWStepGeom_RWTrimmedCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_TrimmedCurve>&   ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "trimmed_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aBasisCurve;

  data->ReadEntity(num, 2, "basis_curve", ach, STANDARD_TYPE(StepGeom_Curve), aBasisCurve);

  occ::handle<StepGeom_CartesianPoint> aCartesianPoint;

  occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> aTrim1;
  int                                                       nsub3;
  if (data->ReadSubList(num, 3, "trim_1", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aTrim1  = new NCollection_HArray1<StepGeom_TrimmingSelect>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      StepGeom_TrimmingSelect aTrim1Item;

      if (data->ReadEntity(nsub3, i3, "trim_1", ach, aTrim1Item))
        aTrim1->SetValue(i3, aTrim1Item);
    }
  }

  occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> aTrim2;
  int                                                       nsub4;
  if (data->ReadSubList(num, 4, "trim_2", ach, nsub4))
  {
    int nb4 = data->NbParams(nsub4);
    aTrim2  = new NCollection_HArray1<StepGeom_TrimmingSelect>(1, nb4);
    for (int i4 = 1; i4 <= nb4; i4++)
    {

      StepGeom_TrimmingSelect aTrim2Item;

      if (data->ReadEntity(nsub4, i4, "trim_2", ach, aTrim2Item))
        aTrim2->SetValue(i4, aTrim2Item);
    }
  }

  bool aSenseAgreement;

  data->ReadBoolean(num, 5, "sense_agreement", ach, aSenseAgreement);

  StepGeom_TrimmingPreference aMasterRepresentation = StepGeom_tpCartesian;
  if (data->ParamType(num, 6) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 6);
    if (!RWStepGeom_RWTrimmingPreference::ConvertToEnum(text, aMasterRepresentation))
    {
      ach->AddFail("Enumeration trimming_preference has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #6 (master_representation) is not an enumeration");

  ent->Init(aName, aBasisCurve, aTrim1, aTrim2, aSenseAgreement, aMasterRepresentation);
}

void RWStepGeom_RWTrimmedCurve::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_TrimmedCurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisCurve());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbTrim1(); i2++)
  {
    SW.Send(ent->Trim1Value(i2).Value());
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbTrim2(); i3++)
  {
    SW.Send(ent->Trim2Value(i3).Value());
  }
  SW.CloseSub();

  SW.SendBoolean(ent->SenseAgreement());

  SW.SendEnum(RWStepGeom_RWTrimmingPreference::ConvertToString(ent->MasterRepresentation()));
}

void RWStepGeom_RWTrimmedCurve::Share(const occ::handle<StepGeom_TrimmedCurve>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->BasisCurve());

  int nbElem2 = ent->NbTrim1();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    if (ent->Trim1Value(is2).CaseNumber() > 0)
    {
      iter.GetOneItem(ent->Trim1Value(is2).Value());
    }
  }

  int nbElem3 = ent->NbTrim2();
  for (int is3 = 1; is3 <= nbElem3; is3++)
  {
    if (ent->Trim2Value(is3).CaseNumber() > 0)
    {
      iter.GetOneItem(ent->Trim2Value(is3).Value());
    }
  }
}
