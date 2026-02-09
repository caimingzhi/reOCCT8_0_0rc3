

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDocumentType.hpp"
#include <StepBasic_DocumentType.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepBasic_RWDocumentType::RWStepBasic_RWDocumentType() = default;

void RWStepBasic_RWDocumentType::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepBasic_DocumentType>&  ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "document_type"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "product_data_type", ach, aId);

  ent->Init(aId);
}

void RWStepBasic_RWDocumentType::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepBasic_DocumentType>& ent) const
{

  SW.Send(ent->ProductDataType());
}

void RWStepBasic_RWDocumentType::Share(const occ::handle<StepBasic_DocumentType>&,
                                       Interface_EntityIterator&) const
{
}
