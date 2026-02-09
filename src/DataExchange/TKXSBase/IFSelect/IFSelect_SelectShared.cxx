

#include <IFSelect_SelectShared.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectShared, IFSelect_SelectDeduct)

IFSelect_SelectShared::IFSelect_SelectShared() = default;

Interface_EntityIterator IFSelect_SelectShared::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter = InputResult(G);
  Interface_Graph          GG(G);
  for (iter.Start(); iter.More(); iter.Next())
  {
    GG.GetFromIter(G.Shareds(iter.Value()), 0);
  }
  return Interface_GraphContent(GG);
}

TCollection_AsciiString IFSelect_SelectShared::Label() const
{
  return TCollection_AsciiString("Shared Entities (one level)");
}
