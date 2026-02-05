// Created on : Sat May 02 12:41:16 2020

#include "RWStepKinematics_RWRollingCurvePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RollingCurvePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnCurve.hpp>

//=================================================================================================

RWStepKinematics_RWRollingCurvePairValue::RWStepKinematics_RWRollingCurvePairValue() = default;

//=================================================================================================

void RWStepKinematics_RWRollingCurvePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theArch,
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 3, theArch, "rolling_curve_pair_value"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  // Inherited fields of PairValue

  occ::handle<StepKinematics_KinematicPair> aPairValue_AppliesToPair;
  theData->ReadEntity(theNum,
                      2,
                      "pair_value.applies_to_pair",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicPair),
                      aPairValue_AppliesToPair);

  // Own fields of RollingCurvePairValue

  occ::handle<StepGeom_PointOnCurve> aActualPointOnCurve1;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_curve1",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnCurve),
                      aActualPointOnCurve1);

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name, aPairValue_AppliesToPair, aActualPointOnCurve1);
}

//=================================================================================================

void RWStepKinematics_RWRollingCurvePairValue::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of PairValue

  theSW.Send(theEnt->AppliesToPair());

  // Own fields of RollingCurvePairValue

  theSW.Send(theEnt->ActualPointOnCurve1());
}

//=================================================================================================

void RWStepKinematics_RWRollingCurvePairValue::Share(
  const occ::handle<StepKinematics_RollingCurvePairValue>& theEnt,
  Interface_EntityIterator&                                iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of PairValue

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  // Own fields of RollingCurvePairValue

  iter.AddItem(theEnt->ActualPointOnCurve1());
}
