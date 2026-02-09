

#include <IFGraph_Cycles.hpp>
#include <IFGraph_StrongComponants.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>

IFGraph_Cycles::IFGraph_Cycles(const Interface_Graph& agraph, const bool whole)
    : IFGraph_SubPartsIterator(agraph, whole)
{
}

IFGraph_Cycles::IFGraph_Cycles(IFGraph_StrongComponants& subparts)
    : IFGraph_SubPartsIterator(subparts)
{
}

void IFGraph_Cycles::Evaluate()
{
  IFGraph_StrongComponants complist(Model(), false);
  complist.GetFromIter(Loaded());
  for (complist.Start(); complist.More(); complist.Next())
  {
    if (complist.IsSingle())
      continue;
    AddPart();
    GetFromIter(complist.Entities());
  }
}
