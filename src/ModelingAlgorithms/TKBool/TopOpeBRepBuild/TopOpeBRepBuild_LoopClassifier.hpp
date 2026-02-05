#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_State.hpp>
class TopOpeBRepBuild_Loop;

//! classify loops in order to build Areas
class TopOpeBRepBuild_LoopClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~TopOpeBRepBuild_LoopClassifier();

  //! Returns the state of loop <L1> compared with loop <L2>.
  Standard_EXPORT virtual TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                               const occ::handle<TopOpeBRepBuild_Loop>& L2) = 0;
};
