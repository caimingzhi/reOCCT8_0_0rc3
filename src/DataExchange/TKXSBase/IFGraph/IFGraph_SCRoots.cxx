

#include <IFGraph_ExternalSources.hpp>
#include <IFGraph_SCRoots.hpp>
#include <IFGraph_StrongComponants.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>

IFGraph_SCRoots::IFGraph_SCRoots(const Interface_Graph& agraph, const bool whole)
    : IFGraph_StrongComponants(agraph, whole)
{
}

IFGraph_SCRoots::IFGraph_SCRoots(IFGraph_StrongComponants& subparts)
    : IFGraph_StrongComponants(subparts)
{
}

void IFGraph_SCRoots::Evaluate()
{
  IFGraph_StrongComponants complist(Model(), false);
  complist.GetFromIter(Loaded());

  Interface_Graph G(thegraph);
#ifdef OCCT_DEBUG
  std::cout << " SCRoots:" << std::endl;
#endif
  G.ResetStatus();
  for (complist.Start(); complist.More(); complist.Next())
  {
    occ::handle<Standard_Transient> ent = complist.FirstEntity();
    int                             num = G.EntityNumber(ent);
#ifdef OCCT_DEBUG
    std::cout << "   Iteration,num=" << num << (G.IsPresent(num) ? " Taken" : " To take")
              << std::endl;
#endif
    if (!G.IsPresent(num))
    {
      G.GetFromEntity(ent, true);
      Interface_EntityIterator list = complist.Entities();
      AddPart();
      GetFromIter(list);
    }
  }
}
