#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepRepr_QuantifiedAssemblyComponentUsage.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_QuantifiedAssemblyComponentUsage,
                           StepRepr_AssemblyComponentUsage)

StepRepr_QuantifiedAssemblyComponentUsage::StepRepr_QuantifiedAssemblyComponentUsage() = default;

void StepRepr_QuantifiedAssemblyComponentUsage::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const occ::handle<StepBasic_ProductDefinition>&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const occ::handle<StepBasic_ProductDefinition>&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>& aAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<Standard_Transient>&       aQuantity)
{
  StepRepr_AssemblyComponentUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition,
                                        hasAssemblyComponentUsage_ReferenceDesignator,
                                        aAssemblyComponentUsage_ReferenceDesignator);

  theQuantity = aQuantity;
}

void StepRepr_QuantifiedAssemblyComponentUsage::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const StepBasic_ProductDefinitionOrReference&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const StepBasic_ProductDefinitionOrReference&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>& aAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<Standard_Transient>&       aQuantity)
{
  StepRepr_AssemblyComponentUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition,
                                        hasAssemblyComponentUsage_ReferenceDesignator,
                                        aAssemblyComponentUsage_ReferenceDesignator);

  theQuantity = aQuantity;
}

occ::handle<Standard_Transient> StepRepr_QuantifiedAssemblyComponentUsage::Quantity() const
{
  return theQuantity;
}

void StepRepr_QuantifiedAssemblyComponentUsage::SetQuantity(
  const occ::handle<Standard_Transient>& aQuantity)
{
  theQuantity = aQuantity;
}
