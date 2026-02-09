#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentFile.hpp"
#include <StepBasic_CharacterizedObject.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_DocumentType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDocumentFile::RWStepBasic_RWDocumentFile() = default;

void RWStepBasic_RWDocumentFile::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_DocumentFile>&  ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "document_file"))
    return;

  occ::handle<TCollection_HAsciiString> aDocument_Id;
  data->ReadString(num, 1, "document.id", ach, aDocument_Id);

  occ::handle<TCollection_HAsciiString> aDocument_Name;
  data->ReadString(num, 2, "document.name", ach, aDocument_Name);

  occ::handle<TCollection_HAsciiString> aDocument_Description;
  bool                                  hasDocument_Description = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "document.description", ach, aDocument_Description);
  }
  else
  {
    hasDocument_Description = false;
  }

  occ::handle<StepBasic_DocumentType> aDocument_Kind;
  data->ReadEntity(num,
                   4,
                   "document.kind",
                   ach,
                   STANDARD_TYPE(StepBasic_DocumentType),
                   aDocument_Kind);

  occ::handle<TCollection_HAsciiString> aCharacterizedObject_Name;
  data->ReadString(num, 5, "characterized_object.name", ach, aCharacterizedObject_Name);

  occ::handle<TCollection_HAsciiString> aCharacterizedObject_Description;
  bool                                  hasCharacterizedObject_Description = true;
  if (data->IsParamDefined(num, 6))
  {
    data->ReadString(num,
                     6,
                     "characterized_object.description",
                     ach,
                     aCharacterizedObject_Description);
  }
  else
  {
    hasCharacterizedObject_Description = false;
  }

  ent->Init(aDocument_Id,
            aDocument_Name,
            hasDocument_Description,
            aDocument_Description,
            aDocument_Kind,
            aCharacterizedObject_Name,
            hasCharacterizedObject_Description,
            aCharacterizedObject_Description);
}

void RWStepBasic_RWDocumentFile::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_DocumentFile>& ent) const
{

  SW.Send(ent->StepBasic_Document::Id());

  SW.Send(ent->StepBasic_Document::Name());

  if (ent->StepBasic_Document::HasDescription())
  {
    SW.Send(ent->StepBasic_Document::Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->StepBasic_Document::Kind());

  SW.Send(ent->CharacterizedObject()->Name());

  if (ent->CharacterizedObject()->HasDescription())
  {
    SW.Send(ent->CharacterizedObject()->Description());
  }
  else
    SW.SendUndef();
}

void RWStepBasic_RWDocumentFile::Share(const occ::handle<StepBasic_DocumentFile>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.AddItem(ent->StepBasic_Document::Kind());
}
