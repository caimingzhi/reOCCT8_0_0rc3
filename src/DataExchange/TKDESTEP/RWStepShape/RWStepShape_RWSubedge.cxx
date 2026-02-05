#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSubedge.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Subedge.hpp>
#include <StepShape_Vertex.hpp>

//=================================================================================================

RWStepShape_RWSubedge::RWStepShape_RWSubedge() = default;

//=================================================================================================

void RWStepShape_RWSubedge::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepShape_Subedge>&       ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "subedge"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Inherited fields of Edge

  occ::handle<StepShape_Vertex> aEdge_EdgeStart;
  data
    ->ReadEntity(num, 2, "edge.edge_start", ach, STANDARD_TYPE(StepShape_Vertex), aEdge_EdgeStart);

  occ::handle<StepShape_Vertex> aEdge_EdgeEnd;
  data->ReadEntity(num, 3, "edge.edge_end", ach, STANDARD_TYPE(StepShape_Vertex), aEdge_EdgeEnd);

  // Own fields of Subedge

  occ::handle<StepShape_Edge> aParentEdge;
  data->ReadEntity(num, 4, "parent_edge", ach, STANDARD_TYPE(StepShape_Edge), aParentEdge);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aEdge_EdgeStart, aEdge_EdgeEnd, aParentEdge);
}

//=================================================================================================

void RWStepShape_RWSubedge::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepShape_Subedge>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Inherited fields of Edge

  SW.Send(ent->StepShape_Edge::EdgeStart());

  SW.Send(ent->StepShape_Edge::EdgeEnd());

  // Own fields of Subedge

  SW.Send(ent->ParentEdge());
}

//=================================================================================================

void RWStepShape_RWSubedge::Share(const occ::handle<StepShape_Subedge>& ent,
                                  Interface_EntityIterator&             iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of Edge

  iter.AddItem(ent->StepShape_Edge::EdgeStart());

  iter.AddItem(ent->StepShape_Edge::EdgeEnd());

  // Own fields of Subedge

  iter.AddItem(ent->ParentEdge());
}
