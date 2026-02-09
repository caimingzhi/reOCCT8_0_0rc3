

#include <IFGraph_Cumulate.hpp>
#include <IFGraph_StrongComponants.hpp>
#include <IFSelect_SelectRootComps.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectRootComps, IFSelect_SelectExtract)

IFSelect_SelectRootComps::IFSelect_SelectRootComps() = default;

Interface_EntityIterator IFSelect_SelectRootComps::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator IEIinput = InputResult(G);
  Interface_EntityIterator iter;

  IFGraph_StrongComponants comps(G, false);
  comps.SetLoad();
  comps.GetFromIter(IEIinput);
  Interface_EntityIterator inp1;

  IFGraph_Cumulate GC(G);

  for (comps.Start(); comps.More(); comps.Next())
  {
    occ::handle<Standard_Transient> ent = comps.FirstEntity();
    GC.GetFromEntity(ent);
    inp1.GetOneItem(ent);
  }

  for (inp1.Start(); inp1.More(); inp1.Next())
  {
    const occ::handle<Standard_Transient>& ent = inp1.Value();
    if ((GC.NbTimes(ent) <= 1) == IsDirect())
      iter.GetOneItem(ent);
  }
  return iter;
}

bool IFSelect_SelectRootComps::HasUniqueResult() const
{
  return true;
}

bool IFSelect_SelectRootComps::Sort(const int,
                                    const occ::handle<Standard_Transient>&,
                                    const occ::handle<Interface_InterfaceModel>&) const
{
  return true;
}

TCollection_AsciiString IFSelect_SelectRootComps::ExtractLabel() const
{
  return TCollection_AsciiString("Local Root Components");
}
