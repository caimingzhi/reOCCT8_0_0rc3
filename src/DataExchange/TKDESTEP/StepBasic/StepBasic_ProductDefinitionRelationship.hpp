#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <StepBasic_ProductDefinitionOrReference.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinition;

class StepBasic_ProductDefinitionRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ProductDefinitionRelationship();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    aId,
    const occ::handle<TCollection_HAsciiString>&    aName,
    const bool                                      hasDescription,
    const occ::handle<TCollection_HAsciiString>&    aDescription,
    const occ::handle<StepBasic_ProductDefinition>& aRelatingProductDefinition,
    const occ::handle<StepBasic_ProductDefinition>& aRelatedProductDefinition);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&  aId,
    const occ::handle<TCollection_HAsciiString>&  aName,
    const bool                                    hasDescription,
    const occ::handle<TCollection_HAsciiString>&  aDescription,
    const StepBasic_ProductDefinitionOrReference& aRelatingProductDefinition,
    const StepBasic_ProductDefinitionOrReference& aRelatedProductDefinition);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> RelatingProductDefinition() const;

  Standard_EXPORT StepBasic_ProductDefinitionOrReference RelatingProductDefinitionAP242() const;

  Standard_EXPORT void SetRelatingProductDefinition(
    const occ::handle<StepBasic_ProductDefinition>& RelatingProductDefinition);

  Standard_EXPORT void SetRelatingProductDefinition(
    const StepBasic_ProductDefinitionOrReference& RelatingProductDefinition);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> RelatedProductDefinition() const;

  Standard_EXPORT StepBasic_ProductDefinitionOrReference RelatedProductDefinitionAP242() const;

  Standard_EXPORT void SetRelatedProductDefinition(
    const occ::handle<StepBasic_ProductDefinition>& RelatedProductDefinition);

  Standard_EXPORT void SetRelatedProductDefinition(
    const StepBasic_ProductDefinitionOrReference& RelatedProductDefinition);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>  theId;
  occ::handle<TCollection_HAsciiString>  theName;
  occ::handle<TCollection_HAsciiString>  theDescription;
  StepBasic_ProductDefinitionOrReference theRelatingProductDefinition;
  StepBasic_ProductDefinitionOrReference theRelatedProductDefinition;
  bool                                   defDescription;
};
