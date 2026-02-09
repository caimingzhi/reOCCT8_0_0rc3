

#include "RWStepKinematics_RWKinematicJoint.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepShape_Vertex.hpp>

RWStepKinematics_RWKinematicJoint::RWStepKinematics_RWKinematicJoint() = default;

void RWStepKinematics_RWKinematicJoint::ReadStep(
  const occ::handle<StepData_StepReaderData>&       theData,
  const int                                         theNum,
  occ::handle<Interface_Check>&                     theArch,
  const occ::handle<StepKinematics_KinematicJoint>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "kinematic_joint"))
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

  theEnt->Init(aRepresentationItem_Name, aEdge_EdgeStart, aEdge_EdgeEnd);
}

void RWStepKinematics_RWKinematicJoint::WriteStep(
  StepData_StepWriter&                              theSW,
  const occ::handle<StepKinematics_KinematicJoint>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->EdgeStart());

  theSW.Send(theEnt->EdgeEnd());
}

void RWStepKinematics_RWKinematicJoint::Share(
  const occ::handle<StepKinematics_KinematicJoint>& theEnt,
  Interface_EntityIterator&                         iter) const
{

  iter.AddItem(theEnt->StepShape_Edge::EdgeStart());

  iter.AddItem(theEnt->StepShape_Edge::EdgeEnd());
}
