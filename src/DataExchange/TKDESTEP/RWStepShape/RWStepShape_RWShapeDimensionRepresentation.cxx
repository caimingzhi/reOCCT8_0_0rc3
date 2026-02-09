#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWShapeDimensionRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepShape_ShapeDimensionRepresentation.hpp>

RWStepShape_RWShapeDimensionRepresentation::RWStepShape_RWShapeDimensionRepresentation() = default;

void RWStepShape_RWShapeDimensionRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                data,
  const int                                                  num,
  occ::handle<Interface_Check>&                              ach,
  const occ::handle<StepShape_ShapeDimensionRepresentation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "shape_dimension_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentation_Name;
  data->ReadString(num, 1, "representation.name", ach, aRepresentation_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aRepresentation_Items;
  occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>> anItems;
  int                                                                          sub2 = 0;
  if (data->ReadSubList(num, 2, "representation.items", ach, sub2))
  {
    int                                        num2 = sub2;
    int                                        nb0  = data->NbParams(num2);
    occ::handle<StepRepr_RepresentationItem>   anIt0;
    StepShape_ShapeDimensionRepresentationItem anIt0AP242;
    if (data->ReadEntity(num2,
                         1,
                         "representation.items",
                         ach,
                         STANDARD_TYPE(StepRepr_RepresentationItem),
                         anIt0))
    {
      aRepresentation_Items =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb0);
      for (int i0 = 1; i0 <= nb0; i0++)
      {
        data->ReadEntity(num2,
                         i0,
                         "representation.items",
                         ach,
                         STANDARD_TYPE(StepRepr_RepresentationItem),
                         anIt0);
        aRepresentation_Items->SetValue(i0, anIt0);
      }
    }
    else
    {
      anItems = new NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>(1, nb0);
      for (int i0 = 1; i0 <= nb0; i0++)
      {
        data->ReadEntity(num2, i0, "representation.items", ach, anIt0AP242);
        anItems->SetValue(i0, anIt0AP242);
      }
    }
  }

  occ::handle<StepRepr_RepresentationContext> aRepresentation_ContextOfItems;
  data->ReadEntity(num,
                   3,
                   "representation.context_of_items",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationContext),
                   aRepresentation_ContextOfItems);

  if (anItems.IsNull())
  {
    ent->Init(aRepresentation_Name, aRepresentation_Items, aRepresentation_ContextOfItems);
  }
  else
  {
    ent->Init(aRepresentation_Name, anItems, aRepresentation_ContextOfItems);
  }
}

void RWStepShape_RWShapeDimensionRepresentation::WriteStep(
  StepData_StepWriter&                                       SW,
  const occ::handle<StepShape_ShapeDimensionRepresentation>& ent) const
{

  SW.Send(ent->StepRepr_Representation::Name());

  SW.OpenSub();
  if (ent->ItemsAP242().IsNull())
  {
    for (int i1 = 1; i1 <= ent->StepRepr_Representation::NbItems(); i1++)
    {
      occ::handle<StepRepr_RepresentationItem> Var0 =
        ent->StepRepr_Representation::Items()->Value(i1);
      SW.Send(Var0);
    }
  }
  else
  {
    for (int i1 = 1; i1 <= ent->ItemsAP242()->Length(); i1++)
    {
      StepShape_ShapeDimensionRepresentationItem Var0 = ent->ItemsAP242()->Value(i1);
      SW.Send(Var0.Value());
    }
  }
  SW.CloseSub();

  SW.Send(ent->StepRepr_Representation::ContextOfItems());
}

void RWStepShape_RWShapeDimensionRepresentation::Share(
  const occ::handle<StepShape_ShapeDimensionRepresentation>& ent,
  Interface_EntityIterator&                                  iter) const
{

  if (ent->ItemsAP242().IsNull())
  {
    for (int i1 = 1; i1 <= ent->StepRepr_Representation::NbItems(); i1++)
    {
      occ::handle<StepRepr_RepresentationItem> Var0 =
        ent->StepRepr_Representation::Items()->Value(i1);
      iter.AddItem(Var0);
    }
  }
  else
  {
    for (int i1 = 1; i1 <= ent->ItemsAP242()->Length(); i1++)
    {
      StepShape_ShapeDimensionRepresentationItem Var0 = ent->ItemsAP242()->Value(i1);
      iter.AddItem(Var0.Value());
    }
  }

  iter.AddItem(ent->StepRepr_Representation::ContextOfItems());
}
