#ifdef _WIN32
  #include <windows.h>
#endif

#include <Standard_MMgrOpt.hpp>
#include <Standard_OutOfMemory.hpp>
#include <Standard_Assert.hpp>

#include <cstring>
#include <cstdio>
#include <cerrno>

#ifndef _WIN32
  #include <unistd.h>
  #include <sys/mman.h>
#endif

#include <fcntl.h>

#if defined(__sun) || defined(SOLARIS)
extern "C" int getpagesize();
#endif

#ifdef _WIN32
  #include <strsafe.h>
#endif

#if defined(__hpux) || defined(HPUX)
  #define MMAP_BASE_ADDRESS 0x80000000
  #define MMAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE | MAP_VARIABLE)
#elif defined(__osf__) || defined(DECOSF1)
  #define MMAP_BASE_ADDRESS 0x1000000000
  #define MMAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE | MAP_VARIABLE)
#elif defined(_AIX)
  #define MMAP_BASE_ADDRESS 0x80000000
  #define MMAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE | MAP_VARIABLE)
#elif defined(__APPLE__)
  #define MMAP_BASE_ADDRESS 0x80000000
  #define MMAP_FLAGS (MAP_ANON | MAP_PRIVATE)
#elif defined(__linux__)
  #define MMAP_BASE_ADDRESS 0x20000000
  #define MMAP_FLAGS (MAP_PRIVATE)
#elif defined(_WIN32)

#else
  #define MMAP_BASE_ADDRESS 0x60000000
  #define MMAP_FLAGS (MAP_PRIVATE)
#endif

#define PAGE_ALIGN(size, thePageSize) (((size) + (thePageSize) - 1) & ~((thePageSize) - 1))

#define ROUNDUP16(size) (((size) + 0xf) & ~(size_t)0xf)
#define ROUNDUP8(size) (((size) + 0x7) & ~(size_t)0x7)
#define ROUNDUP4(size) (((size) + 0x3) & ~(size_t)0x3)
#define ROUNDDOWN8(size) ((size) & ~(size_t)0x7)

#define ROUNDUP_CELL(size) ROUNDUP8(size)
#define ROUNDDOWN_CELL(size) ROUNDDOWN8(size)
#define INDEX_CELL(rsize) ((rsize) >> 3)

#if defined(IRIX) || defined(SOLARIS)
  #define BLOCK_SHIFT 2
#else
  #define BLOCK_SHIFT 1
#endif

#define GET_USER(block) (((size_t*)(block)) + BLOCK_SHIFT)
#define GET_BLOCK(storage) (((size_t*)(storage)) - BLOCK_SHIFT)

Standard_MMgrOpt::Standard_MMgrOpt(const bool   aClear,
                                   const bool   aMMap,
                                   const size_t aCellSize,
                                   const int    aNbPages,
                                   const size_t aThreshold)
{

  Standard_STATIC_ASSERT(sizeof(size_t) == sizeof(void*));

  myFreeListMax = 0;
  myFreeList    = nullptr;
  myPageSize    = 0;
  myAllocList   = nullptr;
  myNextAddr    = nullptr;
  myEndBlock    = nullptr;

  myClear     = aClear;
  myMMap      = (int)aMMap;
  myCellSize  = aCellSize;
  myNbPages   = aNbPages;
  myThreshold = aThreshold;

  Initialize();
}

Standard_MMgrOpt::~Standard_MMgrOpt()
{
  Purge(true);
  free(myFreeList);

  FreePools();
}

void Standard_MMgrOpt::Initialize()
{

  if (myNbPages < 100)
    myNbPages = 1000;

#ifndef _WIN32
  myPageSize = getpagesize();
  if (!myPageSize)
    myMMap = 0;
#else
  SYSTEM_INFO SystemInfo;
  GetSystemInfo(&SystemInfo);
  myPageSize = SystemInfo.dwPageSize;
#endif

  if (myMMap)
  {
#if defined(__sgi) || defined(IRIX)

    char*  var;
    size_t high_sbrk;

    high_sbrk = 700 * 1024 * 1024;
    if ((var = getenv("CLD_HIGH_SBRK")) != NULL)
    {
      high_sbrk = atoi(var);
    }

    var = (char*)malloc(high_sbrk);
    if (var)
      free(var);
    else
      perror("ERR_MEMRY_FAIL");
#endif

#if defined(IRIX) || defined(__sgi) || defined(SOLARIS) || defined(__sun) || defined(__linux__)    \
  || defined(__FreeBSD__) || defined(__ANDROID__)
    if ((myMMap = open("/dev/zero", O_RDWR)) < 0)
    {
      if ((myMMap = open("/dev/null", O_RDWR)) < 0)
      {
        myMMap = 0;
      }
    }
    if (!myMMap)
      perror("ERR_MMAP_FAIL");
#else
    myMMap = -1;
#endif
  }

  myFreeListMax = INDEX_CELL(ROUNDUP_CELL(myThreshold - BLOCK_SHIFT));

  myFreeList = (size_t**)calloc(myFreeListMax + 1, sizeof(size_t*));
  myCellSize = ROUNDUP16(myCellSize);
}

static Standard_MMgrOpt::TPCallBackFunc MyPCallBackFunc = nullptr;

Standard_EXPORT void Standard_MMgrOpt::SetCallBackFunction(TPCallBackFunc pFunc)
{
  MyPCallBackFunc = pFunc;
}

inline void callBack(const bool   isAlloc,
                     void* const  aStorage,
                     const size_t aRoundSize,
                     const size_t aSize)
{
  if (MyPCallBackFunc)
    (*MyPCallBackFunc)(isAlloc, aStorage, aRoundSize, aSize);
}

void* Standard_MMgrOpt::Allocate(const size_t aSize)
{
  size_t* aStorage = nullptr;

  volatile size_t RoundSize = ROUNDUP_CELL(aSize);
  const size_t    Index     = INDEX_CELL(RoundSize);

  if (Index <= myFreeListMax)
  {
    const size_t RoundSizeN = RoundSize / sizeof(size_t);

    myMutex.lock();

    if (myFreeList[Index])
    {

      size_t* aBlock    = myFreeList[Index];
      myFreeList[Index] = *(size_t**)aBlock;

      myMutex.unlock();

      aBlock[0] = RoundSize;
      aStorage  = GET_USER(aBlock);

      if (myClear)
        memset(aStorage, 0, RoundSize);
    }

    else if (RoundSize <= myCellSize)
    {

      myMutex.unlock();

      std::lock_guard<std::mutex> aLock(myMutexPools);

      size_t* aBlock = myNextAddr;
      if (&aBlock[BLOCK_SHIFT + RoundSizeN] > myEndBlock)
      {

        size_t Size = myPageSize * myNbPages;
        aBlock      = AllocMemory(Size);

        if (myEndBlock > myNextAddr)
        {

          const size_t aPSize  = (myEndBlock - GET_USER(myNextAddr)) * sizeof(size_t);
          const size_t aRPSize = ROUNDDOWN_CELL(aPSize);
          const size_t aPIndex = INDEX_CELL(aRPSize);
          if (aPIndex > 0 && aPIndex <= myFreeListMax)
          {
            myMutex.lock();
            *(size_t**)myNextAddr = myFreeList[aPIndex];
            myFreeList[aPIndex]   = myNextAddr;
            myMutex.unlock();
          }
        }

        myEndBlock = aBlock + Size / sizeof(size_t);

        *(size_t**)aBlock = myAllocList;

        myAllocList = aBlock;
        aBlock += BLOCK_SHIFT;
      }

      aBlock[0] = RoundSize;
      aStorage  = GET_USER(aBlock);

      myNextAddr = &aStorage[RoundSizeN];
    }

    else
    {

      myMutex.unlock();

      size_t* aBlock = (size_t*)(myClear ? calloc(RoundSizeN + BLOCK_SHIFT, sizeof(size_t))
                                         : malloc((RoundSizeN + BLOCK_SHIFT) * sizeof(size_t)));

      if (!aBlock)
      {
        if (Purge(false))
          aBlock = (size_t*)calloc(RoundSizeN + BLOCK_SHIFT, sizeof(size_t));

        if (!aBlock)
          throw Standard_OutOfMemory("Standard_MMgrOpt::Allocate(): malloc failed");
      }

      aBlock[0] = RoundSize;
      aStorage  = GET_USER(aBlock);
    }
  }

  else
  {

    size_t AllocSize = RoundSize + sizeof(size_t);

    size_t* aBlock = AllocMemory(AllocSize);

    aBlock[0] = RoundSize;
    aStorage  = GET_USER(aBlock);
  }

  callBack(true, aStorage, RoundSize, aSize);

  return aStorage;
}

void Standard_MMgrOpt::Free(void* theStorage)
{

  if (!theStorage)
    return;

  size_t* aBlock = GET_BLOCK(theStorage);

  size_t RoundSize = aBlock[0];

  callBack(false, theStorage, RoundSize, 0);

  const size_t Index = INDEX_CELL(RoundSize);
  if (Index <= myFreeListMax)
  {

    {
      std::lock_guard<std::mutex> aLock(myMutex);

      *(size_t**)aBlock = myFreeList[Index];

      myFreeList[Index] = aBlock;
    }
  }

  else
    FreeMemory(aBlock, RoundSize);
}

int Standard_MMgrOpt::Purge(bool)
{

  std::lock_guard<std::mutex> aLock(myMutex);

  int    nbFreed = 0;
  size_t i       = INDEX_CELL(ROUNDUP_CELL(myCellSize + BLOCK_SHIFT));
  for (; i <= myFreeListMax; i++)
  {
    size_t* aFree = myFreeList[i];
    while (aFree)
    {
      size_t* anOther = aFree;
      aFree           = *(size_t**)aFree;
      free(anOther);
      nbFreed++;
    }
    myFreeList[i] = nullptr;
  }

  std::lock_guard<std::mutex> aLock1(myMutexPools);

#ifndef _WIN32
  const size_t PoolSize = myPageSize * myNbPages;
#else
  const size_t PoolSize =
    PAGE_ALIGN(myPageSize * myNbPages + sizeof(HANDLE), myPageSize) - sizeof(HANDLE);
#endif
  const size_t RPoolSize = ROUNDDOWN_CELL(PoolSize);
  const size_t PoolSizeN = RPoolSize / sizeof(size_t);

  static const int NB_POOLS_WIN = 512;
  static size_t*   aPools[NB_POOLS_WIN];
  static size_t    aFreeSize[NB_POOLS_WIN];
  static int       aFreePools[NB_POOLS_WIN];

  size_t*      aNextPool = myAllocList;
  size_t*      aPrevPool = nullptr;
  const size_t nCells    = INDEX_CELL(myCellSize);
  int          nPool = 0, nPoolFreed = 0;

  while (aNextPool)
  {

    int iPool;
    for (iPool = 0; aNextPool && iPool < NB_POOLS_WIN; iPool++)
    {
      aPools[iPool]    = aNextPool;
      aFreeSize[iPool] = 0;
      aNextPool        = *(size_t**)aNextPool;
    }
    const int iLast = iPool - 1;

    (void)nPool;
    nPool += iPool;

    for (i = 0; i <= nCells; i++)
    {
      size_t* aFree = myFreeList[i];
      size_t  aSize = BLOCK_SHIFT * sizeof(size_t) + ROUNDUP_CELL(1) * i;
      while (aFree)
      {
        for (iPool = 0; iPool <= iLast; iPool++)
        {
          if (aFree >= aPools[iPool] && aFree < aPools[iPool] + PoolSizeN)
          {
            aFreeSize[iPool] += aSize;
            break;
          }
        }
        aFree = *(size_t**)aFree;
      }
    }

    int iLastFree = -1;
    for (iPool = 0; iPool <= iLast; iPool++)
    {
      aFreeSize[iPool] = ROUNDUP_CELL(aFreeSize[iPool]);
      if (aFreeSize[iPool] == RPoolSize)
        aFreePools[++iLastFree] = iPool;
    }
    if (iLastFree == -1)
    {

      aPrevPool = aPools[iLast];
      continue;
    }

    int j;
    for (i = 0; i <= nCells; i++)
    {
      size_t* aFree     = myFreeList[i];
      size_t* aPrevFree = nullptr;
      while (aFree)
      {
        for (j = 0; j <= iLastFree; j++)
        {
          iPool = aFreePools[j];
          if (aFree >= aPools[iPool] && aFree < aPools[iPool] + PoolSizeN)
            break;
        }
        if (j <= iLastFree)
        {

          aFree = *(size_t**)aFree;
          if (aPrevFree)
            *(size_t**)aPrevFree = aFree;
          else
            myFreeList[i] = aFree;
          nbFreed++;
        }
        else
        {

          aPrevFree = aFree;
          aFree     = *(size_t**)aFree;
        }
      }
    }

    size_t* aPrev = (aFreePools[0] == 0 ? aPrevPool : aPools[aFreePools[0] - 1]);
    for (j = 0; j <= iLastFree; j++)
    {
      iPool = aFreePools[j];
      if (j > 0)
      {

        if (iPool - aFreePools[j - 1] > 1)
          aPrev = aPools[iPool - 1];
      }
      if (j == iLastFree || aFreePools[j + 1] - iPool > 1)
      {

        size_t* aNext = (j == iLastFree && aFreePools[j] == iLast) ? aNextPool : aPools[iPool + 1];

        if (aPrev)
          *(size_t**)aPrev = aNext;
        else
          myAllocList = aNext;
      }
      FreeMemory(aPools[iPool], PoolSize);
    }

    aPrevPool = (aFreePools[iLastFree] == iLast ? aPrev : aPools[iLast]);
    (void)nPoolFreed;
    nPoolFreed += iLastFree + 1;
  }

  return nbFreed;
}

void Standard_MMgrOpt::FreePools()
{

  std::lock_guard<std::mutex> aLock(myMutexPools);

  size_t* aFree = myAllocList;
  myAllocList   = nullptr;
  while (aFree)
  {
    size_t* aBlock = aFree;

    aFree = *(size_t**)aFree;

    FreeMemory(aBlock, myPageSize * myNbPages);
  }
}

void* Standard_MMgrOpt::Reallocate(void* theStorage, const size_t theNewSize)
{

  if (!theStorage)
  {
    return Allocate(theNewSize);
  }

  size_t* aBlock     = GET_BLOCK(theStorage);
  void*   newStorage = nullptr;

  size_t OldSize = aBlock[0];

  if (theNewSize <= OldSize)
  {
    newStorage = theStorage;
  }

  else
  {
    newStorage = Allocate(theNewSize);
    memcpy(newStorage, theStorage, OldSize);
    Free(theStorage);

    if (myClear)
      memset(((char*)newStorage) + OldSize, 0, theNewSize - OldSize);
  }
  return newStorage;
}

size_t* Standard_MMgrOpt::AllocMemory(size_t& Size)
{

retry:

  size_t* aBlock = nullptr;

  if (myMMap)
  {
#ifndef _WIN32

    const size_t AlignedSize = PAGE_ALIGN(Size, myPageSize);

    aBlock = (size_t*)
      mmap((char*)MMAP_BASE_ADDRESS, AlignedSize, PROT_READ | PROT_WRITE, MMAP_FLAGS, myMMap, 0);
    if (aBlock == MAP_FAILED)
    {
      int errcode = errno;

      if (Purge(false))
        goto retry;

      throw Standard_OutOfMemory(strerror(errcode));
    }

    Size = AlignedSize;

#else

    const size_t AlignedSize = PAGE_ALIGN(Size + sizeof(HANDLE), myPageSize);

    HANDLE  hMap    = CreateFileMapping(INVALID_HANDLE_VALUE,
                                    NULL,
                                    PAGE_READWRITE,
                                    DWORD(AlignedSize / 0x80000000),
                                    DWORD(AlignedSize % 0x80000000),
                                    NULL);
    HANDLE* aMBlock = (hMap && GetLastError() != ERROR_ALREADY_EXISTS
                         ? (HANDLE*)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0)
                         : NULL);

    if (!aMBlock)
    {

      if (hMap)
        CloseHandle(hMap);
      hMap = 0;

      if (Purge(false))
        goto retry;

      const int BUFSIZE = 1024;

      wchar_t message[BUFSIZE];

      if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, message, BUFSIZE - 1, 0)
          <= 0)
        StringCchCopyW(message,
                       _countof(message),
                       L"Standard_MMgrOpt::AllocMemory() failed to mmap");

      char messageA[BUFSIZE];
      WideCharToMultiByte(CP_UTF8, 0, message, -1, messageA, sizeof(messageA), NULL, NULL);
      throw Standard_OutOfMemory(messageA);
    }

    aMBlock[0] = hMap;

    aBlock = (size_t*)(aMBlock + 1);

    Size = AlignedSize - sizeof(HANDLE);
#endif
  }

  else
  {
    aBlock = (size_t*)(myClear ? calloc(Size, sizeof(char)) : malloc(Size));

    if (!aBlock)
    {

      if (Purge(false))
        goto retry;

      throw Standard_OutOfMemory("Standard_MMgrOpt::Allocate(): malloc failed");
    }
  }

  if (myClear)
    memset(aBlock, 0, Size);
  return aBlock;
}

void Standard_MMgrOpt::FreeMemory(void* aBlock,
                                  const size_t
#ifndef _WIN32
                                    aSize
#endif
)
{

  if (myMMap)
  {
#ifndef _WIN32

    const size_t AlignedSize = PAGE_ALIGN(aSize, myPageSize);
    munmap((char*)aBlock, AlignedSize);
#else

    const HANDLE* aMBlock = (const HANDLE*)aBlock;
    HANDLE        hMap    = *(--aMBlock);
    UnmapViewOfFile((LPCVOID)aMBlock);
    CloseHandle(hMap);
#endif
  }
  else
    free(aBlock);
}
