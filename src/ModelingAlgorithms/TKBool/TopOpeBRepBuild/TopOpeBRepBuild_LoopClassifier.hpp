#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_State.hpp>
class TopOpeBRepBuild_Loop;

class TopOpeBRepBuild_LoopClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~TopOpeBRepBuild_LoopClassifier();

  Standard_EXPORT virtual TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                               const occ::handle<TopOpeBRepBuild_Loop>& L2) = 0;
};
