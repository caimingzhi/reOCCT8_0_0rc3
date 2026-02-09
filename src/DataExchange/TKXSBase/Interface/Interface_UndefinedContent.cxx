

#include <Interface_CopyTool.hpp>
#include <Interface_InterfaceMismatch.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_UndefinedContent, Standard_Transient)

#define Content_TypeField 31
#define Content_LocalField 7
#define Content_LocalRef 1
#define Content_LocalShift 5
#define Content_NumberShift 8

Interface_UndefinedContent::Interface_UndefinedContent()
{
  thenbparams = 0;
  thenbstr    = 0;
}

int Interface_UndefinedContent::NbParams() const
{
  return thenbparams;
}

int Interface_UndefinedContent::NbLiterals() const
{
  return thenbstr;
}

bool Interface_UndefinedContent::ParamData(const int                              num,
                                           Interface_ParamType&                   ptype,
                                           occ::handle<Standard_Transient>&       ent,
                                           occ::handle<TCollection_HAsciiString>& val) const
{
  if (num < 1 || num > thenbparams)
    throw Standard_OutOfRange("Interface UndefinedContent : ParamData");
  int desc  = theparams->Value(num);
  int local = ((desc >> Content_LocalShift) & Content_LocalField);
  ptype     = Interface_ParamType(desc & Content_TypeField);
  int adr   = desc >> Content_NumberShift;
  if (local == Content_LocalRef)
    ent = theentities.Value(adr);
  else
    val = thevalues->Value(adr);
  return (local == Content_LocalRef);
}

Interface_ParamType Interface_UndefinedContent::ParamType(const int num) const
{
  return Interface_ParamType(theparams->Value(num) & Content_TypeField);
}

bool Interface_UndefinedContent::IsParamEntity(const int num) const
{
  return (((theparams->Value(num) >> Content_LocalShift) & Content_LocalField) == Content_LocalRef);
}

occ::handle<Standard_Transient> Interface_UndefinedContent::ParamEntity(const int num) const
{
  int desc = theparams->Value(num);
  if (((desc >> Content_LocalShift) & Content_LocalField) != Content_LocalRef)
    throw Interface_InterfaceError("UndefinedContent : Param is not Entity type");
  return theentities.Value(desc >> Content_NumberShift);
}

occ::handle<TCollection_HAsciiString> Interface_UndefinedContent::ParamValue(const int num) const
{
  int desc = theparams->Value(num);
  if (((desc >> Content_LocalShift) & Content_LocalField) != 0)
    throw Interface_InterfaceError("UndefinedContent : Param is not literal");
  return thevalues->Value(desc >> Content_NumberShift);
}

void Interface_UndefinedContent::Reservate(const int nb, const int nblit)
{

  if (nb > thenbparams)
  {
    if (theparams.IsNull())
      theparams = new NCollection_HArray1<int>(1, nb);
    else if (nb > theparams->Length())
    {
      int nbnew = 2 * thenbparams;
      if (nbnew < nb)
        nbnew = nb;
      occ::handle<NCollection_HArray1<int>> newparams = new NCollection_HArray1<int>(1, nbnew);
      for (int i = 1; i <= thenbparams; i++)
        newparams->SetValue(i, theparams->Value(i));
      theparams = newparams;
    }
  }

  if (nblit > thenbstr)
  {
    if (thevalues.IsNull())
      thevalues = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nblit);
    else if (nblit > thevalues->Length())
    {
      int nbnew = 2 * thenbstr;
      if (nbnew < nblit)
        nbnew = nblit;
      occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> newvalues =
        new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nbnew);
      for (int i = 1; i <= thenbstr; i++)
        newvalues->SetValue(i, thevalues->Value(i));
      thevalues = newvalues;
    }
  }
}

void Interface_UndefinedContent::AddLiteral(const Interface_ParamType                    ptype,
                                            const occ::handle<TCollection_HAsciiString>& val)
{
  Reservate(thenbparams + 1, thenbstr + 1);
  int desc = int(ptype);
  thenbstr++;
  thenbparams++;
  thevalues->SetValue(thenbstr, val);
  desc += (thenbstr << Content_NumberShift);
  theparams->SetValue(thenbparams, desc);
}

void Interface_UndefinedContent::AddEntity(const Interface_ParamType              ptype,
                                           const occ::handle<Standard_Transient>& ent)
{
  Reservate(thenbparams + 1, 0);
  int desc = int(ptype);
  theentities.Append(ent);
  desc += Content_LocalRef << Content_LocalShift;
  thenbparams++;
  desc += ((thenbparams - thenbstr) << Content_NumberShift);
  theparams->SetValue(thenbparams, desc);
}

void Interface_UndefinedContent::RemoveParam(const int num)
{
  int  desc  = theparams->Value(num);
  int  rang  = desc >> Content_NumberShift;
  int  local = ((desc >> Content_LocalShift) & Content_LocalField);
  bool c1ent = (local == Content_LocalRef);

  if (c1ent)
    theentities.Remove(rang);

  else
  {
    for (int i = rang + 1; i <= thenbstr; i++)
      thevalues->SetValue(i - 1, thevalues->Value(i));
    occ::handle<TCollection_HAsciiString> nulstr;
    thevalues->SetValue(thenbstr, nulstr);
    thenbstr--;
  }

  int np;
  for (np = num + 1; np <= thenbparams; np++)
    theparams->SetValue(np - 1, theparams->Value(np));
  theparams->SetValue(thenbparams, 0);
  thenbparams--;

  for (np = 1; np <= thenbparams; np++)
  {
    desc = theparams->Value(np);
    if (((desc >> Content_LocalShift) & Content_LocalField) == local
        && (desc >> Content_NumberShift) > rang)
      theparams->SetValue(np, desc - (1 << Content_NumberShift));
  }
}

void Interface_UndefinedContent::SetLiteral(const int                                    num,
                                            const Interface_ParamType                    ptype,
                                            const occ::handle<TCollection_HAsciiString>& val)
{

  int  desc  = theparams->Value(num);
  int  rang  = desc >> Content_NumberShift;
  int  local = ((desc >> Content_LocalShift) & Content_LocalField);
  bool c1ent = (local == Content_LocalRef);
  if (c1ent)
  {

    theentities.Remove(rang);
    for (int i = 1; i <= thenbparams; i++)
    {
      desc = theparams->Value(i);
      if (((desc >> Content_LocalShift) & Content_LocalField) == Content_LocalRef
          && (desc >> Content_NumberShift) > rang)
        theparams->SetValue(i, desc - (1 << Content_NumberShift));
    }

    Reservate(thenbparams, thenbstr + 1);
    thenbstr++;
    rang = thenbstr;
  }

  thevalues->SetValue(rang, val);
  desc = int(ptype) + (rang << Content_NumberShift);
  theparams->SetValue(num, desc);
}

void Interface_UndefinedContent::SetEntity(const int                              num,
                                           const Interface_ParamType              ptype,
                                           const occ::handle<Standard_Transient>& ent)
{

  int  desc  = theparams->Value(num);
  int  rang  = desc >> Content_NumberShift;
  int  local = ((desc >> Content_LocalShift) & Content_LocalField);
  bool c1ent = (local == Content_LocalRef);
  if (!c1ent)
  {

    int i;
    for (i = rang + 1; i <= thenbstr; i++)
      thevalues->SetValue(i - 1, thevalues->Value(i));
    occ::handle<TCollection_HAsciiString> nulstr;
    thevalues->SetValue(thenbstr, nulstr);

    for (i = 1; i <= thenbparams; i++)
    {
      desc = theparams->Value(i);
      if (((desc >> Content_LocalShift) & Content_LocalField) == 0
          && (desc >> Content_NumberShift) > rang)
        theparams->SetValue(i, desc - (1 << Content_NumberShift));
    }

    thenbstr--;
    rang = thenbparams - thenbstr;

    theentities.Append(ent);
  }
  else
    theentities.SetValue(rang, ent);

  desc = int(ptype) + (Content_LocalRef << Content_LocalShift) + (rang << Content_NumberShift);
  theparams->SetValue(num, desc);
}

void Interface_UndefinedContent::SetEntity(const int                              num,
                                           const occ::handle<Standard_Transient>& ent)
{

  int  desc  = theparams->Value(num);
  int  rang  = desc >> Content_NumberShift;
  int  local = ((desc >> Content_LocalShift) & Content_LocalField);
  bool c1ent = (local == Content_LocalRef);
  if (!c1ent)
    throw Interface_InterfaceError("UndefinedContent : SetEntity");
  theentities.SetValue(rang, ent);
}

Interface_EntityList Interface_UndefinedContent::EntityList() const
{
  return theentities;
}

void Interface_UndefinedContent::GetFromAnother(
  const occ::handle<Interface_UndefinedContent>& other,
  Interface_CopyTool&                            TC)
{
  int nb = other->NbParams();
  theentities.Clear();
  thevalues.Nullify();
  theparams.Nullify();
  Reservate(nb, other->NbLiterals());

  occ::handle<Standard_Transient> ent;
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType                   ptype;
    occ::handle<TCollection_HAsciiString> val;
    if (other->ParamData(i, ptype, ent, val))
    {
      ent = TC.Transferred(ent);
      AddEntity(ptype, ent);
    }
    else
      AddLiteral(ptype, val);
  }
}
