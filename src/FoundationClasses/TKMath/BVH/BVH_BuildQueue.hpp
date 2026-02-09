#pragma once

#include <BVH_Builder.hpp>

#include <NCollection_Sequence.hpp>

#include <atomic>
#include <mutex>

class BVH_BuildQueue
{
  template <class T, int N>
  friend class BVH_QueueBuilder;

public:
  BVH_BuildQueue()
      : myNbThreads(0),
        mySize(0)
  {
  }

  ~BVH_BuildQueue() = default;

public:
  int Size() const { return mySize.load(std::memory_order_acquire); }

  void Enqueue(const int theWorkItem)
  {
    std::lock_guard<std::mutex> aLock(myMutex);
    myQueue.Append(theWorkItem);
    mySize.fetch_add(1, std::memory_order_release);
  }

  int Fetch(bool& wasBusy)
  {
    int aQuery = -1;

    {
      std::lock_guard<std::mutex> aLock(myMutex);
      if (!myQueue.IsEmpty())
      {
        aQuery = myQueue.First();
        myQueue.Remove(1);
        mySize.fetch_sub(1, std::memory_order_release);
      }
    }

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

  bool HasBusyThreads() const { return myNbThreads.load(std::memory_order_acquire) != 0; }

private:
  NCollection_Sequence<int> myQueue;

  std::mutex myMutex;

  std::atomic<int> myNbThreads;

  std::atomic<int> mySize;
};
