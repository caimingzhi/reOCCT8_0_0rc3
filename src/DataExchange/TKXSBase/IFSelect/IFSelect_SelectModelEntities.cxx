

#include <IFSelect_SelectModelEntities.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectModelEntities, IFSelect_SelectBase)

IFSelect_SelectModelEntities::IFSelect_SelectModelEntities() = default;

Interface_EntityIterator IFSelect_SelectModelEntities::RootResult(const Interface_Graph& G) const
{
  return G.Model()->Entities();
}

Interface_EntityIterator IFSelect_SelectModelEntities::CompleteResult(
  const Interface_Graph& G) const
{
  return G.Model()->Entities();
}

TCollection_AsciiString IFSelect_SelectModelEntities::Label() const
{
  return TCollection_AsciiString("All Entities from Model");
}
