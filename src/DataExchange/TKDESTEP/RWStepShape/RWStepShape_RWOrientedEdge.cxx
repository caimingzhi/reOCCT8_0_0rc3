

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWOrientedEdge.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_Vertex.hpp>

RWStepShape_RWOrientedEdge::RWStepShape_RWOrientedEdge() = default;

void RWStepShape_RWOrientedEdge::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepShape_OrientedEdge>&  ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "oriented_edge"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  data->CheckDerived(num, 2, "edge_start", ach, false);

  data->CheckDerived(num, 3, "edge_end", ach, false);

  occ::handle<StepShape_Edge> aEdgeElement;

  data->ReadEntity(num, 4, "edge_element", ach, STANDARD_TYPE(StepShape_Edge), aEdgeElement);

  bool aOrientation;

  data->ReadBoolean(num, 5, "orientation", ach, aOrientation);

  ent->Init(aName, aEdgeElement, aOrientation);
}

void RWStepShape_RWOrientedEdge::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepShape_OrientedEdge>& ent) const
{

  SW.Send(ent->Name());

  SW.SendDerived();

  SW.SendDerived();

  SW.Send(ent->EdgeElement());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWOrientedEdge::Share(const occ::handle<StepShape_OrientedEdge>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->EdgeElement());
}
