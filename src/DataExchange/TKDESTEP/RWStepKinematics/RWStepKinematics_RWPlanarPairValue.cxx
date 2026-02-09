

#include "RWStepKinematics_RWPlanarPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PlanarPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWPlanarPairValue::RWStepKinematics_RWPlanarPairValue() = default;

void RWStepKinematics_RWPlanarPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&        theData,
  const int                                          theNum,
  occ::handle<Interface_Check>&                      theArch,
  const occ::handle<StepKinematics_PlanarPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 5, theArch, "planar_pair_value"))
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

  double aActualTranslationX;
  theData->ReadReal(theNum, 4, "actual_translation_x", theArch, aActualTranslationX);

  double aActualTranslationY;
  theData->ReadReal(theNum, 5, "actual_translation_y", theArch, aActualTranslationY);

  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualRotation,
               aActualTranslationX,
               aActualTranslationY);
}

void RWStepKinematics_RWPlanarPairValue::WriteStep(
  StepData_StepWriter&                               theSW,
  const occ::handle<StepKinematics_PlanarPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualRotation());

  theSW.Send(theEnt->ActualTranslationX());

  theSW.Send(theEnt->ActualTranslationY());
}

void RWStepKinematics_RWPlanarPairValue::Share(
  const occ::handle<StepKinematics_PlanarPairValue>& theEnt,
  Interface_EntityIterator&                          iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
