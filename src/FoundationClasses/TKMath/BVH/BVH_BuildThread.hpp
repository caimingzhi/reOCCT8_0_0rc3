#pragma once


#include <OSD_Thread.hpp>
#include <BVH_BuildQueue.hpp>

//! Tool object to call BVH builder subroutines.
struct BVH_BuildTool
{
  //! Performs splitting of the given BVH node.
  virtual void Perform(const int theNode) = 0;
};

//! Wrapper for BVH build thread.
class BVH_BuildThread : public Standard_Transient
{
  template <class T, int N>
  friend class BVH_QueueBuilder;

public:
  //! Creates new BVH build thread.
  Standard_EXPORT BVH_BuildThread(BVH_BuildTool& theBuildTool, BVH_BuildQueue& theBuildQueue);

  //! Starts execution of BVH build thread.
  void Run() { myWorkThread.Run(this); }

  //! Waits till the thread finishes execution.
  void Wait() { myWorkThread.Wait(); }

protected:
  //! Executes BVH build thread.
  Standard_EXPORT void execute();

  //! Thread function for BVH build thread.
  static void* threadFunction(void* theData);

  //! Assignment operator (to remove VC compile warning).
  BVH_BuildThread& operator=(const BVH_BuildThread&);

protected:
  //! Data needed to build the BVH.
  BVH_BuildTool& myBuildTool;

  //! Reference to BVH build queue.
  BVH_BuildQueue& myBuildQueue;

  //! Thread to execute work items.
  OSD_Thread myWorkThread;

public:
  DEFINE_STANDARD_RTTIEXT(BVH_BuildThread, Standard_Transient)
};

