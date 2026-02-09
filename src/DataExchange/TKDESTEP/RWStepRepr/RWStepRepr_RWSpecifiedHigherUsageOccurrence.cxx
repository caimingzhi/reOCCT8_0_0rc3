#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWSpecifiedHigherUsageOccurrence.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_SpecifiedHigherUsageOccurrence.hpp>

RWStepRepr_RWSpecifiedHigherUsageOccurrence::RWStepRepr_RWSpecifiedHigherUsageOccurrence() =
  default;

void RWStepRepr_RWSpecifiedHigherUsageOccurrence::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepRepr_SpecifiedHigherUsageOccurrence>& ent) const
{

  if (!data->CheckNbParams(num, 8, ach, "specified_higher_usage_occurrence"))
    return;

  occ::handle<TCollection_HAsciiString> aProductDefinitionRelationship_Id;
  data->ReadString(num,
                   1,
                   "product_definition_relationship.id",
                   ach,
                   aProductDefinitionRelationship_Id);

  occ::handle<TCollection_HAsciiString> aProductDefinitionRelationship_Name;
  data->ReadString(num,
                   2,
                   "product_definition_relationship.name",
                   ach,
                   aProductDefinitionRelationship_Name);

  occ::handle<TCollection_HAsciiString> aProductDefinitionRelationship_Description;
  bool                                  hasProductDefinitionRelationship_Description = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num,
                     3,
                     "product_definition_relationship.description",
                     ach,
                     aProductDefinitionRelationship_Description);
  }
  else
  {
    hasProductDefinitionRelationship_Description = false;
  }

  StepBasic_ProductDefinitionOrReference aProductDefinitionRelationship_RelatingProductDefinition;
  data->ReadEntity(num,
                   4,
                   "product_definition_relationship.relating_product_definition",
                   ach,
                   aProductDefinitionRelationship_RelatingProductDefinition);

  StepBasic_ProductDefinitionOrReference aProductDefinitionRelationship_RelatedProductDefinition;
  data->ReadEntity(num,
                   5,
                   "product_definition_relationship.related_product_definition",
                   ach,
                   aProductDefinitionRelationship_RelatedProductDefinition);

  occ::handle<TCollection_HAsciiString> aAssemblyComponentUsage_ReferenceDesignator;
  bool                                  hasAssemblyComponentUsage_ReferenceDesignator = true;
  if (data->IsParamDefined(num, 6))
  {
    data->ReadString(num,
                     6,
                     "assembly_component_usage.reference_designator",
                     ach,
                     aAssemblyComponentUsage_ReferenceDesignator);
  }
  else
  {
    hasAssemblyComponentUsage_ReferenceDesignator = false;
  }

  occ::handle<StepRepr_AssemblyComponentUsage> aUpperUsage;
  data->ReadEntity(num,
                   7,
                   "upper_usage",
                   ach,
                   STANDARD_TYPE(StepRepr_AssemblyComponentUsage),
                   aUpperUsage);

  occ::handle<StepRepr_NextAssemblyUsageOccurrence> aNextUsage;
  data->ReadEntity(num,
                   8,
                   "next_usage",
                   ach,
                   STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence),
                   aNextUsage);

  ent->Init(aProductDefinitionRelationship_Id,
            aProductDefinitionRelationship_Name,
            hasProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_RelatingProductDefinition,
            aProductDefinitionRelationship_RelatedProductDefinition,
            hasAssemblyComponentUsage_ReferenceDesignator,
            aAssemblyComponentUsage_ReferenceDesignator,
            aUpperUsage,
            aNextUsage);
}

void RWStepRepr_RWSpecifiedHigherUsageOccurrence::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepRepr_SpecifiedHigherUsageOccurrence>& ent) const
{

  SW.Send(ent->StepBasic_ProductDefinitionRelationship::Id());

  SW.Send(ent->StepBasic_ProductDefinitionRelationship::Name());

  if (ent->StepBasic_ProductDefinitionRelationship::HasDescription())
  {
    SW.Send(ent->StepBasic_ProductDefinitionRelationship::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->StepBasic_ProductDefinitionRelationship::RelatingProductDefinitionAP242().Value());

  SW.Send(ent->StepBasic_ProductDefinitionRelationship::RelatedProductDefinitionAP242().Value());

  if (ent->StepRepr_AssemblyComponentUsage::HasReferenceDesignator())
  {
    SW.Send(ent->StepRepr_AssemblyComponentUsage::ReferenceDesignator());
  }
  else
    SW.SendUndef();

  SW.Send(ent->UpperUsage());

  SW.Send(ent->NextUsage());
}

void RWStepRepr_RWSpecifiedHigherUsageOccurrence::Share(
  const occ::handle<StepRepr_SpecifiedHigherUsageOccurrence>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatingProductDefinitionAP242().Value());

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatedProductDefinitionAP242().Value());

  iter.AddItem(ent->UpperUsage());

  iter.AddItem(ent->NextUsage());
}
