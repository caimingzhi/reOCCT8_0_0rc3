#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_Area2dBuilder.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;

class TopOpeBRepBuild_FaceAreaBuilder : public TopOpeBRepBuild_Area2dBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_FaceAreaBuilder();

  Standard_EXPORT TopOpeBRepBuild_FaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                  TopOpeBRepBuild_LoopClassifier& LC,
                                                  const bool ForceClass = false);

  Standard_EXPORT void InitFaceAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                           TopOpeBRepBuild_LoopClassifier& LC,
                                           const bool                      ForceClass = false);
};
