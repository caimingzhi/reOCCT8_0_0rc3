#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWMakeFromUsageOption.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MakeFromUsageOption.hpp>

//=================================================================================================

RWStepRepr_RWMakeFromUsageOption::RWStepRepr_RWMakeFromUsageOption() = default;

//=================================================================================================

void RWStepRepr_RWMakeFromUsageOption::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepRepr_MakeFromUsageOption>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 8, ach, "make_from_usage_option"))
    return;

  // Inherited fields of ProductDefinitionRelationship

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

  // Own fields of MakeFromUsageOption

  int aRanking;
  data->ReadInteger(num, 6, "ranking", ach, aRanking);

  occ::handle<TCollection_HAsciiString> aRankingRationale;
  data->ReadString(num, 7, "ranking_rationale", ach, aRankingRationale);

  occ::handle<Standard_Transient> aQuantity;
  data->ReadEntity(num, 8, "quantity", ach, STANDARD_TYPE(Standard_Transient), aQuantity);

  // Initialize entity
  ent->Init(aProductDefinitionRelationship_Id,
            aProductDefinitionRelationship_Name,
            hasProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_Description,
            aProductDefinitionRelationship_RelatingProductDefinition,
            aProductDefinitionRelationship_RelatedProductDefinition,
            aRanking,
            aRankingRationale,
            aQuantity);
}

//=================================================================================================

void RWStepRepr_RWMakeFromUsageOption::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepRepr_MakeFromUsageOption>& ent) const
{

  // Inherited fields of ProductDefinitionRelationship

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

  // Own fields of MakeFromUsageOption

  SW.Send(ent->Ranking());

  SW.Send(ent->RankingRationale());

  SW.Send(ent->Quantity());
}

//=================================================================================================

void RWStepRepr_RWMakeFromUsageOption::Share(const occ::handle<StepRepr_MakeFromUsageOption>& ent,
                                             Interface_EntityIterator& iter) const
{

  // Inherited fields of ProductDefinitionRelationship

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatingProductDefinitionAP242().Value());

  iter.AddItem(
    ent->StepBasic_ProductDefinitionRelationship::RelatedProductDefinitionAP242().Value());

  // Own fields of MakeFromUsageOption

  iter.AddItem(ent->Quantity());
}
