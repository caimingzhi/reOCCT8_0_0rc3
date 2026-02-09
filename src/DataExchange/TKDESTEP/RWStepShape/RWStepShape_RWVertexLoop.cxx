

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWVertexLoop.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Vertex.hpp>
#include <StepShape_VertexLoop.hpp>

RWStepShape_RWVertexLoop::RWStepShape_RWVertexLoop() = default;

void RWStepShape_RWVertexLoop::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepShape_VertexLoop>&    ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "vertex_loop"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_Vertex> aLoopVertex;

  data->ReadEntity(num, 2, "loop_vertex", ach, STANDARD_TYPE(StepShape_Vertex), aLoopVertex);

  ent->Init(aName, aLoopVertex);
}

void RWStepShape_RWVertexLoop::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepShape_VertexLoop>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->LoopVertex());
}

void RWStepShape_RWVertexLoop::Share(const occ::handle<StepShape_VertexLoop>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->LoopVertex());
}
