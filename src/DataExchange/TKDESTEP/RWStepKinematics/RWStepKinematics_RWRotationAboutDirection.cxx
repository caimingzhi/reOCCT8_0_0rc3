

#include "RWStepKinematics_RWRotationAboutDirection.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RotationAboutDirection.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepGeom_Direction.hpp>
#include <Standard_Real.hpp>

RWStepKinematics_RWRotationAboutDirection::RWStepKinematics_RWRotationAboutDirection() = default;

void RWStepKinematics_RWRotationAboutDirection::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theArch,
  const occ::handle<StepKinematics_RotationAboutDirection>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theArch, "rotation_about_direction"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<StepGeom_Direction> aDirectionOfAxis;
  theData->ReadEntity(theNum,
                      2,
                      "direction_of_axis",
                      theArch,
                      STANDARD_TYPE(StepGeom_Direction),
                      aDirectionOfAxis);

  double aRotationAngle;
  theData->ReadReal(theNum, 3, "rotation_angle", theArch, aRotationAngle);

  theEnt->Init(aRepresentationItem_Name, aDirectionOfAxis, aRotationAngle);
}

void RWStepKinematics_RWRotationAboutDirection::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepKinematics_RotationAboutDirection>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->DirectionOfAxis());

  theSW.Send(theEnt->RotationAngle());
}

void RWStepKinematics_RWRotationAboutDirection::Share(
  const occ::handle<StepKinematics_RotationAboutDirection>& theEnt,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(theEnt->DirectionOfAxis());
}
