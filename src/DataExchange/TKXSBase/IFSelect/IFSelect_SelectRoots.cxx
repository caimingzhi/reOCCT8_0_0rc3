

#include <IFGraph_Cumulate.hpp>
#include <IFSelect_SelectRoots.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectRoots, IFSelect_SelectExtract)

IFSelect_SelectRoots::IFSelect_SelectRoots() = default;

Interface_EntityIterator IFSelect_SelectRoots::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator input = InputResult(G);
  Interface_EntityIterator iter;
  IFGraph_Cumulate         GC(G);

  for (input.Start(); input.More(); input.Next())
  {
    const occ::handle<Standard_Transient>& ent = input.Value();
    GC.GetFromEntity(ent);
  }

  for (input.Start(); input.More(); input.Next())
  {
    const occ::handle<Standard_Transient>& ent = input.Value();
    if ((GC.NbTimes(ent) <= 1) == IsDirect())
      iter.GetOneItem(ent);
  }
  return iter;
}

bool IFSelect_SelectRoots::HasUniqueResult() const
{
  return true;
}

bool IFSelect_SelectRoots::Sort(const int,
                                const occ::handle<Standard_Transient>&,
                                const occ::handle<Interface_InterfaceModel>&) const
{
  return true;
}

TCollection_AsciiString IFSelect_SelectRoots::ExtractLabel() const
{
  return TCollection_AsciiString("Local Roots");
}
