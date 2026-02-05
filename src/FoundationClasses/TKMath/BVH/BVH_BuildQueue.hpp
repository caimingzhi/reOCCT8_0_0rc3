#pragma once

#include <BVH_Builder.hpp>

#include <NCollection_Sequence.hpp>

#include <atomic>
#include <mutex>

//! Command-queue for parallel building of BVH nodes.
class BVH_BuildQueue
{
  template <class T, int N>
  friend class BVH_QueueBuilder;

public:
  //! Creates new BVH build queue.
  BVH_BuildQueue()
      : myNbThreads(0),
        mySize(0)
  {
  }

  //! Releases resources of BVH build queue.
  ~BVH_BuildQueue() = default;

public:
  //! Returns current size of BVH build queue.
  //! Uses acquire semantics to synchronize with enqueue/dequeue operations.
  int Size() const { return mySize.load(std::memory_order_acquire); }

  //! Enqueues new work-item onto BVH build queue.
  void Enqueue(const int theWorkItem)
  {
    std::lock_guard<std::mutex> aLock(myMutex);
    myQueue.Append(theWorkItem);
    mySize.fetch_add(1, std::memory_order_release);
  }

  //! Fetches first work-item from BVH build queue.
  int Fetch(bool& wasBusy)
  {
    int aQuery = -1;

    // Fetch item from queue under lock
    {
      std::lock_guard<std::mutex> aLock(myMutex);
      if (!myQueue.IsEmpty())
      {
        aQuery = myQueue.First();
        myQueue.Remove(1);
        mySize.fetch_sub(1, std::memory_order_release);
      }
    }

    // Update thread counter atomically with release/acquire semantics
    // to ensure proper synchronization with HasBusyThreads()
    if (aQuery != -1)
    {
      if (!wasBusy)
      {
        myNbThreads.fetch_add(1, std::memory_order_release);
      }
    }
    else if (wasBusy)
    {
      myNbThreads.fetch_sub(1, std::memory_order_release);
    }

    wasBusy = (aQuery != -1);
    return aQuery;
  }

  //! Checks if there are active build threads.
  //! Uses acquire semantics to ensure visibility of thread counter updates.
  //! This is critical for termination detection: threads check this after
  //! finding an empty queue to determine if they should exit or wait.
  bool HasBusyThreads() const { return myNbThreads.load(std::memory_order_acquire) != 0; }

private:
  //! Queue of BVH nodes to build.
  NCollection_Sequence<int> myQueue;

  //! Manages access serialization for queue operations.
  std::mutex myMutex;

  //! Number of active build threads (atomic for lock-free reads).
  std::atomic<int> myNbThreads;

  //! Current queue size (atomic for lock-free reads).
  std::atomic<int> mySize;
};
