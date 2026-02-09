#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepRepr_MakeFromUsageOption.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_MakeFromUsageOption, StepRepr_ProductDefinitionUsage)

StepRepr_MakeFromUsageOption::StepRepr_MakeFromUsageOption() = default;

void StepRepr_MakeFromUsageOption::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const occ::handle<StepBasic_ProductDefinition>&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const occ::handle<StepBasic_ProductDefinition>&
            aProductDefinitionRelationship_RelatedProductDefinition,
  const int aRanking,
  const occ::handle<TCollection_HAsciiString>& aRankingRationale,
  const occ::handle<Standard_Transient>&       aQuantity)
{
  StepRepr_ProductDefinitionUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition);

  theRanking = aRanking;

  theRankingRationale = aRankingRationale;

  theQuantity = aQuantity;
}

void StepRepr_MakeFromUsageOption::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const StepBasic_ProductDefinitionOrReference&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const StepBasic_ProductDefinitionOrReference&
            aProductDefinitionRelationship_RelatedProductDefinition,
  const int aRanking,
  const occ::handle<TCollection_HAsciiString>& aRankingRationale,
  const occ::handle<Standard_Transient>&       aQuantity)
{
  StepRepr_ProductDefinitionUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition);

  theRanking = aRanking;

  theRankingRationale = aRankingRationale;

  theQuantity = aQuantity;
}

int StepRepr_MakeFromUsageOption::Ranking() const
{
  return theRanking;
}

void StepRepr_MakeFromUsageOption::SetRanking(const int aRanking)
{
  theRanking = aRanking;
}

occ::handle<TCollection_HAsciiString> StepRepr_MakeFromUsageOption::RankingRationale() const
{
  return theRankingRationale;
}

void StepRepr_MakeFromUsageOption::SetRankingRationale(
  const occ::handle<TCollection_HAsciiString>& aRankingRationale)
{
  theRankingRationale = aRankingRationale;
}

occ::handle<Standard_Transient> StepRepr_MakeFromUsageOption::Quantity() const
{
  return theQuantity;
}

void StepRepr_MakeFromUsageOption::SetQuantity(const occ::handle<Standard_Transient>& aQuantity)
{
  theQuantity = aQuantity;
}
