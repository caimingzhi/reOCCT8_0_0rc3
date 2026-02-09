

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWVertexPoint.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Point.hpp>
#include <StepShape_VertexPoint.hpp>

RWStepShape_RWVertexPoint::RWStepShape_RWVertexPoint() = default;

void RWStepShape_RWVertexPoint::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepShape_VertexPoint>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "vertex_point"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Point> aVertexGeometry;

  data->ReadEntity(num, 2, "vertex_geometry", ach, STANDARD_TYPE(StepGeom_Point), aVertexGeometry);

  ent->Init(aName, aVertexGeometry);
}

void RWStepShape_RWVertexPoint::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepShape_VertexPoint>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->VertexGeometry());
}

void RWStepShape_RWVertexPoint::Share(const occ::handle<StepShape_VertexPoint>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->VertexGeometry());
}
