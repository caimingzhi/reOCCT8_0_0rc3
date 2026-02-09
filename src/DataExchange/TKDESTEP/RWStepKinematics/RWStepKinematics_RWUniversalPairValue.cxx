

#include "RWStepKinematics_RWUniversalPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_UniversalPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWUniversalPairValue::RWStepKinematics_RWUniversalPairValue() = default;

void RWStepKinematics_RWUniversalPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&           theData,
  const int                                             theNum,
  occ::handle<Interface_Check>&                         theArch,
  const occ::handle<StepKinematics_UniversalPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theArch, "universal_pair_value"))
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

  double aFirstRotationAngle;
  theData->ReadReal(theNum, 3, "first_rotation_angle", theArch, aFirstRotationAngle);

  double aSecondRotationAngle;
  theData->ReadReal(theNum, 4, "second_rotation_angle", theArch, aSecondRotationAngle);

  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aFirstRotationAngle,
               aSecondRotationAngle);
}

void RWStepKinematics_RWUniversalPairValue::WriteStep(
  StepData_StepWriter&                                  theSW,
  const occ::handle<StepKinematics_UniversalPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->FirstRotationAngle());

  theSW.Send(theEnt->SecondRotationAngle());
}

void RWStepKinematics_RWUniversalPairValue::Share(
  const occ::handle<StepKinematics_UniversalPairValue>& theEnt,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
