

#include "RWStepBasic_RWProductCategory.hpp"
#include <StepBasic_ProductCategory.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductCategory::RWStepBasic_RWProductCategory() = default;

void RWStepBasic_RWProductCategory::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepBasic_ProductCategory>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "product_category"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasAdescription = true;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasAdescription = false;
    aDescription.Nullify();
  }

  ent->Init(aName, hasAdescription, aDescription);
}

void RWStepBasic_RWProductCategory::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepBasic_ProductCategory>& ent) const
{

  SW.Send(ent->Name());

  bool hasAdescription = ent->HasDescription();
  if (hasAdescription)
  {
    SW.Send(ent->Description());
  }
  else
  {
    SW.SendUndef();
  }
}
