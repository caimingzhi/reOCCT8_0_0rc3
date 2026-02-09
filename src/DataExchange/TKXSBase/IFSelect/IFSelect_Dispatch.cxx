

#include <IFGraph_Compare.hpp>
#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_Dispatch.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_Dispatch, Standard_Transient)

void IFSelect_Dispatch::SetRootName(const occ::handle<TCollection_HAsciiString>& name)
{
  thename = name;
}

bool IFSelect_Dispatch::HasRootName() const
{
  return (!thename.IsNull());
}

const occ::handle<TCollection_HAsciiString>& IFSelect_Dispatch::RootName() const
{
  return thename;
}

void IFSelect_Dispatch::SetFinalSelection(const occ::handle<IFSelect_Selection>& sel)
{
  thefinal = sel;
}

occ::handle<IFSelect_Selection> IFSelect_Dispatch::FinalSelection() const
{
  return thefinal;
}

IFSelect_SelectionIterator IFSelect_Dispatch::Selections() const
{
  IFSelect_SelectionIterator iter;
  iter.AddItem(thefinal);
  for (; iter.More(); iter.Next())
  {
    iter.Value()->FillIterator(iter);
  }
  return iter;
}

bool IFSelect_Dispatch::CanHaveRemainder() const
{
  return false;
}

bool IFSelect_Dispatch::LimitedMax(const int, int& max) const
{
  max = 0;
  return false;
}

Interface_EntityIterator IFSelect_Dispatch::GetEntities(const Interface_Graph& G) const
{
  return thefinal->UniqueResult(G);
}

Interface_EntityIterator IFSelect_Dispatch::Packeted(const Interface_Graph& G) const
{
  Interface_EntityIterator total  = GetEntities(G);
  Interface_EntityIterator remain = Remainder(G);
  if (remain.NbEntities() == 0)
    return total;

  IFGraph_Compare GC(G);
  GC.GetFromIter(total, true);
  GC.GetFromIter(remain, false);
  return GC.FirstOnly();
}

Interface_EntityIterator IFSelect_Dispatch::Remainder(const Interface_Graph&) const
{
  Interface_EntityIterator iter;
  return iter;
}
