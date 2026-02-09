

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCurveReplica.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_CurveReplica.hpp>

RWStepGeom_RWCurveReplica::RWStepGeom_RWCurveReplica() = default;

void RWStepGeom_RWCurveReplica::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_CurveReplica>&   ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "curve_replica"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aParentCurve;

  data->ReadEntity(num, 2, "parent_curve", ach, STANDARD_TYPE(StepGeom_Curve), aParentCurve);

  occ::handle<StepGeom_CartesianTransformationOperator> aTransformation;

  data->ReadEntity(num,
                   3,
                   "transformation",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianTransformationOperator),
                   aTransformation);

  ent->Init(aName, aParentCurve, aTransformation);
}

void RWStepGeom_RWCurveReplica::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_CurveReplica>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ParentCurve());

  SW.Send(ent->Transformation());
}

void RWStepGeom_RWCurveReplica::Share(const occ::handle<StepGeom_CurveReplica>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->ParentCurve());

  iter.GetOneItem(ent->Transformation());
}
