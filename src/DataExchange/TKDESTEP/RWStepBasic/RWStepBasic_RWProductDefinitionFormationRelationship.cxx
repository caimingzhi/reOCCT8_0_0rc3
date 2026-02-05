#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionFormationRelationship.hpp"
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionFormationRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWProductDefinitionFormationRelationship::
  RWStepBasic_RWProductDefinitionFormationRelationship() = default;

//=================================================================================================

void RWStepBasic_RWProductDefinitionFormationRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          data,
  const int                                                            num,
  occ::handle<Interface_Check>&                                        ach,
  const occ::handle<StepBasic_ProductDefinitionFormationRelationship>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 5, ach, "product_definition_formation_relationship"))
    return;

  // Own fields of ProductDefinitionFormationRelationship

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 3, "description", ach, aDescription);

  occ::handle<StepBasic_ProductDefinitionFormation> aRelatingProductDefinitionFormation;
  data->ReadEntity(num,
                   4,
                   "relating_product_definition_formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aRelatingProductDefinitionFormation);

  occ::handle<StepBasic_ProductDefinitionFormation> aRelatedProductDefinitionFormation;
  data->ReadEntity(num,
                   5,
                   "related_product_definition_formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aRelatedProductDefinitionFormation);

  // Initialize entity
  ent->Init(aId,
            aName,
            aDescription,
            aRelatingProductDefinitionFormation,
            aRelatedProductDefinitionFormation);
}

//=================================================================================================

void RWStepBasic_RWProductDefinitionFormationRelationship::WriteStep(
  StepData_StepWriter&                                                 SW,
  const occ::handle<StepBasic_ProductDefinitionFormationRelationship>& ent) const
{

  // Own fields of ProductDefinitionFormationRelationship

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->RelatingProductDefinitionFormation());

  SW.Send(ent->RelatedProductDefinitionFormation());
}

//=================================================================================================

void RWStepBasic_RWProductDefinitionFormationRelationship::Share(
  const occ::handle<StepBasic_ProductDefinitionFormationRelationship>& ent,
  Interface_EntityIterator&                                            iter) const
{

  // Own fields of ProductDefinitionFormationRelationship

  iter.AddItem(ent->RelatingProductDefinitionFormation());

  iter.AddItem(ent->RelatedProductDefinitionFormation());
}
