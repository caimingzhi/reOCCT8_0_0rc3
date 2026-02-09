

#include <IFGraph_Articulations.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>

IFGraph_Articulations::IFGraph_Articulations(const Interface_Graph& agraph, const bool whole)
    : thegraph(agraph)
{
  if (whole)
    thegraph.GetFromModel();
}

void IFGraph_Articulations::GetFromEntity(const occ::handle<Standard_Transient>& ent)
{
  thegraph.GetFromEntity(ent, true);
}

void IFGraph_Articulations::GetFromIter(const Interface_EntityIterator& iter)
{
  thegraph.GetFromIter(iter, 0);
}

void IFGraph_Articulations::ResetData()
{
  Reset();
  thegraph.Reset();
  thelist = new NCollection_HSequence<int>();
}

void IFGraph_Articulations::Evaluate()
{

  thelist = new NCollection_HSequence<int>();

  int nb = thegraph.Size();
  for (int i = 1; i <= nb; i++)
  {
    thenow = 0;
    if (thegraph.IsPresent(i))
      Visit(i);
  }

  Reset();
  int nbres = thelist->Length();
  for (int ires = 1; ires <= nbres; ires++)
  {
    int num = thelist->Value(ires);
    GetOneItem(thegraph.Model()->Value(num));
  }
}

int IFGraph_Articulations::Visit(const int num)
{
  thenow++;
  thegraph.SetStatus(num, thenow);
  int min = thenow;

  for (Interface_EntityIterator iter = thegraph.Shareds(thegraph.Entity(num)); iter.More();
       iter.Next())
  {
    const occ::handle<Standard_Transient>& ent    = iter.Value();
    int                                    nument = thegraph.EntityNumber(ent);
    if (!thegraph.IsPresent(num))
    {
      thegraph.GetFromEntity(ent, false);
      nument = thegraph.EntityNumber(ent);
    }
    int statent = thegraph.Status(nument);
    if (statent == 0)
    {
      int mm = Visit(nument);
      if (mm < min)
        min = mm;
      if (mm > thegraph.Status(num))
        thelist->Append(num);
    }
    else if (statent < min)
      min = statent;
  }
  return min;
}
