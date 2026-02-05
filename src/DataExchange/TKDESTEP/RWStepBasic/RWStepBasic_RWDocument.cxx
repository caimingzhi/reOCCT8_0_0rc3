#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocument.hpp"
#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

//=================================================================================================

RWStepBasic_RWDocument::RWStepBasic_RWDocument() = default;

//=================================================================================================

void RWStepBasic_RWDocument::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepBasic_Document>&      ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "document"))
    return;

  // Own fields of Document

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepBasic_DocumentType> aKind;
  data->ReadEntity(num, 4, "kind", ach, STANDARD_TYPE(StepBasic_DocumentType), aKind);

  // Initialize entity
  ent->Init(aId, aName, hasDescription, aDescription, aKind);
}

//=================================================================================================

void RWStepBasic_RWDocument::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepBasic_Document>& ent) const
{

  // Own fields of Document

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->Kind());
}

//=================================================================================================

void RWStepBasic_RWDocument::Share(const occ::handle<StepBasic_Document>& ent,
                                   Interface_EntityIterator&              iter) const
{

  // Own fields of Document

  iter.AddItem(ent->Kind());
}
