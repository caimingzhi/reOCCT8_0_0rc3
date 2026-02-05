// Created on : Sat May 02 12:41:16 2020

#include "RWStepKinematics_RWSlidingSurfacePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_SlidingSurfacePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <Standard_Real.hpp>

//=================================================================================================

RWStepKinematics_RWSlidingSurfacePairValue::RWStepKinematics_RWSlidingSurfacePairValue() = default;

//=================================================================================================

void RWStepKinematics_RWSlidingSurfacePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                theData,
  const int                                                  theNum,
  occ::handle<Interface_Check>&                              theArch,
  const occ::handle<StepKinematics_SlidingSurfacePairValue>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 5, theArch, "sliding_surface_pair_value"))
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

  // Own fields of SlidingSurfacePairValue

  occ::handle<StepGeom_PointOnSurface> aActualPointOnSurface1;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_surface1",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnSurface),
                      aActualPointOnSurface1);

  occ::handle<StepGeom_PointOnSurface> aActualPointOnSurface2;
  theData->ReadEntity(theNum,
                      4,
                      "actual_point_on_surface2",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnSurface),
                      aActualPointOnSurface2);

  double aActualRotation;
  theData->ReadReal(theNum, 5, "actual_rotation", theArch, aActualRotation);

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualPointOnSurface1,
               aActualPointOnSurface2,
               aActualRotation);
}

//=================================================================================================

void RWStepKinematics_RWSlidingSurfacePairValue::WriteStep(
  StepData_StepWriter&                                       theSW,
  const occ::handle<StepKinematics_SlidingSurfacePairValue>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of PairValue

  theSW.Send(theEnt->AppliesToPair());

  // Own fields of SlidingSurfacePairValue

  theSW.Send(theEnt->ActualPointOnSurface1());

  theSW.Send(theEnt->ActualPointOnSurface2());

  theSW.Send(theEnt->ActualRotation());
}

//=================================================================================================

void RWStepKinematics_RWSlidingSurfacePairValue::Share(
  const occ::handle<StepKinematics_SlidingSurfacePairValue>& theEnt,
  Interface_EntityIterator&                                  iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of PairValue

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  // Own fields of SlidingSurfacePairValue

  iter.AddItem(theEnt->ActualPointOnSurface1());

  iter.AddItem(theEnt->ActualPointOnSurface2());
}
