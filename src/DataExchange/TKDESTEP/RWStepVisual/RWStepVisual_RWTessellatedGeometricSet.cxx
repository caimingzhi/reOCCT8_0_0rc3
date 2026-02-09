#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTessellatedGeometricSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TessellatedGeometricSet.hpp>
#include <StepVisual_TessellatedItem.hpp>

RWStepVisual_RWTessellatedGeometricSet::RWStepVisual_RWTessellatedGeometricSet() = default;

void RWStepVisual_RWTessellatedGeometricSet::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepVisual_TessellatedGeometricSet>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "tessellated_geometric_set"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>> anItems;
  int                                                                             nsub2;
  if (data->ReadSubList(num, 2, "items", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    anItems = new NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      occ::handle<StepVisual_TessellatedItem> anItem;
      if (data
            ->ReadEntity(nsub2, i2, "item", ach, STANDARD_TYPE(StepVisual_TessellatedItem), anItem))
        anItems->SetValue(i2, anItem);
    }
  }

  ent->Init(aName, anItems);
}

void RWStepVisual_RWTessellatedGeometricSet::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepVisual_TessellatedGeometricSet>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i = 1; i <= ent->Items()->Length(); i++)
    SW.Send(ent->Items()->Value(i));
  SW.CloseSub();
}

void RWStepVisual_RWTessellatedGeometricSet::Share(
  const occ::handle<StepVisual_TessellatedGeometricSet>& ent,
  Interface_EntityIterator&                              iter) const
{

  for (int i = 1; i <= ent->Items()->Length(); i++)
    iter.AddItem(ent->Items()->Value(i));
}
