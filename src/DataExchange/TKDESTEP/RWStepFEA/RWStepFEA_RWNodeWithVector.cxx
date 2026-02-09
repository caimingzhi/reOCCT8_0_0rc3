#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWNodeWithVector.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaModel.hpp>
#include <StepFEA_NodeWithVector.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>

RWStepFEA_RWNodeWithVector::RWStepFEA_RWNodeWithVector() = default;

void RWStepFEA_RWNodeWithVector::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepFEA_NodeWithVector>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "node_with_vector"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentation_Name;
  data->ReadString(num, 1, "representation.name", ach, aRepresentation_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aRepresentation_Items;
  int                                                                        sub2 = 0;
  if (data->ReadSubList(num, 2, "representation.items", ach, sub2))
  {
    int nb0 = data->NbParams(sub2);
    aRepresentation_Items =
      new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepRepr_RepresentationItem> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "representation_item",
                       ach,
                       STANDARD_TYPE(StepRepr_RepresentationItem),
                       anIt0);
      aRepresentation_Items->SetValue(i0, anIt0);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aRepresentation_ContextOfItems;
  data->ReadEntity(num,
                   3,
                   "representation.context_of_items",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationContext),
                   aRepresentation_ContextOfItems);

  occ::handle<StepFEA_FeaModel> aNodeRepresentation_ModelRef;
  data->ReadEntity(num,
                   4,
                   "node_representation.model_ref",
                   ach,
                   STANDARD_TYPE(StepFEA_FeaModel),
                   aNodeRepresentation_ModelRef);

  ent->Init(aRepresentation_Name,
            aRepresentation_Items,
            aRepresentation_ContextOfItems,
            aNodeRepresentation_ModelRef);
}

void RWStepFEA_RWNodeWithVector::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepFEA_NodeWithVector>& ent) const
{

  SW.Send(ent->StepRepr_Representation::Name());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->StepRepr_Representation::NbItems(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 =
      ent->StepRepr_Representation::Items()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();

  SW.Send(ent->StepRepr_Representation::ContextOfItems());

  SW.Send(ent->StepFEA_NodeRepresentation::ModelRef());
}

void RWStepFEA_RWNodeWithVector::Share(const occ::handle<StepFEA_NodeWithVector>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  for (int i1 = 1; i1 <= ent->StepRepr_Representation::NbItems(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 =
      ent->StepRepr_Representation::Items()->Value(i1);
    iter.AddItem(Var0);
  }

  iter.AddItem(ent->StepRepr_Representation::ContextOfItems());

  iter.AddItem(ent->StepFEA_NodeRepresentation::ModelRef());
}
