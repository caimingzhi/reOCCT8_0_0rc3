#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSubedge.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Subedge.hpp>
#include <StepShape_Vertex.hpp>

RWStepShape_RWSubedge::RWStepShape_RWSubedge() = default;

void RWStepShape_RWSubedge::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepShape_Subedge>&       ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "subedge"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepShape_Vertex> aEdge_EdgeStart;
  data
    ->ReadEntity(num, 2, "edge.edge_start", ach, STANDARD_TYPE(StepShape_Vertex), aEdge_EdgeStart);

  occ::handle<StepShape_Vertex> aEdge_EdgeEnd;
  data->ReadEntity(num, 3, "edge.edge_end", ach, STANDARD_TYPE(StepShape_Vertex), aEdge_EdgeEnd);

  occ::handle<StepShape_Edge> aParentEdge;
  data->ReadEntity(num, 4, "parent_edge", ach, STANDARD_TYPE(StepShape_Edge), aParentEdge);

  ent->Init(aRepresentationItem_Name, aEdge_EdgeStart, aEdge_EdgeEnd, aParentEdge);
}

void RWStepShape_RWSubedge::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepShape_Subedge>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->StepShape_Edge::EdgeStart());

  SW.Send(ent->StepShape_Edge::EdgeEnd());

  SW.Send(ent->ParentEdge());
}

void RWStepShape_RWSubedge::Share(const occ::handle<StepShape_Subedge>& ent,
                                  Interface_EntityIterator&             iter) const
{

  iter.AddItem(ent->StepShape_Edge::EdgeStart());

  iter.AddItem(ent->StepShape_Edge::EdgeEnd());

  iter.AddItem(ent->ParentEdge());
}
