

#include <IFSelect_SelectModelRoots.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectModelRoots, IFSelect_SelectBase)

IFSelect_SelectModelRoots::IFSelect_SelectModelRoots() = default;

Interface_EntityIterator IFSelect_SelectModelRoots::RootResult(const Interface_Graph& G) const
{
  return G.RootEntities();
}

TCollection_AsciiString IFSelect_SelectModelRoots::Label() const
{
  return TCollection_AsciiString("Root (not shared) Entities from Model");
}
