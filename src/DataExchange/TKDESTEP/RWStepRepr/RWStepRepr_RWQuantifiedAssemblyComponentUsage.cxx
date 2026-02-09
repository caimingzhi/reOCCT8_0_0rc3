#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWQuantifiedAssemblyComponentUsage.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_QuantifiedAssemblyComponentUsage.hpp>

RWStepRepr_RWQuantifiedAssemblyComponentUsage::RWStepRepr_RWQuantifiedAssemblyComponentUsage() =
  default;

void RWStepRepr_RWQuantifiedAssemblyComponentUsage::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   data,
  const int                                                     num,
  occ::handle<Interface_Check>&                                 ach,
  const occ::handle<StepRepr_QuantifiedAssemblyComponentUsage>& ent) const
{

  if (!data->CheckNbParams(num, 7, ach, "quantified_assembly_component_usage"))
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

  occ::handle<Standard_Transient> aQuantity;
  data->ReadEntity(num, 7, "quantity", ach, STANDARD_TYPE(Standard_Transient), aQuantity);

  ent->Init(aProductDefinitionRelationship_Id,
            aProductDefinitionRelationship_Name,
            hasProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_RelatingProductDefinition,
            aProductDefinitionRelationship_RelatedProductDefinition,
            hasAssemblyComponentUsage_ReferenceDesignator,
            aAssemblyComponentUsage_ReferenceDesignator,
            aQuantity);
}

void RWStepRepr_RWQuantifiedAssemblyComponentUsage::WriteStep(
  StepData_StepWriter&                                          SW,
  const occ::handle<StepRepr_QuantifiedAssemblyComponentUsage>& ent) const
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

  SW.Send(ent->Quantity());
}

void RWStepRepr_RWQuantifiedAssemblyComponentUsage::Share(
  const occ::handle<StepRepr_QuantifiedAssemblyComponentUsage>& ent,
  Interface_EntityIterator&                                     iter) const
{

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatingProductDefinitionAP242().Value());

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatedProductDefinitionAP242().Value());

  iter.AddItem(ent->Quantity());
}
