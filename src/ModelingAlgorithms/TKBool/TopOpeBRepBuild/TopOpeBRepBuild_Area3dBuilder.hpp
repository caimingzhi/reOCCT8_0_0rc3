#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_AreaBuilder.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

class TopOpeBRepBuild_Area3dBuilder : public TopOpeBRepBuild_AreaBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_Area3dBuilder();

  Standard_EXPORT TopOpeBRepBuild_Area3dBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                TopOpeBRepBuild_LoopClassifier& LC,
                                                const bool                      ForceClass = false);

  Standard_EXPORT void InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                       TopOpeBRepBuild_LoopClassifier& LC,
                                       const bool                      ForceClass = false) override;
};
