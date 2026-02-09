

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWGeometricCurveSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_GeometricCurveSet.hpp>
#include <StepShape_GeometricSetSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWGeometricCurveSet::RWStepShape_RWGeometricCurveSet() = default;

void RWStepShape_RWGeometricCurveSet::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_GeometricCurveSet>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "geometric_curve_set"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> aElements;
  StepShape_GeometricSetSelect                                   aElementsItem;
  int                                                            nsub2;
  if (data->ReadSubList(num, 2, "elements", ach, nsub2))
  {
    int nb2   = data->NbParams(nsub2);
    aElements = new NCollection_HArray1<StepShape_GeometricSetSelect>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "elements", ach, aElementsItem))
        aElements->SetValue(i2, aElementsItem);
    }
  }

  ent->Init(aName, aElements);
}

void RWStepShape_RWGeometricCurveSet::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_GeometricCurveSet>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbElements(); i2++)
  {
    SW.Send(ent->ElementsValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepShape_RWGeometricCurveSet::Share(const occ::handle<StepShape_GeometricCurveSet>& ent,
                                            Interface_EntityIterator& iter) const
{

  int nbElem1 = ent->NbElements();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ElementsValue(is1).Value());
  }
}
