

#include "RWStepKinematics_RWRevolutePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RevolutePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWRevolutePairValue::RWStepKinematics_RWRevolutePairValue() = default;

void RWStepKinematics_RWRevolutePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&          theData,
  const int                                            theNum,
  occ::handle<Interface_Check>&                        theArch,
  const occ::handle<StepKinematics_RevolutePairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "revolute_pair_value"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<StepKinematics_KinematicPair> aPairValue_AppliesToPair;
  theData->ReadEntity(theNum,
                      2,
                      "pair_value.applies_to_pair",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicPair),
                      aPairValue_AppliesToPair);

  double aActualRotation;
  theData->ReadReal(theNum, 3, "actual_rotation", theArch, aActualRotation);

  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualRotation);
}

void RWStepKinematics_RWRevolutePairValue::WriteStep(
  StepData_StepWriter&                                 theSW,
  const occ::handle<StepKinematics_RevolutePairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualRotation());
}

void RWStepKinematics_RWRevolutePairValue::Share(
  const occ::handle<StepKinematics_RevolutePairValue>& theEnt,
  Interface_EntityIterator&                            iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
