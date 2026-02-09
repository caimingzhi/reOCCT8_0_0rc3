#include <BVH_BuildThread.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BVH_BuildThread, Standard_Transient)

BVH_BuildThread::BVH_BuildThread(BVH_BuildTool& theBuildTool, BVH_BuildQueue& theBuildQueue)
    : myBuildTool(theBuildTool),
      myBuildQueue(theBuildQueue),
      myWorkThread(threadFunction)
{
}

void BVH_BuildThread::execute()
{
  for (bool wasBusy = false;;)
  {
    const int aNode = myBuildQueue.Fetch(wasBusy);

    if (aNode == -1)
    {
      if (!myBuildQueue.HasBusyThreads())
      {
        break;
      }
    }
    else
    {
      myBuildTool.Perform(aNode);
    }
  }
}

void* BVH_BuildThread::threadFunction(void* theData)
{
  static_cast<BVH_BuildThread*>(theData)->execute();

  return nullptr;
}
