#include <StepBasic_ProductDefinition.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_SpecifiedHigherUsageOccurrence.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_SpecifiedHigherUsageOccurrence, StepRepr_AssemblyComponentUsage)

StepRepr_SpecifiedHigherUsageOccurrence::StepRepr_SpecifiedHigherUsageOccurrence() = default;

void StepRepr_SpecifiedHigherUsageOccurrence::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const occ::handle<StepBasic_ProductDefinition>&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const occ::handle<StepBasic_ProductDefinition>&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>&        aAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<StepRepr_AssemblyComponentUsage>& aUpperUsage,
  const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& aNextUsage)
{
  StepRepr_AssemblyComponentUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition,
                                        hasAssemblyComponentUsage_ReferenceDesignator,
                                        aAssemblyComponentUsage_ReferenceDesignator);

  theUpperUsage = aUpperUsage;

  theNextUsage = aNextUsage;
}

void StepRepr_SpecifiedHigherUsageOccurrence::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const StepBasic_ProductDefinitionOrReference&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const StepBasic_ProductDefinitionOrReference&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>&        aAssemblyComponentUsage_ReferenceDesignator,
  const occ::handle<StepRepr_AssemblyComponentUsage>& aUpperUsage,
  const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& aNextUsage)
{
  StepRepr_AssemblyComponentUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition,
                                        hasAssemblyComponentUsage_ReferenceDesignator,
                                        aAssemblyComponentUsage_ReferenceDesignator);

  theUpperUsage = aUpperUsage;

  theNextUsage = aNextUsage;
}

occ::handle<StepRepr_AssemblyComponentUsage> StepRepr_SpecifiedHigherUsageOccurrence::UpperUsage()
  const
{
  return theUpperUsage;
}

void StepRepr_SpecifiedHigherUsageOccurrence::SetUpperUsage(
  const occ::handle<StepRepr_AssemblyComponentUsage>& aUpperUsage)
{
  theUpperUsage = aUpperUsage;
}

occ::handle<StepRepr_NextAssemblyUsageOccurrence> StepRepr_SpecifiedHigherUsageOccurrence::
  NextUsage() const
{
  return theNextUsage;
}

void StepRepr_SpecifiedHigherUsageOccurrence::SetNextUsage(
  const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& aNextUsage)
{
  theNextUsage = aNextUsage;
}
