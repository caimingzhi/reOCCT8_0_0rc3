

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSurfaceReplica.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_SurfaceReplica.hpp>

RWStepGeom_RWSurfaceReplica::RWStepGeom_RWSurfaceReplica() = default;

void RWStepGeom_RWSurfaceReplica::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_SurfaceReplica>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "surface_replica"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aParentSurface;

  data->ReadEntity(num, 2, "parent_surface", ach, STANDARD_TYPE(StepGeom_Surface), aParentSurface);

  occ::handle<StepGeom_CartesianTransformationOperator3d> aTransformation;

  data->ReadEntity(num,
                   3,
                   "transformation",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianTransformationOperator3d),
                   aTransformation);

  ent->Init(aName, aParentSurface, aTransformation);
}

void RWStepGeom_RWSurfaceReplica::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_SurfaceReplica>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ParentSurface());

  SW.Send(ent->Transformation());
}

void RWStepGeom_RWSurfaceReplica::Share(const occ::handle<StepGeom_SurfaceReplica>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->ParentSurface());

  iter.GetOneItem(ent->Transformation());
}
