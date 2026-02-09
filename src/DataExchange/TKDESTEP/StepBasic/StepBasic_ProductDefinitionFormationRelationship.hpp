#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionFormation;

class StepBasic_ProductDefinitionFormationRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ProductDefinitionFormationRelationship();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&             aId,
    const occ::handle<TCollection_HAsciiString>&             aName,
    const occ::handle<TCollection_HAsciiString>&             aDescription,
    const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatingProductDefinitionFormation,
    const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatedProductDefinitionFormation);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation>
                  RelatingProductDefinitionFormation() const;

  Standard_EXPORT void SetRelatingProductDefinitionFormation(
    const occ::handle<StepBasic_ProductDefinitionFormation>& RelatingProductDefinitionFormation);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation>
                  RelatedProductDefinitionFormation() const;

  Standard_EXPORT void SetRelatedProductDefinitionFormation(
    const occ::handle<StepBasic_ProductDefinitionFormation>& RelatedProductDefinitionFormation);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormationRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>             theId;
  occ::handle<TCollection_HAsciiString>             theName;
  occ::handle<TCollection_HAsciiString>             theDescription;
  occ::handle<StepBasic_ProductDefinitionFormation> theRelatingProductDefinitionFormation;
  occ::handle<StepBasic_ProductDefinitionFormation> theRelatedProductDefinitionFormation;
};
