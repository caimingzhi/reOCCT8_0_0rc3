

#include "RWStepKinematics_RWPrismaticPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PrismaticPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWPrismaticPairValue::RWStepKinematics_RWPrismaticPairValue() = default;

void RWStepKinematics_RWPrismaticPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&           theData,
  const int                                             theNum,
  occ::handle<Interface_Check>&                         theArch,
  const occ::handle<StepKinematics_PrismaticPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "prismatic_pair_value"))
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

  double aActualTranslation;
  theData->ReadReal(theNum, 3, "actual_translation", theArch, aActualTranslation);

  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualTranslation);
}

void RWStepKinematics_RWPrismaticPairValue::WriteStep(
  StepData_StepWriter&                                  theSW,
  const occ::handle<StepKinematics_PrismaticPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualTranslation());
}

void RWStepKinematics_RWPrismaticPairValue::Share(
  const occ::handle<StepKinematics_PrismaticPairValue>& theEnt,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());
}
