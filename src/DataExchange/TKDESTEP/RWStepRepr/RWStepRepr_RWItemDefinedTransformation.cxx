

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWItemDefinedTransformation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepRepr_RWItemDefinedTransformation::RWStepRepr_RWItemDefinedTransformation() = default;

void RWStepRepr_RWItemDefinedTransformation::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepRepr_ItemDefinedTransformation>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "item_defined_transformation"))
    return;

  occ::handle<TCollection_HAsciiString> name, description;

  data->ReadString(num, 1, "name", ach, name);
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, description);
  }
  occ::handle<StepRepr_RepresentationItem> ti1, ti2;

  data
    ->ReadEntity(num, 3, "transform_item_1", ach, STANDARD_TYPE(StepRepr_RepresentationItem), ti1);
  data
    ->ReadEntity(num, 4, "transform_item_2", ach, STANDARD_TYPE(StepRepr_RepresentationItem), ti2);

  ent->Init(name, description, ti1, ti2);
}

void RWStepRepr_RWItemDefinedTransformation::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepRepr_ItemDefinedTransformation>& ent) const
{

  SW.Send(ent->Name());
  SW.Send(ent->Description());
  SW.Send(ent->TransformItem1());
  SW.Send(ent->TransformItem2());
}

void RWStepRepr_RWItemDefinedTransformation::Share(
  const occ::handle<StepRepr_ItemDefinedTransformation>& ent,
  Interface_EntityIterator&                              iter) const
{
  iter.AddItem(ent->TransformItem1());
  iter.AddItem(ent->TransformItem2());
}
