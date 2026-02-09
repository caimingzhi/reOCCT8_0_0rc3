#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaGroup.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaGroup.hpp>
#include <StepFEA_FeaModel.hpp>

RWStepFEA_RWFeaGroup::RWStepFEA_RWFeaGroup() = default;

void RWStepFEA_RWFeaGroup::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepFEA_FeaGroup>&        ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "fea_group"))
    return;

  occ::handle<TCollection_HAsciiString> aGroup_Name;
  data->ReadString(num, 1, "group.name", ach, aGroup_Name);

  occ::handle<TCollection_HAsciiString> aGroup_Description;
  data->ReadString(num, 2, "group.description", ach, aGroup_Description);

  occ::handle<StepFEA_FeaModel> aModelRef;
  data->ReadEntity(num, 3, "model_ref", ach, STANDARD_TYPE(StepFEA_FeaModel), aModelRef);

  ent->Init(aGroup_Name, aGroup_Description, aModelRef);
}

void RWStepFEA_RWFeaGroup::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepFEA_FeaGroup>& ent) const
{

  SW.Send(ent->StepBasic_Group::Name());

  SW.Send(ent->StepBasic_Group::Description());

  SW.Send(ent->ModelRef());
}

void RWStepFEA_RWFeaGroup::Share(const occ::handle<StepFEA_FeaGroup>& ent,
                                 Interface_EntityIterator&            iter) const
{

  iter.AddItem(ent->ModelRef());
}
