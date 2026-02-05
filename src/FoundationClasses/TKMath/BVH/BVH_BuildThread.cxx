#include <BVH_BuildThread.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BVH_BuildThread, Standard_Transient)

// =======================================================================
// function : BVH_BuildThread
// purpose  : Creates new BVH build thread
// =======================================================================
BVH_BuildThread::BVH_BuildThread(BVH_BuildTool& theBuildTool, BVH_BuildQueue& theBuildQueue)
    : myBuildTool(theBuildTool),
      myBuildQueue(theBuildQueue),
      myWorkThread(threadFunction)
{
}

// =======================================================================
// function : execute
// purpose  : Executes BVH build thread
// =======================================================================
void BVH_BuildThread::execute()
{
  for (bool wasBusy = false; /**/; /**/)
  {
    const int aNode = myBuildQueue.Fetch(wasBusy);

    if (aNode == -1) // queue is empty
    {
      if (!myBuildQueue.HasBusyThreads())
      {
        break; // no active threads
      }
    }
    else
    {
      myBuildTool.Perform(aNode);
    }
  }
}

// =======================================================================
// function : threadFunction
// purpose  : Thread function for BVH build thread
// =======================================================================
void* BVH_BuildThread::threadFunction(void* theData)
{
  static_cast<BVH_BuildThread*>(theData)->execute();

  return nullptr;
}
