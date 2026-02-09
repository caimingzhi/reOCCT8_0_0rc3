

#include "RWStepKinematics_RWRollingCurvePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RollingCurvePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnCurve.hpp>

RWStepKinematics_RWRollingCurvePairValue::RWStepKinematics_RWRollingCurvePairValue() = default;

void RWStepKinematics_RWRollingCurvePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theArch,
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "rolling_curve_pair_value"))
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

  occ::handle<StepGeom_PointOnCurve> aActualPointOnCurve1;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_curve1",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnCurve),
                      aActualPointOnCurve1);

  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualPointOnCurve1);
}

void RWStepKinematics_RWRollingCurvePairValue::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualPointOnCurve1());
}

void RWStepKinematics_RWRollingCurvePairValue::Share(
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt,
  Interface_EntityIterator&                                iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  iter.AddItem(theEnt->ActualPointOnCurve1());
}
