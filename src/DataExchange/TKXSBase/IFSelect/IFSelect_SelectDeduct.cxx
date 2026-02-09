

#include <IFSelect_SelectDeduct.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <IFSelect_SelectPointed.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectDeduct, IFSelect_Selection)

void IFSelect_SelectDeduct::SetInput(const occ::handle<IFSelect_Selection>& sel)
{
  thesel = sel;
}

occ::handle<IFSelect_Selection> IFSelect_SelectDeduct::Input() const
{
  return thesel;
}

bool IFSelect_SelectDeduct::HasInput() const
{
  return (!thesel.IsNull());
}

bool IFSelect_SelectDeduct::HasAlternate() const
{
  if (!thealt.IsNull())
    return thealt->IsSet();
  return false;
}

occ::handle<IFSelect_SelectPointed>& IFSelect_SelectDeduct::Alternate()
{
  if (thealt.IsNull())
    thealt = new IFSelect_SelectPointed;
  return thealt;
}

Interface_EntityIterator IFSelect_SelectDeduct::InputResult(const Interface_Graph& G) const
{
  Interface_EntityIterator res;
  if (!thealt.IsNull())
  {
    if (thealt->IsSet())
    {
      res = thealt->UniqueResult(G);
      thealt->Clear();
      return res;
    }
  }
  if (thesel.IsNull())
    return res;
  return thesel->UniqueResult(G);
}

void IFSelect_SelectDeduct::FillIterator(IFSelect_SelectionIterator& iter) const
{
  iter.AddItem(thesel);
}
