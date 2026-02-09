

#include "RWStepVisual_RWRepositionedTessellatedItem.hpp"

#include <Interface_Check.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_RepositionedTessellatedItem.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

void RWStepVisual_RWRepositionedTessellatedItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                theData,
  const int                                                  theNum,
  occ::handle<Interface_Check>&                              theAch,
  const occ::handle<StepVisual_RepositionedTessellatedItem>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 2, theAch, "tessellated_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  occ::handle<StepGeom_Axis2Placement3d> aLocation;
  theData->ReadEntity(theNum,
                      2,
                      "location",
                      theAch,
                      STANDARD_TYPE(StepGeom_Axis2Placement3d),
                      aLocation);

  theEnt->Init(aName, aLocation);
}

void RWStepVisual_RWRepositionedTessellatedItem::WriteStep(
  StepData_StepWriter&                                       theSW,
  const occ::handle<StepVisual_RepositionedTessellatedItem>& theEnt) const
{

  theSW.Send(theEnt->Name());
  theSW.Send(theEnt->Location());
}
