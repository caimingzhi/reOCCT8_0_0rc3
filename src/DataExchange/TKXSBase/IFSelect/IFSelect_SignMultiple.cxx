

#include <IFSelect_SignMultiple.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SignMultiple, IFSelect_Signature)

static TCollection_AsciiString theval;

IFSelect_SignMultiple::IFSelect_SignMultiple(const char* name)
    : IFSelect_Signature(name)
{
}

void IFSelect_SignMultiple::Add(const occ::handle<IFSelect_Signature>& subsign,
                                const int                              tabul,
                                const bool                             maxi)
{
  if (subsign.IsNull())
    return;
  thesubs.Append(subsign);
  thetabs.Append(maxi ? -tabul : tabul);
}

const char* IFSelect_SignMultiple::Value(const occ::handle<Standard_Transient>&       ent,
                                         const occ::handle<Interface_InterfaceModel>& model) const
{
  theval.Clear();
  int i, nb = thesubs.Length();
  for (i = 1; i <= nb; i++)
  {
    int  tabul = thetabs.Value(i);
    bool maxi  = (tabul < 0);
    if (maxi)
      tabul = -tabul;
    occ::handle<IFSelect_Signature> sign = occ::down_cast<IFSelect_Signature>(thesubs.Value(i));
    const char*                     val  = sign->Value(ent, model);
    TCollection_AsciiString         str(val);
    int                             sl = str.Length();
    str.LeftJustify(tabul, ' ');
    if (sl > tabul && maxi)
    {
      str.Remove(sl + 1, tabul - sl);
      str.SetValue(sl, '.');
    }
    str.AssignCat("   ");
    theval.AssignCat(str);
  }
  return theval.ToCString();
}

bool IFSelect_SignMultiple::Matches(const occ::handle<Standard_Transient>&       ent,
                                    const occ::handle<Interface_InterfaceModel>& model,
                                    const TCollection_AsciiString&               text,
                                    const bool                                   exact) const
{
  if (exact)
    return IFSelect_Signature::Matches(ent, model, text, exact);
  int i, nb = thesubs.Length();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IFSelect_Signature> sign = occ::down_cast<IFSelect_Signature>(thesubs.Value(i));
    if (sign->Matches(ent, model, text, exact))
      return true;
  }
  return false;
}
