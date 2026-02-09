

#include "RWStepKinematics_RWLowOrderKinematicPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_LowOrderKinematicPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWLowOrderKinematicPairValue::RWStepKinematics_RWLowOrderKinematicPairValue() =
  default;

void RWStepKinematics_RWLowOrderKinematicPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   theData,
  const int                                                     theNum,
  occ::handle<Interface_Check>&                                 theArch,
  const occ::handle<StepKinematics_LowOrderKinematicPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 8, theArch, "low_order_kinematic_pair_value"))
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

  double aActualTranslationX;
  theData->ReadReal(theNum, 3, "actual_translation_x", theArch, aActualTranslationX);

  double aActualTranslationY;
  theData->ReadReal(theNum, 4, "actual_translation_y", theArch, aActualTranslationY);

  double aActualTranslationZ;
  theData->ReadReal(theNum, 5, "actual_translation_z", theArch, aActualTranslationZ);

  double aActualRotationX;
  theData->ReadReal(theNum, 6, "actual_rotation_x", theArch, aActualRotationX);

  double aActualRotationY;
  theData->ReadReal(theNum, 7, "actual_rotation_y", theArch, aActualRotationY);

  double aActualRotationZ;
  theData->ReadReal(theNum, 8, "actual_rotation_z", theArch, aActualRotationZ);

  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualTranslationX,
               aActualTranslationY,
               aActualTranslationZ,
               aActualRotationX,
               aActualRotationY,
               aActualRotationZ);
}

void RWStepKinematics_RWLowOrderKinematicPairValue::WriteStep(
  StepData_StepWriter&                                          theSW,
  const occ::handle<StepKinematics_LowOrderKinematicPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualTranslationX());

  theSW.Send(theEnt->ActualTranslationY());

  theSW.Send(theEnt->ActualTranslationZ());

  theSW.Send(theEnt->ActualRotationX());

  theSW.Send(theEnt->ActualRotationY());

  theSW.Send(theEnt->ActualRotationZ());
}

void RWStepKinematics_RWLowOrderKinematicPairValue::Share(
  const occ::handle<StepKinematics_LowOrderKinematicPairValue>& theEnt,
  Interface_EntityIterator&                                     iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
