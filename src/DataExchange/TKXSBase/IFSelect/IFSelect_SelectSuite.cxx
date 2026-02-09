

#include <IFSelect_SelectPointed.hpp>
#include <IFSelect_SelectSuite.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSuite, IFSelect_SelectDeduct)

IFSelect_SelectSuite::IFSelect_SelectSuite() = default;

bool IFSelect_SelectSuite::AddInput(const occ::handle<IFSelect_Selection>& item)
{
  if (item.IsNull())
    return false;
  occ::handle<IFSelect_Selection> input = Input();
  if (!input.IsNull())
    return false;
  occ::handle<IFSelect_SelectDeduct> first = occ::down_cast<IFSelect_SelectDeduct>(item);
  if (first.IsNull())
    SetInput(item);
  else
    thesel.Prepend(item);
  return true;
}

void IFSelect_SelectSuite::AddPrevious(const occ::handle<IFSelect_SelectDeduct>& item)
{
  if (!item.IsNull())
    thesel.Prepend(item);
}

void IFSelect_SelectSuite::AddNext(const occ::handle<IFSelect_SelectDeduct>& item)
{
  if (!item.IsNull())
    thesel.Append(item);
}

int IFSelect_SelectSuite::NbItems() const
{
  return thesel.Length();
}

occ::handle<IFSelect_SelectDeduct> IFSelect_SelectSuite::Item(const int num) const
{
  return occ::down_cast<IFSelect_SelectDeduct>(thesel.Value(num));
}

void IFSelect_SelectSuite::SetLabel(const char* lab)
{
  thelab.Clear();
  thelab.AssignCat(lab);
}

Interface_EntityIterator IFSelect_SelectSuite::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter;
  bool                     firstin = (HasInput() || HasAlternate());
  if (firstin)
    iter = InputResult(G);

  int i, nb = NbItems();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IFSelect_SelectDeduct> anitem = Item(i);
    if (firstin)
      anitem->Alternate()->SetList(iter.Content());
    firstin = true;
    iter    = anitem->UniqueResult(G);
  }
  return iter;
}

TCollection_AsciiString IFSelect_SelectSuite::Label() const
{
  if (thelab.Length() > 0)
    return thelab;
  char txt[100];
  Sprintf(txt, "Suite of %d Selections", NbItems());
  TCollection_AsciiString lab(txt);
  return lab;
}
