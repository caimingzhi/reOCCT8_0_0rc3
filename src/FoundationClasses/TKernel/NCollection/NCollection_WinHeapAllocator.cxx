#include <NCollection_WinHeapAllocator.hpp>
#include <Standard_OutOfMemory.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NCollection_WinHeapAllocator, NCollection_BaseAllocator)

#if (defined(_WIN32) || defined(__WIN32__))
  #include <windows.h>
#endif

NCollection_WinHeapAllocator::NCollection_WinHeapAllocator(const size_t theInitSizeBytes)
    :
#if (defined(_WIN32) || defined(__WIN32__))
      myHeapH(HeapCreate(0, theInitSizeBytes, 0)),
#endif
      myToZeroMemory(false)
{
#if defined(_WIN32) && (_WIN32_WINNT >= 0x0501)

  ULONG aHeapInfo = 2;
  HeapSetInformation(myHeapH, HeapCompatibilityInformation, &aHeapInfo, sizeof(aHeapInfo));
#else
  (void)theInitSizeBytes;
#endif
}

NCollection_WinHeapAllocator::~NCollection_WinHeapAllocator()
{
#if (defined(_WIN32) || defined(__WIN32__))
  HeapDestroy(myHeapH);
#endif
}

void* NCollection_WinHeapAllocator::Allocate(const size_t theSize)
{

  const size_t aRoundSize = (theSize + 3) & ~0x3;
#if (defined(_WIN32) || defined(__WIN32__))
  void* aResult = HeapAlloc(myHeapH, myToZeroMemory ? HEAP_ZERO_MEMORY : 0, aRoundSize);
#else
  void* aResult = malloc(aRoundSize);
#endif
  if (aResult == nullptr)
  {
    char aBuf[128];
    Sprintf(aBuf, "Failed to allocate %" PRIuPTR " bytes in local dynamic heap", theSize);
    throw Standard_OutOfMemory(aBuf);
  }
  return aResult;
}

void NCollection_WinHeapAllocator::Free(void* theAddress)
{
  if (theAddress != nullptr)
  {
#if (defined(_WIN32) || defined(__WIN32__))
    HeapFree(myHeapH, 0, theAddress);
#else
    free(theAddress);
#endif
  }
}
