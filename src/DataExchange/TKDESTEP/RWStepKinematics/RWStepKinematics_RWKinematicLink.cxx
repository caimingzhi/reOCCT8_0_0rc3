

#include "RWStepKinematics_RWKinematicLink.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_KinematicLink.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepKinematics_RWKinematicLink::RWStepKinematics_RWKinematicLink() = default;

void RWStepKinematics_RWKinematicLink::ReadStep(
  const occ::handle<StepData_StepReaderData>&      theData,
  const int                                        theNum,
  occ::handle<Interface_Check>&                    theArch,
  const occ::handle<StepKinematics_KinematicLink>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 1, theArch, "kinematic_link"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  theEnt->Init(aRepresentationItem_Name);
}

void RWStepKinematics_RWKinematicLink::WriteStep(
  StepData_StepWriter&                             theSW,
  const occ::handle<StepKinematics_KinematicLink>& theEnt) const
{

  theSW.Send(theEnt->Name());
}

void RWStepKinematics_RWKinematicLink::Share(const occ::handle<StepKinematics_KinematicLink>&,
                                             Interface_EntityIterator&) const
{
}
