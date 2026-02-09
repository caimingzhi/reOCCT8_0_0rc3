

#include <IFSelect_SelectSharing.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSharing, IFSelect_SelectDeduct)

IFSelect_SelectSharing::IFSelect_SelectSharing() = default;

Interface_EntityIterator IFSelect_SelectSharing::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter = InputResult(G);
  Interface_Graph          GG(G);
  for (iter.Start(); iter.More(); iter.Next())
  {
    GG.GetFromIter(G.Sharings(iter.Value()), 0);
  }
  return Interface_GraphContent(GG);
}

TCollection_AsciiString IFSelect_SelectSharing::Label() const
{
  return TCollection_AsciiString("Sharing Entities (one level)");
}
