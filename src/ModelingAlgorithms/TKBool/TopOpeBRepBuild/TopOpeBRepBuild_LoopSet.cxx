#include <TopOpeBRepBuild_LoopSet.hpp>

TopOpeBRepBuild_LoopSet::TopOpeBRepBuild_LoopSet()
    : myLoopIndex(1),
      myNbLoop(0)
{
}

TopOpeBRepBuild_LoopSet::~TopOpeBRepBuild_LoopSet() = default;

void TopOpeBRepBuild_LoopSet::InitLoop()
{
  myLoopIterator.Initialize(myListOfLoop);
  myLoopIndex = 1;
  myNbLoop    = myListOfLoop.Extent();
}

bool TopOpeBRepBuild_LoopSet::MoreLoop() const
{
  bool b = myLoopIterator.More();
  return b;
}

void TopOpeBRepBuild_LoopSet::NextLoop()
{
  myLoopIndex++;
  myLoopIterator.Next();
}

occ::handle<TopOpeBRepBuild_Loop> TopOpeBRepBuild_LoopSet::Loop() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = myLoopIterator.Value();
  return L;
}

NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& TopOpeBRepBuild_LoopSet::ChangeListOfLoop()
{
  return myListOfLoop;
}
