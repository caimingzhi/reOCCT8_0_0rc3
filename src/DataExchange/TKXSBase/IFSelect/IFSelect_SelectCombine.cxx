

#include <IFGraph_Cumulate.hpp>
#include <IFSelect_SelectCombine.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectCombine, IFSelect_Selection)

IFSelect_SelectCombine::IFSelect_SelectCombine() = default;

int IFSelect_SelectCombine::NbInputs() const
{
  return thelist.Length();
}

occ::handle<IFSelect_Selection> IFSelect_SelectCombine::Input(const int num) const
{
  return thelist.Value(num);
}

int IFSelect_SelectCombine::InputRank(const occ::handle<IFSelect_Selection>& sel) const
{
  if (sel.IsNull())
    return 0;
  int i, nb = thelist.Length();
  for (i = 1; i <= nb; i++)
    if (sel == thelist.Value(i))
      return i;
  return 0;
}

void IFSelect_SelectCombine::Add(const occ::handle<IFSelect_Selection>& sel, const int atnum)
{
  if (atnum <= 0 || atnum > thelist.Length())
    thelist.Append(sel);
  else
    thelist.InsertBefore(atnum, sel);
}

bool IFSelect_SelectCombine::Remove(const occ::handle<IFSelect_Selection>& sel)
{
  return Remove(InputRank(sel));
}

bool IFSelect_SelectCombine::Remove(const int num)
{
  if (num <= 0 || num > thelist.Length())
    return false;
  thelist.Remove(num);
  return true;
}

bool IFSelect_SelectCombine::HasUniqueResult() const
{
  return true;
}

void IFSelect_SelectCombine::FillIterator(IFSelect_SelectionIterator& iter) const
{
  iter.AddList(thelist);
}
