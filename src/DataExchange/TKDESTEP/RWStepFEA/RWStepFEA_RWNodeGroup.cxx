#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWNodeGroup.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaModel.hpp>
#include <StepFEA_NodeGroup.hpp>
#include <StepFEA_NodeRepresentation.hpp>

RWStepFEA_RWNodeGroup::RWStepFEA_RWNodeGroup() = default;

void RWStepFEA_RWNodeGroup::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepFEA_NodeGroup>&       ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "node_group"))
    return;

  occ::handle<TCollection_HAsciiString> aGroup_Name;
  data->ReadString(num, 1, "group.name", ach, aGroup_Name);

  occ::handle<TCollection_HAsciiString> aGroup_Description;
  data->ReadString(num, 2, "group.description", ach, aGroup_Description);

  occ::handle<StepFEA_FeaModel> aFeaGroup_ModelRef;
  data->ReadEntity(num,
                   3,
                   "fea_group.model_ref",
                   ach,
                   STANDARD_TYPE(StepFEA_FeaModel),
                   aFeaGroup_ModelRef);

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> aNodes;
  int                                                                       sub4 = 0;
  if (data->ReadSubList(num, 4, "nodes", ach, sub4))
  {
    int nb0  = data->NbParams(sub4);
    aNodes   = new NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>(1, nb0);
    int num2 = sub4;
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

  ent->Init(aGroup_Name, aGroup_Description, aFeaGroup_ModelRef, aNodes);
}

void RWStepFEA_RWNodeGroup::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepFEA_NodeGroup>& ent) const
{

  SW.Send(ent->StepBasic_Group::Name());

  SW.Send(ent->StepBasic_Group::Description());

  SW.Send(ent->StepFEA_FeaGroup::ModelRef());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->Nodes()->Length(); i3++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->Nodes()->Value(i3);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepFEA_RWNodeGroup::Share(const occ::handle<StepFEA_NodeGroup>& ent,
                                  Interface_EntityIterator&             iter) const
{

  iter.AddItem(ent->StepFEA_FeaGroup::ModelRef());

  for (int i2 = 1; i2 <= ent->Nodes()->Length(); i2++)
  {
    occ::handle<StepFEA_NodeRepresentation> Var0 = ent->Nodes()->Value(i2);
    iter.AddItem(Var0);
  }
}
