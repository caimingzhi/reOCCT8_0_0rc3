#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSeamEdge.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepShape_SeamEdge.hpp>
#include <StepShape_Vertex.hpp>

RWStepShape_RWSeamEdge::RWStepShape_RWSeamEdge() = default;

void RWStepShape_RWSeamEdge::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepShape_SeamEdge>&      ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "seam_edge"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepShape_Vertex> aEdge_EdgeStart;
  data->CheckDerived(num, 2, "edge.edge_start", ach, false);

  occ::handle<StepShape_Vertex> aEdge_EdgeEnd;
  data->CheckDerived(num, 3, "edge.edge_end", ach, false);

  occ::handle<StepShape_Edge> aOrientedEdge_EdgeElement;
  data->ReadEntity(num,
                   4,
                   "oriented_edge.edge_element",
                   ach,
                   STANDARD_TYPE(StepShape_Edge),
                   aOrientedEdge_EdgeElement);

  bool aOrientedEdge_Orientation;
  data->ReadBoolean(num, 5, "oriented_edge.orientation", ach, aOrientedEdge_Orientation);

  occ::handle<StepGeom_Pcurve> aPcurveReference;
  data
    ->ReadEntity(num, 6, "pcurve_reference", ach, STANDARD_TYPE(StepGeom_Pcurve), aPcurveReference);

  ent->Init(aRepresentationItem_Name,
            aOrientedEdge_EdgeElement,
            aOrientedEdge_Orientation,
            aPcurveReference);
}

void RWStepShape_RWSeamEdge::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepShape_SeamEdge>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->StepShape_Edge::EdgeStart());

  SW.Send(ent->StepShape_Edge::EdgeEnd());

  SW.Send(ent->StepShape_OrientedEdge::EdgeElement());

  SW.SendBoolean(ent->StepShape_OrientedEdge::Orientation());

  SW.Send(ent->PcurveReference());
}

void RWStepShape_RWSeamEdge::Share(const occ::handle<StepShape_SeamEdge>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.AddItem(ent->StepShape_Edge::EdgeStart());

  iter.AddItem(ent->StepShape_Edge::EdgeEnd());

  iter.AddItem(ent->StepShape_OrientedEdge::EdgeElement());

  iter.AddItem(ent->PcurveReference());
}
