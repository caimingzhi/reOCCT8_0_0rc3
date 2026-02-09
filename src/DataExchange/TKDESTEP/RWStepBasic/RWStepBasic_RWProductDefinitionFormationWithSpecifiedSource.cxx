

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource.hpp"
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinitionFormationWithSpecifiedSource.hpp>
#include <StepBasic_Source.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepBasic_RWSource.hpp"

RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource::
  RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource() = default;

void RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                 data,
  const int                                                                   num,
  occ::handle<Interface_Check>&                                               ach,
  const occ::handle<StepBasic_ProductDefinitionFormationWithSpecifiedSource>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "product_definition_formation_with_specified_source"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepBasic_Product> aOfProduct;

  data->ReadEntity(num, 3, "of_product", ach, STANDARD_TYPE(StepBasic_Product), aOfProduct);

  StepBasic_Source aMakeOrBuy = StepBasic_sNotKnown;
  if (data->ParamType(num, 4) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 4);
    if (!RWStepBasic_RWSource::ConvertToEnum(text, aMakeOrBuy))
    {
      ach->AddFail("Enumeration source has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #4 (make_or_buy) is not an enumeration");

  ent->Init(aId, aDescription, aOfProduct, aMakeOrBuy);
}

void RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource::WriteStep(
  StepData_StepWriter&                                                        SW,
  const occ::handle<StepBasic_ProductDefinitionFormationWithSpecifiedSource>& ent) const
{

  SW.Send(ent->Id());

  SW.Send(ent->Description());

  SW.Send(ent->OfProduct());

  SW.SendEnum(RWStepBasic_RWSource::ConvertToString(ent->MakeOrBuy()));
}

void RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource::Share(
  const occ::handle<StepBasic_ProductDefinitionFormationWithSpecifiedSource>& ent,
  Interface_EntityIterator&                                                   iter) const
{

  iter.GetOneItem(ent->OfProduct());
}
