#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Document.hpp>
class StepBasic_CharacterizedObject;
class TCollection_HAsciiString;
class StepBasic_DocumentType;

class StepBasic_DocumentFile : public StepBasic_Document
{

public:
  Standard_EXPORT StepBasic_DocumentFile();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aDocument_Id,
    const occ::handle<TCollection_HAsciiString>& aDocument_Name,
    const bool                                   hasDocument_Description,
    const occ::handle<TCollection_HAsciiString>& aDocument_Description,
    const occ::handle<StepBasic_DocumentType>&   aDocument_Kind,
    const occ::handle<TCollection_HAsciiString>& aCharacterizedObject_Name,
    const bool                                   hasCharacterizedObject_Description,
    const occ::handle<TCollection_HAsciiString>& aCharacterizedObject_Description);

  Standard_EXPORT occ::handle<StepBasic_CharacterizedObject> CharacterizedObject() const;

  Standard_EXPORT void SetCharacterizedObject(
    const occ::handle<StepBasic_CharacterizedObject>& CharacterizedObject);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentFile, StepBasic_Document)

private:
  occ::handle<StepBasic_CharacterizedObject> theCharacterizedObject;
};
