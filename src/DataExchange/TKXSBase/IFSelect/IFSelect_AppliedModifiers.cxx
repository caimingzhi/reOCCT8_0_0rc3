

#include <IFSelect_AppliedModifiers.hpp>
#include <IFSelect_GeneralModifier.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_AppliedModifiers, Standard_Transient)

IFSelect_AppliedModifiers::IFSelect_AppliedModifiers(const int nbmax, const int nbent)
    : thelists(nbmax + 1)
{
  thenbent  = nbent;
  theentcnt = 0;
}

bool IFSelect_AppliedModifiers::AddModif(const occ::handle<IFSelect_GeneralModifier>& modif)
{
  if (themodifs.Length() >= thelists.NbEntities())
    return false;
  themodifs.Append(modif);
  thelists.SetNumber(themodifs.Length());
  return true;
}

bool IFSelect_AppliedModifiers::AddNum(const int nument)
{
  thelists.Add(nument);
  return true;
}

int IFSelect_AppliedModifiers::Count() const
{
  return themodifs.Length();
}

bool IFSelect_AppliedModifiers::Item(const int                              num,
                                     occ::handle<IFSelect_GeneralModifier>& modif,
                                     int&                                   entcount)
{
  if (num < 1 || num > themodifs.Length())
    return false;
  modif = themodifs.Value(num);
  thelists.SetNumber(num);
  theentcnt = thelists.Length();
  entcount  = (theentcnt > 0 ? theentcnt : thenbent);
  return true;
}

int IFSelect_AppliedModifiers::ItemNum(const int nument) const
{
  return (theentcnt > 0 ? thelists.Value(nument) : nument);
}

occ::handle<NCollection_HSequence<int>> IFSelect_AppliedModifiers::ItemList() const
{
  occ::handle<NCollection_HSequence<int>> list = new NCollection_HSequence<int>();
  int                                     i, nb = (theentcnt > 0 ? theentcnt : thenbent);
  for (i = 1; i <= nb; i++)
    list->Append(ItemNum(i));
  return list;
}

bool IFSelect_AppliedModifiers::IsForAll() const
{
  return (theentcnt == 0);
}
