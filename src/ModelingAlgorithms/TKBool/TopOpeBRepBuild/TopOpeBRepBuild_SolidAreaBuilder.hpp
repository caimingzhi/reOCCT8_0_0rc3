#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRepBuild_Area3dBuilder.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

class TopOpeBRepBuild_SolidAreaBuilder : public TopOpeBRepBuild_Area3dBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_SolidAreaBuilder();

  Standard_EXPORT TopOpeBRepBuild_SolidAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                   TopOpeBRepBuild_LoopClassifier& LC,
                                                   const bool ForceClass = false);

  Standard_EXPORT void InitSolidAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                            TopOpeBRepBuild_LoopClassifier& LC,
                                            const bool                      ForceClass = false);
};
