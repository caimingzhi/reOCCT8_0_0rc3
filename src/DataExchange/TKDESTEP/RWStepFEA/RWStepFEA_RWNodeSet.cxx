#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWNodeSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_NodeRepresentation.hpp>
#include <StepFEA_NodeSet.hpp>

//=================================================================================================

RWStepFEA_RWNodeSet::RWStepFEA_RWNodeSet() = default;

//=================================================================================================

void RWStepFEA_RWNodeSet::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepFEA_NodeSet>&         ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "node_set"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of NodeSet

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> aNodes;
  int                                                                       sub2 = 0;
  if (data->ReadSubList(num, 2, "nodes", ach, sub2))
  {
    int nb0  = data->NbParams(sub2);
    aNodes   = new NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepFEA_NodeRepresentation> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "node_representation",
                       ach,
                       STANDARD_TYPE(StepFEA_NodeRepresentation),
                       anIt0);
      aNodes->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aNodes);
}

//=================================================================================================

void RWStepFEA_RWNodeSet::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepFEA_NodeSet>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of NodeSet

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Nodes()->Length(); i1++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->Nodes()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepFEA_RWNodeSet::Share(const occ::handle<StepFEA_NodeSet>& ent,
                                Interface_EntityIterator&           iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of NodeSet

  for (int i1 = 1; i1 <= ent->Nodes()->Length(); i1++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->Nodes()->Value(i1);
    iter.AddItem(Var0);
  }
}
