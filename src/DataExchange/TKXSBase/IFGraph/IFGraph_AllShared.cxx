

#include <IFGraph_AllShared.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>

IFGraph_AllShared::IFGraph_AllShared(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

IFGraph_AllShared::IFGraph_AllShared(const Interface_Graph&                 agraph,
                                     const occ::handle<Standard_Transient>& ent)
    : thegraph(agraph)
{
  if (!agraph.Model()->Contains(ent))
    return;
  GetFromEntity(ent);
}

void IFGraph_AllShared::GetFromEntity(const occ::handle<Standard_Transient>& ent)
{
  thegraph.GetFromEntity(ent, true);
}

void IFGraph_AllShared::GetFromIter(const Interface_EntityIterator& iter)
{
  for (iter.Start(); iter.More(); iter.Next())
    thegraph.GetFromEntity(iter.Value(), true);
}

void IFGraph_AllShared::ResetData()
{
  Reset();
  thegraph.Reset();
}

void IFGraph_AllShared::Evaluate()
{
  Reset();
  GetFromGraph(thegraph);
}
