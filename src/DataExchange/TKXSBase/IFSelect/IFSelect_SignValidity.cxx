

#include <IFSelect_SignValidity.hpp>
#include <Interface_Check.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SignValidity, IFSelect_Signature)

static const char* nulsign = "";

IFSelect_SignValidity::IFSelect_SignValidity()
    : IFSelect_Signature("Validity")
{
  AddCase("UNKNOWN");
  AddCase("UNLOADED");
  AddCase("Load-Error");
  AddCase("Data-Error");
  AddCase("Load-Warning");
  AddCase("Data-Warning");
  AddCase("OK");
}

const char* IFSelect_SignValidity::CVal(const occ::handle<Standard_Transient>&       ent,
                                        const occ::handle<Interface_InterfaceModel>& model)
{
  if (ent.IsNull() || model.IsNull())
    return nulsign;
  int num = model->Number(ent);
  int cas = 0;
  if (model->IsUnknownEntity(num))
    return "UNKNOWN";
  if (model->IsRedefinedContent(num))
    return "UNLOADED";

  const occ::handle<Interface_Check> ch1 = model->Check(num, true);
  const occ::handle<Interface_Check> ch2 = model->Check(num, false);
  if (ch1->NbFails() > 0)
    return "Load-Error";
  else if (ch1->NbWarnings() > 0)
    cas = 1;

  if (ch2->NbFails() > 0)
    return "Data-Error";
  else if (cas == 1)
    return "Load-Warning";
  else if (ch2->NbWarnings() > 0)
    return "Data-Warning";

  return "OK";
}

const char* IFSelect_SignValidity::Value(const occ::handle<Standard_Transient>&       ent,
                                         const occ::handle<Interface_InterfaceModel>& model) const
{
  return IFSelect_SignValidity::CVal(ent, model);
}
