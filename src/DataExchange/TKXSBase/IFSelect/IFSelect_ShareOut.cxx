

#include <IFSelect_Dispatch.hpp>
#include <IFSelect_Modifier.hpp>
#include <IFSelect_ShareOut.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_ShareOut, Standard_Transient)

IFSelect_ShareOut::IFSelect_ShareOut()
{
  thedefrt  = new TCollection_HAsciiString("Default");
  thenbdefs = thelastrun = 0;
}

void IFSelect_ShareOut::Clear(const bool onlydisp)
{
  thedisps.Clear();
  ClearResult(!onlydisp);
  if (onlydisp)
    return;
  themodelmodifiers.Clear();
  thefilemodifiers.Clear();
}

bool IFSelect_ShareOut::RemoveItem(const occ::handle<Standard_Transient>& item)
{
  DeclareAndCast(IFSelect_GeneralModifier, modifier, item);
  if (!modifier.IsNull())
  {
    bool formodel = modifier->IsKind(STANDARD_TYPE(IFSelect_Modifier));
    int  atnum    = ModifierRank(modifier);
    return RemoveModifier(formodel, atnum);
  }
  DeclareAndCast(IFSelect_Dispatch, disp, item);
  if (!disp.IsNull())
  {
    int atnum = DispatchRank(disp);
    return RemoveDispatch(atnum);
  }
  return false;
}

void IFSelect_ShareOut::ClearResult(const bool alsoname)
{
  thelastrun = 0;
  if (alsoname)
    thenbdefs = 0;
}

int IFSelect_ShareOut::LastRun() const
{
  return thelastrun;
}

void IFSelect_ShareOut::SetLastRun(const int lastrun)
{
  thelastrun = lastrun;
}

int IFSelect_ShareOut::NbDispatches() const
{
  return thedisps.Length();
}

int IFSelect_ShareOut::DispatchRank(const occ::handle<IFSelect_Dispatch>& disp) const
{
  if (disp.IsNull())
    return 0;
  for (int i = thedisps.Length(); i >= 1; i--)
    if (disp == thedisps.Value(i))
      return i;
  return 0;
}

const occ::handle<IFSelect_Dispatch>& IFSelect_ShareOut::Dispatch(const int num) const
{
  return thedisps.Value(num);
}

void IFSelect_ShareOut::AddDispatch(const occ::handle<IFSelect_Dispatch>& disp)
{
  if (disp.IsNull())
    return;
  thedisps.Append(disp);
}

bool IFSelect_ShareOut::RemoveDispatch(const int rank)
{
  if (rank <= thelastrun || rank > thedisps.Length())
    return false;
  thedisps.Remove(rank);
  return true;
}

void IFSelect_ShareOut::AddModifier(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                    const int                                    atnum)
{
  bool formodel = modifier->IsKind(STANDARD_TYPE(IFSelect_Modifier));
  if (ModifierRank(modifier) == 0)
    AddModif(modifier, formodel, atnum);
  occ::handle<IFSelect_Dispatch> nuldisp;
  modifier->SetDispatch(nuldisp);
}

void IFSelect_ShareOut::AddModifier(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                    const int                                    dispnum,
                                    const int                                    atnum)
{
  bool formodel = modifier->IsKind(STANDARD_TYPE(IFSelect_Modifier));
  if (ModifierRank(modifier) == 0)
    AddModif(modifier, formodel, atnum);
  occ::handle<IFSelect_Dispatch> disp = Dispatch(dispnum);
  modifier->SetDispatch(disp);
}

void IFSelect_ShareOut::AddModif(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                 const bool                                   formodel,
                                 const int                                    atnum)
{
  if (formodel)
  {
    if (atnum > 0 && atnum <= themodelmodifiers.Length())
      themodelmodifiers.InsertBefore(atnum, modifier);
    else
      themodelmodifiers.Append(modifier);
  }
  else
  {
    if (atnum > 0 && atnum <= thefilemodifiers.Length())
      thefilemodifiers.InsertBefore(atnum, modifier);
    else
      thefilemodifiers.Append(modifier);
  }
}

int IFSelect_ShareOut::NbModifiers(const bool formodel) const
{
  if (formodel)
    return themodelmodifiers.Length();
  else
    return thefilemodifiers.Length();
}

occ::handle<IFSelect_GeneralModifier> IFSelect_ShareOut::GeneralModifier(const bool formodel,
                                                                         const int  atnum) const
{
  if (formodel)
    return themodelmodifiers.Value(atnum);
  else
    return thefilemodifiers.Value(atnum);
}

occ::handle<IFSelect_Modifier> IFSelect_ShareOut::ModelModifier(const int num) const
{
  return occ::down_cast<IFSelect_Modifier>(themodelmodifiers.Value(num));
}

int IFSelect_ShareOut::ModifierRank(const occ::handle<IFSelect_GeneralModifier>& modifier) const
{
  int  i;
  bool formodel = modifier->IsKind(STANDARD_TYPE(IFSelect_Modifier));
  if (formodel)
  {
    for (i = themodelmodifiers.Length(); i >= 1; i--)
      if (modifier == themodelmodifiers.Value(i))
        return i;
  }
  else
  {
    for (i = thefilemodifiers.Length(); i >= 1; i--)
      if (modifier == thefilemodifiers.Value(i))
        return i;
  }
  return 0;
}

bool IFSelect_ShareOut::RemoveModifier(const bool formodel, const int atnum)
{
  if (atnum <= 0)
    return false;
  if (formodel)
  {
    if (atnum > themodelmodifiers.Length())
      return false;
    themodelmodifiers.Remove(atnum);
  }
  else
  {
    if (atnum > thefilemodifiers.Length())
      return false;
    thefilemodifiers.Remove(atnum);
  }
  return true;
}

bool IFSelect_ShareOut::ChangeModifierRank(const bool formodel, const int before, const int after)
{
  int nb;
  if (before <= 0 || after <= 0)
    return false;
  if (before == after)
    return true;
  if (formodel)
  {
    nb = themodelmodifiers.Length();
    if (before > nb || after > nb)
      return false;
    occ::handle<IFSelect_GeneralModifier> bef = themodelmodifiers.Value(before);
    themodelmodifiers.Remove(before);
    if (after == nb)
      themodelmodifiers.Append(bef);
    else
      themodelmodifiers.InsertBefore(after, bef);
  }
  else
  {
    nb = thefilemodifiers.Length();
    if (before > nb || after > nb)
      return false;
    occ::handle<IFSelect_GeneralModifier> bef = thefilemodifiers.Value(before);
    thefilemodifiers.Remove(before);
    if (after == nb)
      thefilemodifiers.Append(bef);
    else
      thefilemodifiers.InsertBefore(after, bef);
  }
  return true;
}

bool IFSelect_ShareOut::SetRootName(const int                                    num,
                                    const occ::handle<TCollection_HAsciiString>& name)
{
  if (num < 1 || num > thedisps.Length())
    return false;
  if (RootNumber(name) != 0)
    return false;
  Dispatch(num)->SetRootName(name);
  return true;
}

bool IFSelect_ShareOut::HasRootName(const int num) const
{
  if (num < 1 || num > thedisps.Length())
    return false;
  return Dispatch(num)->HasRootName();
}

occ::handle<TCollection_HAsciiString> IFSelect_ShareOut::RootName(const int num) const
{
  occ::handle<TCollection_HAsciiString> nulname;
  if (num < 1 || num > thedisps.Length())
    return nulname;
  return Dispatch(num)->RootName();
}

int IFSelect_ShareOut::RootNumber(const occ::handle<TCollection_HAsciiString>& name) const
{
  if (name.IsNull())
    return 0;
  if (!thedefrt.IsNull())
  {
    if (thedefrt->IsSameString(name))
      return -1;
  }
  for (int i = 1; i <= thedisps.Length(); i++)
  {
    occ::handle<TCollection_HAsciiString> root = thedisps.Value(i)->RootName();
    if (root.IsNull())
      continue;
    if (root->IsSameString(name))
      return i;
  }
  return 0;
}

void IFSelect_ShareOut::SetPrefix(const occ::handle<TCollection_HAsciiString>& pref)
{
  thepref   = pref;
  thenbdefs = 0;
}

bool IFSelect_ShareOut::SetDefaultRootName(const occ::handle<TCollection_HAsciiString>& defrt)
{
  if (RootNumber(defrt) != 0)
    return false;
  if (thedefrt.IsNull() || !thedefrt->IsSameString(defrt))
    thenbdefs = 0;
  thedefrt = defrt;
  return true;
}

void IFSelect_ShareOut::SetExtension(const occ::handle<TCollection_HAsciiString>& ext)
{
  theext    = ext;
  thenbdefs = 0;
}

occ::handle<TCollection_HAsciiString> IFSelect_ShareOut::Prefix() const
{
  if (thepref.IsNull())
    return new TCollection_HAsciiString("");
  return thepref;
}

occ::handle<TCollection_HAsciiString> IFSelect_ShareOut::DefaultRootName() const
{
  if (thedefrt.IsNull())
    return new TCollection_HAsciiString("");
  return thedefrt;
}

occ::handle<TCollection_HAsciiString> IFSelect_ShareOut::Extension() const
{
  if (theext.IsNull())
    return new TCollection_HAsciiString("");
  return theext;
}

TCollection_AsciiString IFSelect_ShareOut::FileName(const int dnum,
                                                    const int pnum,
                                                    const int nbpack)
{
  occ::handle<TCollection_HAsciiString> rot    = RootName(dnum);
  int                                   num    = pnum;
  int                                   npac   = nbpack;
  bool                                  sufnum = (npac > 1 || num > 1);
  if (rot.IsNull())
  {
    rot = thedefrt;
    thenbdefs++;
    num    = thenbdefs;
    npac   = 0;
    sufnum = true;
  }

  TCollection_AsciiString res;
  if (!thepref.IsNull())
    res.AssignCat(thepref->ToCString());
  if (!rot.IsNull())
    res.AssignCat(rot->ToCString());

  if (sufnum)
  {

    int  nbch = 0;
    char format[30], suffixe[30];
    format[1] = ' ';
    if (npac >= num)
    {
      int nbpa = 1;
      while (nbpa <= npac)
      {
        nbpa *= 10;
        nbch++;
      }
    }
    if (nbch > 1)
    {
      Sprintf(format, "_ %d.%dd", nbch, nbch);
      format[1] = '%';
    }
    else if (npac >= num || num >= 1)
    {
      Sprintf(format, "_ d");
      format[1] = '%';
    }
    if (format[1] == '%')
    {
      Sprintf(suffixe, format, num);
      res.AssignCat(suffixe);
    }
  }

  if (!theext.IsNull())
    res.AssignCat(theext->ToCString());
  return res;
}
