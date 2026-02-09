

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWRepresentationRelationshipWithTransformation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_Transformation.hpp>

RWStepRepr_RWRepresentationRelationshipWithTransformation::
  RWStepRepr_RWRepresentationRelationshipWithTransformation() = default;

void RWStepRepr_RWRepresentationRelationshipWithTransformation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                               data,
  const int                                                                 num,
  occ::handle<Interface_Check>&                                             ach,
  const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "representation_relationship_with_transformation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepRepr_Representation> aRep1;

  data->ReadEntity(num, 3, "rep_1", ach, STANDARD_TYPE(StepRepr_Representation), aRep1);

  occ::handle<StepRepr_Representation> aRep2;

  data->ReadEntity(num, 4, "rep_2", ach, STANDARD_TYPE(StepRepr_Representation), aRep2);

  StepRepr_Transformation aTrans;

  data->ReadEntity(num, 5, "transformation_operator", ach, aTrans);

  ent->Init(aName, aDescription, aRep1, aRep2, aTrans);
}

void RWStepRepr_RWRepresentationRelationshipWithTransformation::WriteStep(
  StepData_StepWriter&                                                      SW,
  const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Rep1());

  SW.Send(ent->Rep2());

  SW.Send(ent->TransformationOperator().Value());
}

void RWStepRepr_RWRepresentationRelationshipWithTransformation::Share(
  const occ::handle<StepRepr_RepresentationRelationshipWithTransformation>& ent,
  Interface_EntityIterator&                                                 iter) const
{

  iter.GetOneItem(ent->Rep1());

  iter.GetOneItem(ent->Rep2());

  iter.GetOneItem(ent->TransformationOperator().Value());
}
