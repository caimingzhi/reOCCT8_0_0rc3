

#include "RWStepKinematics_RWUnconstrainedPairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_UnconstrainedPairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

RWStepKinematics_RWUnconstrainedPairValue::RWStepKinematics_RWUnconstrainedPairValue() = default;

void RWStepKinematics_RWUnconstrainedPairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theArch,
  const occ::handle<StepKinematics_UnconstrainedPairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "unconstrained_pair_value"))
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

  occ::handle<StepGeom_Axis2Placement3d> aActualPlacement;
  theData->ReadEntity(theNum,
                      3,
                      "actual_placement",
                      theArch,
                      STANDARD_TYPE(StepGeom_Axis2Placement3d),
                      aActualPlacement);

  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualPlacement);
}

void RWStepKinematics_RWUnconstrainedPairValue::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepKinematics_UnconstrainedPairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualPlacement());
}

void RWStepKinematics_RWUnconstrainedPairValue::Share(
  const occ::handle<StepKinematics_UnconstrainedPairValue>& theEnt,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  iter.AddItem(theEnt->ActualPlacement());
}
