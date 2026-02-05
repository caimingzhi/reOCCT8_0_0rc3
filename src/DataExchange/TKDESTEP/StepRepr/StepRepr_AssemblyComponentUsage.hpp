#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ProductDefinitionUsage.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

//! Representation of STEP entity AssemblyComponentUsage
class StepRepr_AssemblyComponentUsage : public StepRepr_ProductDefinitionUsage
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_AssemblyComponentUsage();

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
    const bool hasReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aReferenceDesignator);

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
    const bool hasReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aReferenceDesignator);

  //! Returns field ReferenceDesignator
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReferenceDesignator() const;

  //! Set field ReferenceDesignator
  Standard_EXPORT void SetReferenceDesignator(
    const occ::handle<TCollection_HAsciiString>& ReferenceDesignator);

  //! Returns True if optional field ReferenceDesignator is defined
  Standard_EXPORT bool HasReferenceDesignator() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_AssemblyComponentUsage, StepRepr_ProductDefinitionUsage)

private:
  occ::handle<TCollection_HAsciiString> theReferenceDesignator;
  bool                                  defReferenceDesignator;
};
