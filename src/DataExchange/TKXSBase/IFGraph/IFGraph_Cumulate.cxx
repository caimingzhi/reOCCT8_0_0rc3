

#include <IFGraph_AllShared.hpp>
#include <IFGraph_Cumulate.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>

IFGraph_Cumulate::IFGraph_Cumulate(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

void IFGraph_Cumulate::GetFromEntity(const occ::handle<Standard_Transient>& ent)
{
  IFGraph_AllShared iter(thegraph.Model(), ent);
  GetFromIter(iter);
}

void IFGraph_Cumulate::ResetData()
{
  Reset();
  thegraph.Reset();
}

void IFGraph_Cumulate::GetFromIter(const Interface_EntityIterator& iter)
{
  thegraph.GetFromIter(iter, 1, 1, true);
  thegraph.ChangeStatus(1, 2);
}

void IFGraph_Cumulate::Evaluate()
{
  Reset();
  GetFromGraph(thegraph);
}

Interface_EntityIterator IFGraph_Cumulate::Overlapped() const
{
  Interface_EntityIterator iter;
  int                      nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (thegraph.IsPresent(i) && thegraph.Status(i) > 2)
      iter.GetOneItem(thegraph.Entity(i));
  }
  return iter;
}

Interface_EntityIterator IFGraph_Cumulate::Forgotten() const
{
  Interface_EntityIterator iter;
  int                      nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (!thegraph.IsPresent(i))
      iter.GetOneItem(thegraph.Model()->Value(i));
  }
  return iter;
}

Interface_EntityIterator IFGraph_Cumulate::PerCount(const int count) const
{
  Interface_EntityIterator iter;
  int                      nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (thegraph.IsPresent(i) && thegraph.Status(i) == (count + 1))
      iter.GetOneItem(thegraph.Model()->Value(i));
  }
  return iter;
}

int IFGraph_Cumulate::NbTimes(const occ::handle<Standard_Transient>& ent) const
{
  int num = thegraph.EntityNumber(ent);
  if (num == 0)
    return 0;
  int stat = thegraph.Status(num);
  return stat - 1;
}

int IFGraph_Cumulate::HighestNbTimes() const
{
  int max = 0;
  int nb  = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    if (!thegraph.IsPresent(i))
      continue;
    int count = thegraph.Status(i) - 1;
    if (count > max)
      max = count;
  }
  return max;
}
