

#include <IFSelect_Selection.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <Standard_NoSuchObject.hpp>

IFSelect_SelectionIterator::IFSelect_SelectionIterator()
{
  thecurr = 1;
  thelist = new NCollection_HSequence<occ::handle<IFSelect_Selection>>();
}

IFSelect_SelectionIterator::IFSelect_SelectionIterator(const occ::handle<IFSelect_Selection>& sel)
{
  thecurr = 1;
  thelist = new NCollection_HSequence<occ::handle<IFSelect_Selection>>();
  sel->FillIterator(*this);
}

void IFSelect_SelectionIterator::AddFromIter(IFSelect_SelectionIterator& iter)
{
  for (; iter.More(); iter.Next())
    AddItem(iter.Value());
}

void IFSelect_SelectionIterator::AddItem(const occ::handle<IFSelect_Selection>& sel)
{
  if (!sel.IsNull())
    thelist->Append(sel);
}

void IFSelect_SelectionIterator::AddList(
  const NCollection_Sequence<occ::handle<IFSelect_Selection>>& list)
{
  int nb = list.Length();
  for (int i = 1; i <= nb; i++)
    thelist->Append(list.Value(i));
}

bool IFSelect_SelectionIterator::More() const
{
  return (thecurr <= thelist->Length());
}

void IFSelect_SelectionIterator::Next()
{
  thecurr++;
}

const occ::handle<IFSelect_Selection>& IFSelect_SelectionIterator::Value() const
{
  return thelist->Value(thecurr);
}
