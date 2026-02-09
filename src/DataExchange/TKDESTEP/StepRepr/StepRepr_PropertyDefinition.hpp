#pragma once

#include <Standard.hpp>

#include <StepRepr_CharacterizedDefinition.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepRepr_PropertyDefinition : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_PropertyDefinition();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const StepRepr_CharacterizedDefinition&      aDefinition);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT StepRepr_CharacterizedDefinition Definition() const;

  Standard_EXPORT void SetDefinition(const StepRepr_CharacterizedDefinition& Definition);

  DEFINE_STANDARD_RTTIEXT(StepRepr_PropertyDefinition, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  StepRepr_CharacterizedDefinition      theDefinition;
  bool                                  defDescription;
};
