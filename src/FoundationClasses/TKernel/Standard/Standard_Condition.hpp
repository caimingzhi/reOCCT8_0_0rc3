#pragma once

#include <Standard.hpp>
#include <Standard_Macro.hpp>

#include <atomic>
#include <condition_variable>
#include <chrono>
#include <mutex>

class Standard_Condition
{
public:
  Standard_Condition(bool theIsSet = false)
      : myFlag(theIsSet)
  {
  }

  ~Standard_Condition() = default;

  void Set()
  {
    {
      std::lock_guard<std::mutex> aLock(myMutex);
      myFlag = true;
    }
    myCondition.notify_all();
  }

  void Reset()
  {
    std::lock_guard<std::mutex> aLock(myMutex);
    myFlag = false;
  }

  void Wait()
  {
    std::unique_lock<std::mutex> aLock(myMutex);
    myCondition.wait(aLock, [this] { return myFlag.load(); });
  }

  bool Wait(int theTimeMilliseconds)
  {
    std::unique_lock<std::mutex> aLock(myMutex);
    auto                         aTimeout = std::chrono::milliseconds(theTimeMilliseconds);
    return myCondition.wait_for(aLock, aTimeout, [this] { return myFlag.load(); });
  }

  bool Check() { return myFlag.load(); }

  bool CheckReset()
  {
    std::lock_guard<std::mutex> aLock(myMutex);
    bool                        wasSignalled = myFlag.load();
    myFlag                                   = false;
    return wasSignalled;
  }

private:
  Standard_Condition(const Standard_Condition& theCopy) = delete;

  Standard_Condition& operator=(const Standard_Condition& theCopy) = delete;

private:
  std::mutex              myMutex;
  std::condition_variable myCondition;
  std::atomic<bool>       myFlag;
};
