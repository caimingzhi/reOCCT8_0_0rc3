#include "RWStepAP242_RWIdAttribute.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepAP242_IdAttribute.hpp>
#include <StepAP242_IdAttributeSelect.hpp>

RWStepAP242_RWIdAttribute::RWStepAP242_RWIdAttribute() = default;

void RWStepAP242_RWIdAttribute::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepAP242_IdAttribute>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "id_attribute"))
    return;

  occ::handle<TCollection_HAsciiString> anAttributeValue;
  data->ReadString(num, 1, "attribute_value", ach, anAttributeValue);

  StepAP242_IdAttributeSelect anIdentifiedItem;
  data->ReadEntity(num, 2, "identified_item", ach, anIdentifiedItem);

  ent->Init(anAttributeValue, anIdentifiedItem);
}

void RWStepAP242_RWIdAttribute::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepAP242_IdAttribute>& ent) const
{

  SW.Send(ent->AttributeValue());

  SW.Send(ent->IdentifiedItem().Value());
}

void RWStepAP242_RWIdAttribute::Share(const occ::handle<StepAP242_IdAttribute>& ent,
                                      Interface_EntityIterator&                 iter) const
{
  iter.GetOneItem(ent->IdentifiedItem().Value());
}
