

#include <IFGraph_AllConnected.hpp>
#include <IFGraph_ConnectedComponants.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>

IFGraph_ConnectedComponants::IFGraph_ConnectedComponants(const Interface_Graph& agraph,
                                                         const bool             whole)
    : IFGraph_SubPartsIterator(agraph, whole)
{
}

void IFGraph_ConnectedComponants::Evaluate()
{

  Interface_EntityIterator loaded = Loaded();
  Reset();
  for (loaded.Start(); loaded.More(); loaded.Next())
  {
    const occ::handle<Standard_Transient>& ent = loaded.Value();
    if (IsInPart(ent))
      continue;
    IFGraph_AllConnected connect(Model(), ent);
    AddPart();
    GetFromIter(connect);
  }
}
