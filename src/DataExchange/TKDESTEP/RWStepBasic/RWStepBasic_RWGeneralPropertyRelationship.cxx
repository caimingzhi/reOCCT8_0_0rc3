

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWGeneralPropertyRelationship.hpp"
#include <StepBasic_GeneralProperty.hpp>
#include <StepBasic_GeneralPropertyRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_PropertyDefinition.hpp>

RWStepBasic_RWGeneralPropertyRelationship::RWStepBasic_RWGeneralPropertyRelationship() = default;

void RWStepBasic_RWGeneralPropertyRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theAch,
  const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theAch, "general_property_association"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theAch, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (theData->IsParamDefined(theNum, 2))
  {
    theData->ReadString(theNum, 2, "description", theAch, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepBasic_GeneralProperty> aRelatingGeneralProperty;
  theData->ReadEntity(theNum,
                      3,
                      "relating_property",
                      theAch,
                      STANDARD_TYPE(StepBasic_GeneralProperty),
                      aRelatingGeneralProperty);

  occ::handle<StepBasic_GeneralProperty> aRelatedGeneralProperty;
  theData->ReadEntity(theNum,
                      4,
                      "related_property",
                      theAch,
                      STANDARD_TYPE(StepBasic_GeneralProperty),
                      aRelatedGeneralProperty);

  theEnt->Init(aName,
               hasDescription,
               aDescription,
               aRelatingGeneralProperty,
               aRelatedGeneralProperty);
}

void RWStepBasic_RWGeneralPropertyRelationship::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt) const
{
  theSW.Send(theEnt->Name());

  if (theEnt->HasDescription())
  {
    theSW.Send(theEnt->Description());
  }
  else
  {
    theSW.SendUndef();
  }

  theSW.Send(theEnt->RelatingGeneralProperty());

  theSW.Send(theEnt->RelatedGeneralProperty());
}

void RWStepBasic_RWGeneralPropertyRelationship::Share(
  const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt,
  Interface_EntityIterator&                                 theIter) const
{
  theIter.AddItem(theEnt->RelatingGeneralProperty());

  theIter.AddItem(theEnt->RelatedGeneralProperty());
}
