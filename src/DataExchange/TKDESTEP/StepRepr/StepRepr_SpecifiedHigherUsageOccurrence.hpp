#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_AssemblyComponentUsage.hpp>
class StepRepr_NextAssemblyUsageOccurrence;
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

class StepRepr_SpecifiedHigherUsageOccurrence : public StepRepr_AssemblyComponentUsage
{

public:
  Standard_EXPORT StepRepr_SpecifiedHigherUsageOccurrence();

  Standard_EXPORT void Init(
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
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& aNextUsage);

  Standard_EXPORT void Init(
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
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& aNextUsage);

  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> UpperUsage() const;

  Standard_EXPORT void SetUpperUsage(
    const occ::handle<StepRepr_AssemblyComponentUsage>& UpperUsage);

  Standard_EXPORT occ::handle<StepRepr_NextAssemblyUsageOccurrence> NextUsage() const;

  Standard_EXPORT void SetNextUsage(
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& NextUsage);

  DEFINE_STANDARD_RTTIEXT(StepRepr_SpecifiedHigherUsageOccurrence, StepRepr_AssemblyComponentUsage)

private:
  occ::handle<StepRepr_AssemblyComponentUsage>      theUpperUsage;
  occ::handle<StepRepr_NextAssemblyUsageOccurrence> theNextUsage;
};
