

#include <IFSelect_CheckCounter.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_SignText.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_CheckCounter, IFSelect_SignatureList)

IFSelect_CheckCounter::IFSelect_CheckCounter(const bool withlist)
    : IFSelect_SignatureList(withlist)
{
  SetName("Check");
}

void IFSelect_CheckCounter::SetSignature(const occ::handle<MoniTool_SignText>& sign)
{
  thesign = sign;
}

occ::handle<MoniTool_SignText> IFSelect_CheckCounter::Signature() const
{
  return thesign;
}

void IFSelect_CheckCounter::Analyse(const Interface_CheckIterator&               list,
                                    const occ::handle<Interface_InterfaceModel>& model,
                                    const bool                                   original,
                                    const bool                                   failsonly)
{
  int  i, nb, num, nbe = (model.IsNull() ? 0 : model->NbEntities());
  char mess[300];
  Sprintf(mess, "Check %s", list.Name());
  SetName(mess);
  for (list.Start(); list.More(); list.Next())
  {
    num = list.Number();
    occ::handle<Standard_Transient>     ent;
    const occ::handle<Interface_Check>& check = list.Value();
    ent                                       = check->Entity();
    if (ent.IsNull() && num > 0 && num <= nbe)
      ent = model->Value(num);
    nb                = check->NbFails();
    const char* tystr = nullptr;
    if (!ent.IsNull())
    {
      if (!thesign.IsNull())
        tystr = thesign->Text(ent, model).ToCString();
      else if (!model.IsNull())
        tystr = model->TypeName(ent);
      else
        tystr = Interface_InterfaceModel::ClassName(ent->DynamicType()->Name());
    }
    for (i = 1; i <= nb; i++)
    {
      if (ent.IsNull())
        Sprintf(mess, "F: %s", check->CFail(i, original));
      else
        Sprintf(mess, "F:%s: %s", tystr, check->CFail(i, original));
      Add(ent, mess);
    }
    nb = 0;
    if (!failsonly)
      nb = check->NbWarnings();
    for (i = 1; i <= nb; i++)
    {
      if (ent.IsNull())
        Sprintf(mess, "W: %s", check->CWarning(i, original));
      else
        Sprintf(mess, "W:%s: %s", tystr, check->CWarning(i, original));
      Add(ent, mess);
    }
  }
}
