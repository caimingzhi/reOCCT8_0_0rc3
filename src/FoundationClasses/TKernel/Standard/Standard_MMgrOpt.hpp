#pragma once

#include <Standard_MMgrRoot.hpp>

#include <mutex>

class Standard_MMgrOpt : public Standard_MMgrRoot
{
public:
  Standard_EXPORT Standard_MMgrOpt(const bool   aClear     = true,
                                   const bool   aMMap      = true,
                                   const size_t aCellSize  = 200,
                                   const int    aNbPages   = 10000,
                                   const size_t aThreshold = 40000);

  Standard_EXPORT ~Standard_MMgrOpt() override;

  Standard_EXPORT void* Allocate(const size_t aSize) override;

  Standard_EXPORT void* Reallocate(void* thePtr, const size_t theSize) override;

  Standard_EXPORT void Free(void* thePtr) override;

  Standard_EXPORT int Purge(bool isDestroyed) override;

  typedef void (*TPCallBackFunc)(const bool   theIsAlloc,
                                 void* const  theStorage,
                                 const size_t theRoundSize,
                                 const size_t theSize);

  Standard_EXPORT static void SetCallBackFunction(TPCallBackFunc pFunc);

protected:
  Standard_EXPORT void Initialize();

  size_t* AllocMemory(size_t& aSize);

  void FreeMemory(void* aPtr, const size_t aSize);

  void FreePools();

protected:
  bool myClear;

  size_t   myFreeListMax;
  size_t** myFreeList;

  size_t  myCellSize;
  int     myNbPages;
  size_t  myPageSize;
  size_t* myAllocList;
  size_t* myNextAddr;
  size_t* myEndBlock;

  int myMMap;

  size_t myThreshold;

  std::mutex myMutex;
  std::mutex myMutexPools;
};
