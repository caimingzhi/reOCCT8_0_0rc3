

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGeneralPropertyAssociation.hpp"
#include <StepBasic_GeneralProperty.hpp>
#include <StepBasic_GeneralPropertyAssociation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinition.hpp>

RWStepBasic_RWGeneralPropertyAssociation::RWStepBasic_RWGeneralPropertyAssociation() = default;

void RWStepBasic_RWGeneralPropertyAssociation::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theAch,
  const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theAch, "general_property_association"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  theData->ReadString(theNum, 2, "description", theAch, aDescription);

  occ::handle<StepBasic_GeneralProperty> aGeneralProperty;
  theData->ReadEntity(theNum,
                      3,
                      "base_definition",
                      theAch,
                      STANDARD_TYPE(StepBasic_GeneralProperty),
                      aGeneralProperty);

  occ::handle<StepRepr_PropertyDefinition> aPropertyDefinition;
  theData->ReadEntity(theNum,
                      4,
                      "derived_definition",
                      theAch,
                      STANDARD_TYPE(StepRepr_PropertyDefinition),
                      aPropertyDefinition);

  theEnt->Init(aName, aDescription, aGeneralProperty, aPropertyDefinition);
}

void RWStepBasic_RWGeneralPropertyAssociation::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt) const
{
  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->Description());

  theSW.Send(theEnt->GeneralProperty());

  theSW.Send(theEnt->PropertyDefinition());
}

void RWStepBasic_RWGeneralPropertyAssociation::Share(
  const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt,
  Interface_EntityIterator&                                theIter) const
{
  theIter.AddItem(theEnt->GeneralProperty());

  theIter.AddItem(theEnt->PropertyDefinition());
}
