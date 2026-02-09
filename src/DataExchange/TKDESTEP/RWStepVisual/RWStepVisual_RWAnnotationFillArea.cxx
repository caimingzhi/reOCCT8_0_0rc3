#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWAnnotationFillArea.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_AnnotationFillArea.hpp>
#include <StepShape_GeometricSetSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWAnnotationFillArea::RWStepVisual_RWAnnotationFillArea() = default;

void RWStepVisual_RWAnnotationFillArea::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepVisual_AnnotationFillArea>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "annotation_fill_area"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> aElements;
  StepShape_GeometricSetSelect                                   aElementsItem;
  int                                                            nsub;
  if (data->ReadSubList(num, 2, "boundaries", ach, nsub))
  {
    int nb    = data->NbParams(nsub);
    aElements = new NCollection_HArray1<StepShape_GeometricSetSelect>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      if (data->ReadEntity(nsub, i, "boundaries", ach, aElementsItem))
        aElements->SetValue(i, aElementsItem);
    }
  }

  ent->Init(aName, aElements);
}

void RWStepVisual_RWAnnotationFillArea::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepVisual_AnnotationFillArea>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbElements(); i++)
  {
    SW.Send(ent->ElementsValue(i).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWAnnotationFillArea::Share(const occ::handle<StepVisual_AnnotationFillArea>& ent,
                                              Interface_EntityIterator& iter) const
{
  int nbBound = ent->NbElements();
  for (int i = 1; i <= nbBound; i++)
  {
    iter.GetOneItem(ent->ElementsValue(i).Value());
  }
}
