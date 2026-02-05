#include <StepBasic_ProductDefinition.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_AssemblyComponentUsage, StepRepr_ProductDefinitionUsage)

//=================================================================================================

StepRepr_AssemblyComponentUsage::StepRepr_AssemblyComponentUsage()
{
  defReferenceDesignator = false;
}

//=================================================================================================

void StepRepr_AssemblyComponentUsage::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const occ::handle<StepBasic_ProductDefinition>&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const occ::handle<StepBasic_ProductDefinition>&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>& aReferenceDesignator)
{
  StepRepr_ProductDefinitionUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition);

  defReferenceDesignator = hasReferenceDesignator;
  if (defReferenceDesignator)
  {
    theReferenceDesignator = aReferenceDesignator;
  }
  else
    theReferenceDesignator.Nullify();
}

//=================================================================================================

void StepRepr_AssemblyComponentUsage::Init(
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Id,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Name,
  const bool                                   hasProductDefinitionRelationship_Description,
  const occ::handle<TCollection_HAsciiString>& aProductDefinitionRelationship_Description,
  const StepBasic_ProductDefinitionOrReference&
    aProductDefinitionRelationship_RelatingProductDefinition,
  const StepBasic_ProductDefinitionOrReference&
             aProductDefinitionRelationship_RelatedProductDefinition,
  const bool hasReferenceDesignator,
  const occ::handle<TCollection_HAsciiString>& aReferenceDesignator)
{
  StepRepr_ProductDefinitionUsage::Init(aProductDefinitionRelationship_Id,
                                        aProductDefinitionRelationship_Name,
                                        hasProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_Description,
                                        aProductDefinitionRelationship_RelatingProductDefinition,
                                        aProductDefinitionRelationship_RelatedProductDefinition);

  defReferenceDesignator = hasReferenceDesignator;
  if (defReferenceDesignator)
  {
    theReferenceDesignator = aReferenceDesignator;
  }
  else
    theReferenceDesignator.Nullify();
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_AssemblyComponentUsage::ReferenceDesignator() const
{
  return theReferenceDesignator;
}

//=================================================================================================

void StepRepr_AssemblyComponentUsage::SetReferenceDesignator(
  const occ::handle<TCollection_HAsciiString>& aReferenceDesignator)
{
  theReferenceDesignator = aReferenceDesignator;
}

//=================================================================================================

bool StepRepr_AssemblyComponentUsage::HasReferenceDesignator() const
{
  return defReferenceDesignator;
}
