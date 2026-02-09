

#include "RWStepKinematics_RWOrientedJoint.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_OrientedJoint.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepShape_Vertex.hpp>
#include <StepShape_Edge.hpp>

RWStepKinematics_RWOrientedJoint::RWStepKinematics_RWOrientedJoint() = default;

void RWStepKinematics_RWOrientedJoint::ReadStep(
  const occ::handle<StepData_StepReaderData>&      theData,
  const int                                        theNum,
  occ::handle<Interface_Check>&                    theArch,
  const occ::handle<StepKinematics_OrientedJoint>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 5, theArch, "oriented_joint"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<StepShape_Vertex> aEdge_EdgeStart;
  theData->ReadEntity(theNum,
                      2,
                      "edge.edge_start",
                      theArch,
                      STANDARD_TYPE(StepShape_Vertex),
                      aEdge_EdgeStart);

  occ::handle<StepShape_Vertex> aEdge_EdgeEnd;
  theData->ReadEntity(theNum,
                      3,
                      "edge.edge_end",
                      theArch,
                      STANDARD_TYPE(StepShape_Vertex),
                      aEdge_EdgeEnd);

  occ::handle<StepShape_Edge> aOrientedEdge_EdgeElement;
  theData->ReadEntity(theNum,
                      4,
                      "oriented_edge.edge_element",
                      theArch,
                      STANDARD_TYPE(StepShape_Edge),
                      aOrientedEdge_EdgeElement);

  bool aOrientedEdge_Orientation;
  theData->ReadBoolean(theNum, 5, "oriented_edge.orientation", theArch, aOrientedEdge_Orientation);

  theEnt->Init(aRepresentationItem_Name, aOrientedEdge_EdgeElement, aOrientedEdge_Orientation);
}

void RWStepKinematics_RWOrientedJoint::WriteStep(
  StepData_StepWriter&                             theSW,
  const occ::handle<StepKinematics_OrientedJoint>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->EdgeStart());

  theSW.Send(theEnt->EdgeEnd());

  theSW.Send(theEnt->EdgeElement());

  theSW.SendBoolean(theEnt->Orientation());
}

void RWStepKinematics_RWOrientedJoint::Share(
  const occ::handle<StepKinematics_OrientedJoint>& theEnt,
  Interface_EntityIterator&                        iter) const
{

  iter.AddItem(theEnt->StepShape_Edge::EdgeStart());

  iter.AddItem(theEnt->StepShape_Edge::EdgeEnd());

  iter.AddItem(theEnt->StepShape_OrientedEdge::EdgeElement());
}
