

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductRelatedProductCategory.hpp"
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductRelatedProductCategory::RWStepBasic_RWProductRelatedProductCategory() =
  default;

void RWStepBasic_RWProductRelatedProductCategory::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepBasic_ProductRelatedProductCategory>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "product_related_product_category"))
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

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> aProducts;
  occ::handle<StepBasic_Product>                                   anent3;
  int                                                              nsub3;
  if (data->ReadSubList(num, 3, "products", ach, nsub3))
  {
    int nb3   = data->NbParams(nsub3);
    aProducts = new NCollection_HArray1<occ::handle<StepBasic_Product>>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3, i3, "product", ach, STANDARD_TYPE(StepBasic_Product), anent3))
        aProducts->SetValue(i3, anent3);
    }
  }

  ent->Init(aName, hasAdescription, aDescription, aProducts);
}

void RWStepBasic_RWProductRelatedProductCategory::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepBasic_ProductRelatedProductCategory>& ent) const
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

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbProducts(); i3++)
  {
    SW.Send(ent->ProductsValue(i3));
  }
  SW.CloseSub();
}

void RWStepBasic_RWProductRelatedProductCategory::Share(
  const occ::handle<StepBasic_ProductRelatedProductCategory>& ent,
  Interface_EntityIterator&                                   iter) const
{

  int nbElem1 = ent->NbProducts();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ProductsValue(is1));
  }
}
