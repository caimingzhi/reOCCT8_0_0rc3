#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ProductDefinitionUsage.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

class StepRepr_AssemblyComponentUsage : public StepRepr_ProductDefinitionUsage
{

public:
  Standard_EXPORT StepRepr_AssemblyComponentUsage();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
    const bool                                   hasProductDefinitionRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
    const occ::handle<StepBasic_ProductDefinition>&
      aProductDefinitionRelationship_RelatingProductDefinition,
    const occ::handle<StepBasic_ProductDefinition>&
               aProductDefinitionRelationship_RelatedProductDefinition,
    const bool hasReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aReferenceDesignator);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
    const bool                                   hasProductDefinitionRelationship_Description,
    const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
    const StepBasic_ProductDefinitionOrReference&
      aProductDefinitionRelationship_RelatingProductDefinition,
    const StepBasic_ProductDefinitionOrReference&
               aProductDefinitionRelationship_RelatedProductDefinition,
    const bool hasReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aReferenceDesignator);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceDesignator() const;

  Standard_EXPORT void SetReferenceDesignator(
    const occ::handle<TCollection_HAsciiString>& ReferenceDesignator);

  Standard_EXPORT bool HasReferenceDesignator() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_AssemblyComponentUsage, StepRepr_ProductDefinitionUsage)

private:
  occ::handle<TCollection_HAsciiString> theReferenceDesignator;
  bool                                  defReferenceDesignator;
};
