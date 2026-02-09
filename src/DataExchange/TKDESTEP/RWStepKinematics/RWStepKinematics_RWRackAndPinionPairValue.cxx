

#include "RWStepKinematics_RWRackAndPinionPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RackAndPinionPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWRackAndPinionPairValue::RWStepKinematics_RWRackAndPinionPairValue() = default;

void RWStepKinematics_RWRackAndPinionPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theArch,
  const occ::handle<StepKinematics_RackAndPinionPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "rack_and_pinion_pair_value"))
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

  double aActualDisplacement;
  theData->ReadReal(theNum, 3, "actual_displacement", theArch, aActualDisplacement);

  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualDisplacement);
}

void RWStepKinematics_RWRackAndPinionPairValue::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepKinematics_RackAndPinionPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualDisplacement());
}

void RWStepKinematics_RWRackAndPinionPairValue::Share(
  const occ::handle<StepKinematics_RackAndPinionPairValue>& theEnt,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
