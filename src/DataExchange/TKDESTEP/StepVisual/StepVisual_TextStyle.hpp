#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepVisual_TextStyleForDefinedFont;

class StepVisual_TextStyle : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_TextStyle();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&           aName,
    const occ::handle<StepVisual_TextStyleForDefinedFont>& aCharacterAppearance);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetCharacterAppearance(
    const occ::handle<StepVisual_TextStyleForDefinedFont>& aCharacterAppearance);

  Standard_EXPORT occ::handle<StepVisual_TextStyleForDefinedFont> CharacterAppearance() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TextStyle, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>           name;
  occ::handle<StepVisual_TextStyleForDefinedFont> characterAppearance;
};
