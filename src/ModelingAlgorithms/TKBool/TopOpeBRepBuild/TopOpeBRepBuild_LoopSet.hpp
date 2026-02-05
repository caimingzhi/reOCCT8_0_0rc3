#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_Loop.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepBuild_Loop;

class TopOpeBRepBuild_LoopSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_LoopSet();

  Standard_EXPORT virtual ~TopOpeBRepBuild_LoopSet();

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& ChangeListOfLoop();

  Standard_EXPORT virtual void InitLoop();

  Standard_EXPORT virtual bool MoreLoop() const;

  Standard_EXPORT virtual void NextLoop();

  Standard_EXPORT virtual occ::handle<TopOpeBRepBuild_Loop> Loop() const;

private:
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>           myListOfLoop;
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator myLoopIterator;
  int                                                           myLoopIndex;
  int                                                           myNbLoop;
};
