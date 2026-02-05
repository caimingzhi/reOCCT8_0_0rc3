#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWElementRepresentation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_ElementRepresentation.hpp>
#include <StepFEA_NodeRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationContext.hpp>

//=================================================================================================

RWStepFEA_RWElementRepresentation::RWStepFEA_RWElementRepresentation() = default;

//=================================================================================================

void RWStepFEA_RWElementRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepFEA_ElementRepresentation>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "element_representation"))
    return;

  // Inherited fields of Representation

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

  // Own fields of ElementRepresentation

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> aNodeList;
  int                                                                       sub4 = 0;
  if (data->ReadSubList(num, 4, "node_list", ach, sub4))
  {
    int nb0   = data->NbParams(sub4);
    aNodeList = new NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>(1, nb0);
    int num2  = sub4;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepFEA_NodeRepresentation> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "node_representation",
                       ach,
                       STANDARD_TYPE(StepFEA_NodeRepresentation),
                       anIt0);
      aNodeList->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aRepresentation_Name, aRepresentation_Items, aRepresentation_ContextOfItems, aNodeList);
}

//=================================================================================================

void RWStepFEA_RWElementRepresentation::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepFEA_ElementRepresentation>& ent) const
{

  // Inherited fields of Representation

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

  // Own fields of ElementRepresentation

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NodeList()->Length(); i3++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->NodeList()->Value(i3);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepFEA_RWElementRepresentation::Share(const occ::handle<StepFEA_ElementRepresentation>& ent,
                                              Interface_EntityIterator& iter) const
{

  // Inherited fields of Representation

  for (int i1 = 1; i1 <= ent->StepRepr_Representation::NbItems(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 =
      ent->StepRepr_Representation::Items()->Value(i1);
    iter.AddItem(Var0);
  }

  iter.AddItem(ent->StepRepr_Representation::ContextOfItems());

  // Own fields of ElementRepresentation

  for (int i3 = 1; i3 <= ent->NodeList()->Length(); i3++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->NodeList()->Value(i3);
    iter.AddItem(Var0);
  }
}
