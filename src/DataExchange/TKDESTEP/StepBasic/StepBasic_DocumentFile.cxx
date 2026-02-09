#include <Standard_Type.hpp>
#include <StepBasic_CharacterizedObject.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_DocumentType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentFile, StepBasic_Document)

StepBasic_DocumentFile::StepBasic_DocumentFile()
{
  theCharacterizedObject = new StepBasic_CharacterizedObject;
}

void StepBasic_DocumentFile::Init(
  const occ::handle<TCollection_HAsciiString>& aDocument_Id,
  const occ::handle<TCollection_HAsciiString>& aDocument_Name,
  const bool                                   hasDocument_Description,
  const occ::handle<TCollection_HAsciiString>& aDocument_Description,
  const occ::handle<StepBasic_DocumentType>&   aDocument_Kind,
  const occ::handle<TCollection_HAsciiString>& aCharacterizedObject_Name,
  const bool                                   hasCharacterizedObject_Description,
  const occ::handle<TCollection_HAsciiString>& aCharacterizedObject_Description)
{
  StepBasic_Document::Init(aDocument_Id,
                           aDocument_Name,
                           hasDocument_Description,
                           aDocument_Description,
                           aDocument_Kind);
  theCharacterizedObject->Init(aCharacterizedObject_Name,
                               hasCharacterizedObject_Description,
                               aCharacterizedObject_Description);
}

occ::handle<StepBasic_CharacterizedObject> StepBasic_DocumentFile::CharacterizedObject() const
{
  return theCharacterizedObject;
}

void StepBasic_DocumentFile::SetCharacterizedObject(
  const occ::handle<StepBasic_CharacterizedObject>& aCharacterizedObject)
{
  theCharacterizedObject = aCharacterizedObject;
}
