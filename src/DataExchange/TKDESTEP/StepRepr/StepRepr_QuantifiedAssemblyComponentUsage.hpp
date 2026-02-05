#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_AssemblyComponentUsage.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

//! Representation of STEP entity QuantifiedAssemblyComponentUsage
class StepRepr_QuantifiedAssemblyComponentUsage : public StepRepr_AssemblyComponentUsage
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_QuantifiedAssemblyComponentUsage();

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
    const bool hasAssemblyComponentUsage_ReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aAssemblyComponentUsage_ReferenceDesignator,
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
    const bool hasAssemblyComponentUsage_ReferenceDesignator,
    const occ::handle<TCollection_HAsciiString>& aAssemblyComponentUsage_ReferenceDesignator,
    const occ::handle<Standard_Transient>&       aQuantity);

  //! Returns field Quantity
  Standard_EXPORT occ::handle<Standard_Transient> Quantity() const;

  //! Set field Quantity
  Standard_EXPORT void SetQuantity(const occ::handle<Standard_Transient>& Quantity);

  DEFINE_STANDARD_RTTIEXT(StepRepr_QuantifiedAssemblyComponentUsage,
                          StepRepr_AssemblyComponentUsage)

private:
  occ::handle<Standard_Transient> theQuantity;
};
