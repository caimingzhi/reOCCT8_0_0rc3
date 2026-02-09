

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPointReplica.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_PointReplica.hpp>

RWStepGeom_RWPointReplica::RWStepGeom_RWPointReplica() = default;

void RWStepGeom_RWPointReplica::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_PointReplica>&   ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "point_replica"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Point> aParentPt;

  data->ReadEntity(num, 2, "parent_pt", ach, STANDARD_TYPE(StepGeom_Point), aParentPt);

  occ::handle<StepGeom_CartesianTransformationOperator> aTransformation;

  data->ReadEntity(num,
                   3,
                   "transformation",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianTransformationOperator),
                   aTransformation);

  ent->Init(aName, aParentPt, aTransformation);
}

void RWStepGeom_RWPointReplica::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_PointReplica>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ParentPt());

  SW.Send(ent->Transformation());
}

void RWStepGeom_RWPointReplica::Share(const occ::handle<StepGeom_PointReplica>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->ParentPt());

  iter.GetOneItem(ent->Transformation());
}
