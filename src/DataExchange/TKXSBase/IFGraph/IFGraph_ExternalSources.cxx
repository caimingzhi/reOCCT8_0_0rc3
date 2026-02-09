

#include <IFGraph_ExternalSources.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>

IFGraph_ExternalSources::IFGraph_ExternalSources(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

void IFGraph_ExternalSources::GetFromEntity(const occ::handle<Standard_Transient>& ent)
{
  thegraph.GetFromEntity(ent, true);
}

void IFGraph_ExternalSources::GetFromIter(const Interface_EntityIterator& iter)
{
  thegraph.GetFromIter(iter, 0);
}

void IFGraph_ExternalSources::ResetData()
{
  Reset();
  thegraph.Reset();
}

void IFGraph_ExternalSources::Evaluate()
{
  Reset();
  thegraph.RemoveStatus(1);
  int nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (thegraph.IsPresent(i) && thegraph.Status(i) == 0)
      thegraph.GetFromIter(thegraph.Sharings(thegraph.Entity(i)), 1);
  }
  GetFromGraph(thegraph, 1);
}

bool IFGraph_ExternalSources::IsEmpty()
{
  Evaluate();
  int nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (thegraph.IsPresent(i) || thegraph.Status(i) == 1)
      return false;
  }
  return true;
}
