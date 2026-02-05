#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>
#include <TopOpeBRepBuild_SolidAreaBuilder.hpp>

//=================================================================================================

TopOpeBRepBuild_SolidAreaBuilder::TopOpeBRepBuild_SolidAreaBuilder() = default;

//=================================================================================================

TopOpeBRepBuild_SolidAreaBuilder::TopOpeBRepBuild_SolidAreaBuilder(
  TopOpeBRepBuild_LoopSet&        LS,
  TopOpeBRepBuild_LoopClassifier& LC,
  const bool                      ForceClass)
{
  InitSolidAreaBuilder(LS, LC, ForceClass);
}

//=================================================================================================

void TopOpeBRepBuild_SolidAreaBuilder::InitSolidAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                            TopOpeBRepBuild_LoopClassifier& LC,
                                                            const bool ForceClass)
{
  InitAreaBuilder(LS, LC, ForceClass);
}
