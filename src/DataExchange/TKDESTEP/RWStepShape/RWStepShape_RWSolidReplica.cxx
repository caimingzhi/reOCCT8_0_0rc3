

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSolidReplica.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepShape_SolidReplica.hpp>

RWStepShape_RWSolidReplica::RWStepShape_RWSolidReplica() = default;

void RWStepShape_RWSolidReplica::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepShape_SolidReplica>&  ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "solid_replica"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_SolidModel> aParentSolid;

  data->ReadEntity(num, 2, "parent_solid", ach, STANDARD_TYPE(StepShape_SolidModel), aParentSolid);

  occ::handle<StepGeom_CartesianTransformationOperator3d> aTransformation;

  data->ReadEntity(num,
                   3,
                   "transformation",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianTransformationOperator3d),
                   aTransformation);

  ent->Init(aName, aParentSolid, aTransformation);
}

void RWStepShape_RWSolidReplica::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepShape_SolidReplica>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ParentSolid());

  SW.Send(ent->Transformation());
}

void RWStepShape_RWSolidReplica::Share(const occ::handle<StepShape_SolidReplica>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->ParentSolid());

  iter.GetOneItem(ent->Transformation());
}
