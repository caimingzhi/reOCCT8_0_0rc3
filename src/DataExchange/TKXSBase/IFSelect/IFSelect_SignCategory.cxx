

#include <IFSelect_SignCategory.hpp>
#include <Interface_Category.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SignCategory, IFSelect_Signature)

static const char* nulsign = "";

IFSelect_SignCategory::IFSelect_SignCategory()
    : IFSelect_Signature("Category")
{
  Interface_Category::Init();
  int i, nb = Interface_Category::NbCategories();
  for (i = 1; i <= nb; i++)
    AddCase(Interface_Category::Name(i));
}

const char* IFSelect_SignCategory::Value(const occ::handle<Standard_Transient>&       ent,
                                         const occ::handle<Interface_InterfaceModel>& model) const
{
  if (ent.IsNull() || model.IsNull())
    return nulsign;
  return Interface_Category::Name(model->CategoryNumber(model->Number(ent)));
}
