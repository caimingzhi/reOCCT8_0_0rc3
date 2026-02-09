

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>

Interface_GraphContent::Interface_GraphContent() = default;

Interface_GraphContent::Interface_GraphContent(const Interface_Graph& agraph)
{
  GetFromGraph(agraph);
}

Interface_GraphContent::Interface_GraphContent(const Interface_Graph& agraph, const int stat)
{
  GetFromGraph(agraph, stat);
}

Interface_GraphContent::Interface_GraphContent(const Interface_Graph&                 agraph,
                                               const occ::handle<Standard_Transient>& ent)
{
  Interface_EntityIterator list = agraph.Shareds(ent);
  int                      nb   = list.NbEntities();
  if (nb == 0)
    return;
  for (; list.More(); list.Next())
  {
    const occ::handle<Standard_Transient>& curent = list.Value();
    if (agraph.IsPresent(agraph.EntityNumber(curent)))
      GetOneItem(curent);
  }
}

void Interface_GraphContent::GetFromGraph(const Interface_Graph& agraph)
{
  int nb = agraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (agraph.IsPresent(i))
      GetOneItem(agraph.Entity(i));
  }
}

void Interface_GraphContent::GetFromGraph(const Interface_Graph& agraph, const int stat)
{
  int nb = agraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (agraph.IsPresent(i) && agraph.Status(i) == stat)
      GetOneItem(agraph.Entity(i));
  }
}

Interface_EntityIterator Interface_GraphContent::Result()
{
  Interface_EntityIterator iter;
  for (Begin(); More(); Next())
    iter.GetOneItem(Value());
  return iter;
}

void Interface_GraphContent::Begin()
{
  Evaluate();
  Interface_EntityIterator::Start();
}

void Interface_GraphContent::Evaluate() {}
