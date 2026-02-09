

#include <IFGraph_AllConnected.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>

IFGraph_AllConnected::IFGraph_AllConnected(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

IFGraph_AllConnected::IFGraph_AllConnected(const Interface_Graph&                 agraph,
                                           const occ::handle<Standard_Transient>& ent)
    : thegraph(agraph)
{
  GetFromEntity(ent);
}

void IFGraph_AllConnected::GetFromEntity(const occ::handle<Standard_Transient>& ent)
{
  if (!thegraph.IsPresent(thegraph.EntityNumber(ent)))
    return;
  thegraph.GetFromEntity(ent, false);

  for (Interface_EntityIterator shareds = thegraph.Shareds(ent); shareds.More(); shareds.Next())
    GetFromEntity(shareds.Value());

  for (Interface_EntityIterator sharings = thegraph.Sharings(ent); sharings.More(); sharings.Next())
    GetFromEntity(sharings.Value());
}

void IFGraph_AllConnected::ResetData()
{
  Reset();
  thegraph.Reset();
}

void IFGraph_AllConnected::Evaluate()
{
  GetFromGraph(thegraph);
}
