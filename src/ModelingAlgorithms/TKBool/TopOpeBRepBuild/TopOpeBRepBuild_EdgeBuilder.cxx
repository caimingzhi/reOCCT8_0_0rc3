#include <TopOpeBRepBuild_EdgeBuilder.hpp>
#include <TopOpeBRepBuild_PaveClassifier.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>

TopOpeBRepBuild_EdgeBuilder::TopOpeBRepBuild_EdgeBuilder() = default;

TopOpeBRepBuild_EdgeBuilder::TopOpeBRepBuild_EdgeBuilder(TopOpeBRepBuild_PaveSet&        LS,
                                                         TopOpeBRepBuild_PaveClassifier& LC,
                                                         const bool                      ForceClass)
{
  InitEdgeBuilder(LS, LC, ForceClass);
}

void TopOpeBRepBuild_EdgeBuilder::InitEdgeBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                  TopOpeBRepBuild_LoopClassifier& LC,
                                                  const bool                      ForceClass)
{
  InitAreaBuilder(LS, LC, ForceClass);
}

void TopOpeBRepBuild_EdgeBuilder::InitEdge()
{
  InitArea();
}

bool TopOpeBRepBuild_EdgeBuilder::MoreEdge() const
{
  bool b = MoreArea();
  return b;
}

void TopOpeBRepBuild_EdgeBuilder::NextEdge()
{
  NextArea();
}

void TopOpeBRepBuild_EdgeBuilder::InitVertex()
{
  InitLoop();
}

bool TopOpeBRepBuild_EdgeBuilder::MoreVertex() const
{
  bool b = MoreLoop();
  return b;
}

void TopOpeBRepBuild_EdgeBuilder::NextVertex()
{
  NextLoop();
}

const TopoDS_Shape& TopOpeBRepBuild_EdgeBuilder::Vertex() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = Loop();
  occ::handle<TopOpeBRepBuild_Pave>        PV(occ::down_cast<TopOpeBRepBuild_Pave>(L));
  const TopoDS_Shape&                      V = PV->Vertex();
  return V;
}

double TopOpeBRepBuild_EdgeBuilder::Parameter() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = Loop();
  occ::handle<TopOpeBRepBuild_Pave>        PV(occ::down_cast<TopOpeBRepBuild_Pave>(L));
  double                                   parV = PV->Parameter();
  return parV;
}
