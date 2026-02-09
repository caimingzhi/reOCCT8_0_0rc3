#include <TopOpeBRepBuild_FaceAreaBuilder.hpp>
#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>

TopOpeBRepBuild_FaceAreaBuilder::TopOpeBRepBuild_FaceAreaBuilder() = default;

TopOpeBRepBuild_FaceAreaBuilder::TopOpeBRepBuild_FaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                                 TopOpeBRepBuild_LoopClassifier& LC,
                                                                 const bool ForceClass)
{
  InitFaceAreaBuilder(LS, LC, ForceClass);
}

void TopOpeBRepBuild_FaceAreaBuilder::InitFaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                          TopOpeBRepBuild_LoopClassifier& LC,
                                                          const bool ForceClass)
{
  InitAreaBuilder(LS, LC, ForceClass);
}
