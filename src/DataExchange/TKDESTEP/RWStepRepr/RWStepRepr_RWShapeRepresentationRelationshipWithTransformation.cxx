

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWShapeRepresentationRelationshipWithTransformation.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_ShapeRepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_Transformation.hpp>

RWStepRepr_RWShapeRepresentationRelationshipWithTransformation::
  RWStepRepr_RWShapeRepresentationRelationshipWithTransformation() = default;

void RWStepRepr_RWShapeRepresentationRelationshipWithTransformation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                    data,
  const int                                                                      num0,
  occ::handle<Interface_Check>&                                                  ach,
  const occ::handle<StepRepr_ShapeRepresentationRelationshipWithTransformation>& ent) const
{

  int num = 0;
  data->NamedForComplex("REPRESENTATION_RELATIONSHIP", "RPRRLT", num0, num, ach);

  if (!data->CheckNbParams(num, 4, ach, "representation_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepRepr_Representation> aRep1;

  data->ReadEntity(num, 3, "rep_1", ach, STANDARD_TYPE(StepRepr_Representation), aRep1);

  occ::handle<StepRepr_Representation> aRep2;

  data->ReadEntity(num, 4, "rep_2", ach, STANDARD_TYPE(StepRepr_Representation), aRep2);

  data->NamedForComplex("REPRESENTATION_RELATIONSHIP_WITH_TRANSFORMATION", "RRWT", num0, num, ach);
  if (!data->CheckNbParams(num, 1, ach, "representation_relationship_with_transformation"))
    return;

  StepRepr_Transformation aTrans;

  data->ReadEntity(num, 1, "transformation_operator", ach, aTrans);

  data->NamedForComplex("SHAPE_REPRESENTATION_RELATIONSHIP", "SHRPRL", num0, num, ach);
  if (!data->CheckNbParams(num, 0, ach, "shape_representation_relationship"))
    return;

  ent->Init(aName, aDescription, aRep1, aRep2, aTrans);
}

void RWStepRepr_RWShapeRepresentationRelationshipWithTransformation::WriteStep(
  StepData_StepWriter&                                                           SW,
  const occ::handle<StepRepr_ShapeRepresentationRelationshipWithTransformation>& ent) const
{

  SW.StartEntity("REPRESENTATION_RELATIONSHIP");

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Rep1());

  SW.Send(ent->Rep2());

  SW.StartEntity("REPRESENTATION_RELATIONSHIP_WITH_TRANSFORMATION");

  SW.Send(ent->TransformationOperator().Value());

  SW.StartEntity("SHAPE_REPRESENTATION_RELATIONSHIP");
}

void RWStepRepr_RWShapeRepresentationRelationshipWithTransformation::Share(
  const occ::handle<StepRepr_ShapeRepresentationRelationshipWithTransformation>& ent,
  Interface_EntityIterator&                                                      iter) const
{

  iter.GetOneItem(ent->Rep1());

  iter.GetOneItem(ent->Rep2());

  iter.GetOneItem(ent->TransformationOperator().Value());
}
