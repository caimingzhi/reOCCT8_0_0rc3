#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductCategoryRelationship.hpp"
#include <StepBasic_ProductCategory.hpp>
#include <StepBasic_ProductCategoryRelationship.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductCategoryRelationship::RWStepBasic_RWProductCategoryRelationship() = default;

void RWStepBasic_RWProductCategoryRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepBasic_ProductCategoryRelationship>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "product_category_relationship"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepBasic_ProductCategory> aCategory;
  data->ReadEntity(num, 3, "category", ach, STANDARD_TYPE(StepBasic_ProductCategory), aCategory);

  occ::handle<StepBasic_ProductCategory> aSubCategory;
  data->ReadEntity(num,
                   4,
                   "sub_category",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductCategory),
                   aSubCategory);

  ent->Init(aName, hasDescription, aDescription, aCategory, aSubCategory);
}

void RWStepBasic_RWProductCategoryRelationship::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepBasic_ProductCategoryRelationship>& ent) const
{

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->Category());

  SW.Send(ent->SubCategory());
}

void RWStepBasic_RWProductCategoryRelationship::Share(
  const occ::handle<StepBasic_ProductCategoryRelationship>& ent,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(ent->Category());

  iter.AddItem(ent->SubCategory());
}
