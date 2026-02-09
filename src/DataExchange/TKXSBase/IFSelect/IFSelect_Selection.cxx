

#include <IFSelect_Selection.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_Selection, Standard_Transient)

bool IFSelect_Selection::HasUniqueResult() const
{
  return false;
}

Interface_EntityIterator IFSelect_Selection::UniqueResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter = RootResult(G);
  if (HasUniqueResult() || !G.ModeStat())
    return iter;
  Interface_Graph GG(G);
  GG.GetFromIter(iter, 0);
  return Interface_GraphContent(GG);
}

Interface_EntityIterator IFSelect_Selection::CompleteResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter = RootResult(G);

  Interface_Graph GG(G);
  for (iter.Start(); iter.More(); iter.Next())
  {
    const occ::handle<Standard_Transient>& ent = iter.Value();
    GG.GetFromEntity(ent, true);
  }
  return Interface_GraphContent(GG);
}
