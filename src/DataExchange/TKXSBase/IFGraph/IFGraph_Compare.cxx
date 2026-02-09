

#include <IFGraph_AllShared.hpp>
#include <IFGraph_Compare.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>

IFGraph_Compare::IFGraph_Compare(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

void IFGraph_Compare::GetFromEntity(const occ::handle<Standard_Transient>& ent, const bool first)
{
  IFGraph_AllShared iter(thegraph.Model(), ent);
  GetFromIter(iter, first);
}

void IFGraph_Compare::GetFromIter(const Interface_EntityIterator& iter, const bool first)
{
  int stat = 2;
  if (first)
    stat = 1;
  thegraph.GetFromIter(iter, stat, 3, false);
}

void IFGraph_Compare::Merge()
{
  thegraph.ChangeStatus(2, 1);
  thegraph.ChangeStatus(3, 1);
}

void IFGraph_Compare::RemoveSecond()
{
  thegraph.ChangeStatus(3, 1);
  thegraph.RemoveStatus(2);
}

void IFGraph_Compare::KeepCommon()
{
  thegraph.RemoveStatus(1);
  thegraph.RemoveStatus(2);
  thegraph.ChangeStatus(3, 1);
}

void IFGraph_Compare::ResetData()
{
  Reset();
  thegraph.Reset();
}

void IFGraph_Compare::Evaluate()
{
  Reset();
  GetFromGraph(thegraph);
}

Interface_EntityIterator IFGraph_Compare::Common() const
{
  return Interface_GraphContent(thegraph, 3);
}

Interface_EntityIterator IFGraph_Compare::FirstOnly() const
{
  return Interface_GraphContent(thegraph, 1);
}

Interface_EntityIterator IFGraph_Compare::SecondOnly() const
{
  return Interface_GraphContent(thegraph, 2);
}
