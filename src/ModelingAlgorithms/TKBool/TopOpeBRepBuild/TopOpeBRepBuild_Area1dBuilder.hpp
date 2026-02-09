#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_AreaBuilder.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepBuild_Loop.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepBuild_PaveSet;
class TopOpeBRepBuild_PaveClassifier;
class TopOpeBRepBuild_LoopSet;
class TopOpeBRepBuild_LoopClassifier;
class TopOpeBRepBuild_Loop;

class TopOpeBRepBuild_Area1dBuilder : public TopOpeBRepBuild_AreaBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_Area1dBuilder();

  Standard_EXPORT TopOpeBRepBuild_Area1dBuilder(TopOpeBRepBuild_PaveSet&        LS,
                                                TopOpeBRepBuild_PaveClassifier& LC,
                                                const bool                      ForceClass = false);

  Standard_EXPORT void InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                       TopOpeBRepBuild_LoopClassifier& LC,
                                       const bool                      ForceClass = false) override;

  Standard_EXPORT void ADD_Loop_TO_LISTOFLoop(
    const occ::handle<TopOpeBRepBuild_Loop>&             L,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL,
    void* const                                          s = nullptr) const override;

  Standard_EXPORT void REM_Loop_FROM_LISTOFLoop(
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator& ITLOL,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>&           LOL,
    void* const                                                    s = nullptr) const override;

  Standard_EXPORT void ADD_LISTOFLoop_TO_LISTOFLoop(
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL1,
    NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL2,
    void* const                                          s  = nullptr,
    void* const                                          s1 = nullptr,
    void* const                                          s2 = nullptr) const override;

  Standard_EXPORT static void DumpList(
    const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& L);
};
