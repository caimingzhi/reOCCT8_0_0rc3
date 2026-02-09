

#include "RWStepKinematics_RWPairRepresentationRelationship.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PairRepresentationRelationship.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_RepresentationOrRepresentationReference.hpp>
#include <StepRepr_Transformation.hpp>

RWStepKinematics_RWPairRepresentationRelationship::
  RWStepKinematics_RWPairRepresentationRelationship() = default;

void RWStepKinematics_RWPairRepresentationRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                       theData,
  const int                                                         theNum,
  occ::handle<Interface_Check>&                                     theArch,
  const occ::handle<StepKinematics_PairRepresentationRelationship>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 6, theArch, "pair_representation_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<TCollection_HAsciiString> aRepresentationRelationship_Name;
  theData->ReadString(theNum,
                      2,
                      "representation_relationship.name",
                      theArch,
                      aRepresentationRelationship_Name);

  occ::handle<TCollection_HAsciiString> aRepresentationRelationship_Description;
  bool                                  hasRepresentationRelationship_Description = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadString(theNum,
                        3,
                        "representation_relationship.description",
                        theArch,
                        aRepresentationRelationship_Description);
  }
  else
  {
    hasRepresentationRelationship_Description = false;
    aRepresentationRelationship_Description.Nullify();
  }

  StepRepr_RepresentationOrRepresentationReference aRepresentationRelationship_Rep1;
  theData->ReadEntity(theNum,
                      4,
                      "representation_relationship.rep1",
                      theArch,
                      aRepresentationRelationship_Rep1);

  StepRepr_RepresentationOrRepresentationReference aRepresentationRelationship_Rep2;
  theData->ReadEntity(theNum,
                      5,
                      "representation_relationship.rep2",
                      theArch,
                      aRepresentationRelationship_Rep2);

  StepRepr_Transformation aRepresentationRelationshipWithTransformation_TransformationOperator;
  theData->ReadEntity(theNum,
                      6,
                      "representation_relationship_with_transformation.transformation_operator",
                      theArch,
                      aRepresentationRelationshipWithTransformation_TransformationOperator);

  theEnt->Init(aRepresentationItem_Name,
               aRepresentationRelationship_Name,
               hasRepresentationRelationship_Description,
               aRepresentationRelationship_Description,
               aRepresentationRelationship_Rep1,
               aRepresentationRelationship_Rep2,
               aRepresentationRelationshipWithTransformation_TransformationOperator);
}

void RWStepKinematics_RWPairRepresentationRelationship::WriteStep(
  StepData_StepWriter&                                              theSW,
  const occ::handle<StepKinematics_PairRepresentationRelationship>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->Name());

  if (theEnt->RepresentationRelationshipWithTransformation()->HasDescription())
    theSW.Send(theEnt->RepresentationRelationshipWithTransformation()->Description());
  else
    theSW.SendUndef();

  theSW.Send(theEnt->RepresentationRelationshipWithTransformation()->Rep1());

  theSW.Send(theEnt->RepresentationRelationshipWithTransformation()->Rep2());

  theSW.Send(
    theEnt->RepresentationRelationshipWithTransformation()->TransformationOperator().Value());
}

void RWStepKinematics_RWPairRepresentationRelationship::Share(
  const occ::handle<StepKinematics_PairRepresentationRelationship>& theEnt,
  Interface_EntityIterator&                                         iter) const
{

  iter.AddItem(theEnt->RepresentationRelationshipWithTransformation()->Rep1());

  iter.AddItem(theEnt->RepresentationRelationshipWithTransformation()->Rep2());

  iter.AddItem(
    theEnt->RepresentationRelationshipWithTransformation()->TransformationOperator().Value());
}
