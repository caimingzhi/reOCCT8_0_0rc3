#pragma once

#include <Standard.hpp>

#include <StepRepr_CharacterizedDefinition.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepRepr_MaterialDesignation : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_MaterialDesignation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepRepr_CharacterizedDefinition&      aOfDefinition);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetOfDefinition(const StepRepr_CharacterizedDefinition& aOfDefinition);

  Standard_EXPORT StepRepr_CharacterizedDefinition OfDefinition() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_MaterialDesignation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  StepRepr_CharacterizedDefinition      ofDefinition;
};
