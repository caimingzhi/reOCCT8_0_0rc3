

#include "RWStepKinematics_RWRollingSurfacePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RollingSurfacePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWRollingSurfacePairValue::RWStepKinematics_RWRollingSurfacePairValue() = default;

void RWStepKinematics_RWRollingSurfacePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                theData,
  const int                                                  theNum,
  occ::handle<Interface_Check>&                              theArch,
  const occ::handle<StepKinematics_RollingSurfacePairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theArch, "rolling_surface_pair_value"))
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

  occ::handle<StepGeom_PointOnSurface> aActualPointOnSurface;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_surface",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnSurface),
                      aActualPointOnSurface);

  double aActualRotation;
  theData->ReadReal(theNum, 4, "actual_rotation", theArch, aActualRotation);

  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualPointOnSurface,
               aActualRotation);
}

void RWStepKinematics_RWRollingSurfacePairValue::WriteStep(
  StepData_StepWriter&                                       theSW,
  const occ::handle<StepKinematics_RollingSurfacePairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualPointOnSurface());

  theSW.Send(theEnt->ActualRotation());
}

void RWStepKinematics_RWRollingSurfacePairValue::Share(
  const occ::handle<StepKinematics_RollingSurfacePairValue>& theEnt,
  Interface_EntityIterator&                                  iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  iter.AddItem(theEnt->ActualPointOnSurface());
}
