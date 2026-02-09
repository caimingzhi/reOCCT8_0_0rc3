#pragma once

#include <OSD_Thread.hpp>
#include <BVH_BuildQueue.hpp>

struct BVH_BuildTool
{

  virtual void Perform(const int theNode) = 0;
};

class BVH_BuildThread : public Standard_Transient
{
  template <class T, int N>
  friend class BVH_QueueBuilder;

public:
  Standard_EXPORT BVH_BuildThread(BVH_BuildTool& theBuildTool, BVH_BuildQueue& theBuildQueue);

  void Run() { myWorkThread.Run(this); }

  void Wait() { myWorkThread.Wait(); }

protected:
  Standard_EXPORT void execute();

  static void* threadFunction(void* theData);

  BVH_BuildThread& operator=(const BVH_BuildThread&);

protected:
  BVH_BuildTool& myBuildTool;

  BVH_BuildQueue& myBuildQueue;

  OSD_Thread myWorkThread;

public:
  DEFINE_STANDARD_RTTIEXT(BVH_BuildThread, Standard_Transient)
};
