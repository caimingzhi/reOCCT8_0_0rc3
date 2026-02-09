#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class TCollection_HAsciiString;
class StepBasic_GeneralProperty;
class StepRepr_PropertyDefinition;

class StepBasic_GeneralPropertyAssociation : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_GeneralPropertyAssociation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const occ::handle<TCollection_HAsciiString>&    aDescription,
                            const occ::handle<StepBasic_GeneralProperty>&   aGeneralProperty,
                            const occ::handle<StepRepr_PropertyDefinition>& aPropertyDefinition);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> GeneralProperty() const;

  Standard_EXPORT void SetGeneralProperty(
    const occ::handle<StepBasic_GeneralProperty>& GeneralProperty);

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT void SetPropertyDefinition(
    const occ::handle<StepRepr_PropertyDefinition>& PropertyDefinition);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GeneralPropertyAssociation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    theDescription;
  occ::handle<StepBasic_GeneralProperty>   theGeneralProperty;
  occ::handle<StepRepr_PropertyDefinition> thePropertyDefinition;
};
