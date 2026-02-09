

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWEdge.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Edge.hpp>
#include <StepShape_Vertex.hpp>

RWStepShape_RWEdge::RWStepShape_RWEdge() = default;

void RWStepShape_RWEdge::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepShape_Edge>&          ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "edge"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_Vertex> aEdgeStart;

  data->ReadEntity(num, 2, "edge_start", ach, STANDARD_TYPE(StepShape_Vertex), aEdgeStart);

  occ::handle<StepShape_Vertex> aEdgeEnd;

  data->ReadEntity(num, 3, "edge_end", ach, STANDARD_TYPE(StepShape_Vertex), aEdgeEnd);

  ent->Init(aName, aEdgeStart, aEdgeEnd);
}

void RWStepShape_RWEdge::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepShape_Edge>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->EdgeStart());

  SW.Send(ent->EdgeEnd());
}

void RWStepShape_RWEdge::Share(const occ::handle<StepShape_Edge>& ent,
                               Interface_EntityIterator&          iter) const
{

  iter.GetOneItem(ent->EdgeStart());

  iter.GetOneItem(ent->EdgeEnd());
}
