

#include <IFGraph_StrongComponants.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>

IFGraph_StrongComponants::IFGraph_StrongComponants(const Interface_Graph& agraph, const bool whole)
    : IFGraph_SubPartsIterator(agraph, whole)
{
}

void IFGraph_StrongComponants::Evaluate()
{
  Interface_GraphContent iter = Loaded();
  Interface_Graph        G(thegraph);
  G.GetFromIter(iter, 0);
  int nb = G.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (!G.IsPresent(i))
      continue;
    AddPart();
    GetFromEntity(G.Entity(i), false);
  }
}
