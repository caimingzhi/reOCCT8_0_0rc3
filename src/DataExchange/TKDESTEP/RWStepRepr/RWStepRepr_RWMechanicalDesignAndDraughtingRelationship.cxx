

#include <Standard_Type.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMechanicalDesignAndDraughtingRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_MechanicalDesignAndDraughtingRelationship.hpp>

RWStepRepr_RWMechanicalDesignAndDraughtingRelationship::
  RWStepRepr_RWMechanicalDesignAndDraughtingRelationship() = default;

void RWStepRepr_RWMechanicalDesignAndDraughtingRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                            theData,
  const int                                                              theNum,
  occ::handle<Interface_Check>&                                          theAch,
  const occ::handle<StepRepr_MechanicalDesignAndDraughtingRelationship>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theAch, "mechanical_design_and_draughting_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (theData->IsParamDefined(theNum, 2))
  {
    theData->ReadString(theNum, 2, "description", theAch, aDescription);
  }

  occ::handle<StepRepr_Representation> aRep1;
  theData->ReadEntity(theNum, 3, "rep_1", theAch, STANDARD_TYPE(StepRepr_Representation), aRep1);

  occ::handle<StepRepr_Representation> aRep2;
  theData->ReadEntity(theNum, 4, "rep_2", theAch, STANDARD_TYPE(StepRepr_Representation), aRep2);

  theEnt->Init(aName, aDescription, aRep1, aRep2);
}

void RWStepRepr_RWMechanicalDesignAndDraughtingRelationship::WriteStep(
  StepData_StepWriter&                                                   theSW,
  const occ::handle<StepRepr_MechanicalDesignAndDraughtingRelationship>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->Description());

  theSW.Send(theEnt->Rep1());

  theSW.Send(theEnt->Rep2());
}

void RWStepRepr_RWMechanicalDesignAndDraughtingRelationship::Share(
  const occ::handle<StepRepr_MechanicalDesignAndDraughtingRelationship>& theEnt,
  Interface_EntityIterator&                                              theIter) const
{
  theIter.GetOneItem(theEnt->Rep1());
  theIter.GetOneItem(theEnt->Rep2());
}
