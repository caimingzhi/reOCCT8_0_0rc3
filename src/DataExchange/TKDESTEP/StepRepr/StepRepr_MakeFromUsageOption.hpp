#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepRepr_ProductDefinitionUsage.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

//! Representation of STEP entity MakeFromUsageOption
class StepRepr_MakeFromUsageOption : public StepRepr_ProductDefinitionUsage
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_MakeFromUsageOption();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
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
    const occ::handle<Standard_Transient>&       aQuantity);

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
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
    const occ::handle<Standard_Transient>&       aQuantity);

  //! Returns field Ranking
  Standard_EXPORT int Ranking() const;

  //! Set field Ranking
  Standard_EXPORT void SetRanking(const int Ranking);

  //! Returns field RankingRationale
  Standard_EXPORT occ::handle<TCollection_HAsciiString> RankingRationale() const;

  //! Set field RankingRationale
  Standard_EXPORT void SetRankingRationale(
    const occ::handle<TCollection_HAsciiString>& RankingRationale);

  //! Returns field Quantity
  Standard_EXPORT occ::handle<Standard_Transient> Quantity() const;

  //! Set field Quantity
  Standard_EXPORT void SetQuantity(const occ::handle<Standard_Transient>& Quantity);

  DEFINE_STANDARD_RTTIEXT(StepRepr_MakeFromUsageOption, StepRepr_ProductDefinitionUsage)

private:
  int                                   theRanking;
  occ::handle<TCollection_HAsciiString> theRankingRationale;
  occ::handle<Standard_Transient>       theQuantity;
};
