#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_PropertyDefinition;

class StepRepr_PropertyDefinitionRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_PropertyDefinitionRelationship();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    aName,
    const occ::handle<TCollection_HAsciiString>&    aDescription,
    const occ::handle<StepRepr_PropertyDefinition>& aRelatingPropertyDefinition,
    const occ::handle<StepRepr_PropertyDefinition>& aRelatedPropertyDefinition);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> RelatingPropertyDefinition() const;

  Standard_EXPORT void SetRelatingPropertyDefinition(
    const occ::handle<StepRepr_PropertyDefinition>& RelatingPropertyDefinition);

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> RelatedPropertyDefinition() const;

  Standard_EXPORT void SetRelatedPropertyDefinition(
    const occ::handle<StepRepr_PropertyDefinition>& RelatedPropertyDefinition);

  DEFINE_STANDARD_RTTIEXT(StepRepr_PropertyDefinitionRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    theDescription;
  occ::handle<StepRepr_PropertyDefinition> theRelatingPropertyDefinition;
  occ::handle<StepRepr_PropertyDefinition> theRelatedPropertyDefinition;
};
