

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionFormation.hpp"
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionFormation::RWStepBasic_RWProductDefinitionFormation() = default;

void RWStepBasic_RWProductDefinitionFormation::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepBasic_ProductDefinitionFormation>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "product_definition_formation"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepBasic_Product> aOfProduct;

  data->ReadEntity(num, 3, "of_product", ach, STANDARD_TYPE(StepBasic_Product), aOfProduct);

  ent->Init(aId, aDescription, aOfProduct);
}

void RWStepBasic_RWProductDefinitionFormation::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepBasic_ProductDefinitionFormation>& ent) const
{

  SW.Send(ent->Id());

  if (!ent->Description().IsNull())
  {
    SW.Send(ent->Description());
  }
  else
  {
    SW.SendUndef();
  }

  SW.Send(ent->OfProduct());
}

void RWStepBasic_RWProductDefinitionFormation::Share(
  const occ::handle<StepBasic_ProductDefinitionFormation>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.GetOneItem(ent->OfProduct());
}
