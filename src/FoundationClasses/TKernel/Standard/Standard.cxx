

#include <Standard.hpp>

#include <Standard_OutOfMemory.hpp>

#include <cstdlib>

#if (defined(_WIN32) || defined(__WIN32__))
  #include <windows.h>
  #include <malloc.h>
  #include <locale.h>
#endif

#if defined(_MSC_VER) || defined(__ANDROID__) || defined(__QNX__)
  #include <malloc.h>
#elif (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))               \
       && (defined(__i386) || defined(__x86_64)))
  #include <mm_malloc.h>
#else
extern "C" int posix_memalign(void** thePtr, size_t theAlign, size_t theSize);
#endif

namespace
{
  static Standard::AllocatorType& allocatorTypeInstance()
  {
    static Standard::AllocatorType aType =
#ifdef OCCT_MMGT_OPT_FLEXIBLE
      Standard::AllocatorType::NATIVE;
#elif defined OCCT_MMGT_OPT_TBB
      Standard::AllocatorType::TBB;
#elif defined OCCT_MMGT_OPT_JEMALLOC
      Standard::AllocatorType::JEMALLOC;
#else
      Standard::AllocatorType::NATIVE;
#endif
    return aType;
  }
} // namespace

#ifdef OCCT_MMGT_OPT_JEMALLOC
  #define JEMALLOC_NO_DEMANGLE
  #include <jemalloc.h>
#endif

#ifdef HAVE_TBB
  #include <tbb/scalable_allocator.h>
#else
  #ifdef OCCT_MMGT_OPT_TBB
    #undef OCCT_MMGT_OPT_TBB
  #endif
  #define scalable_malloc malloc
  #define scalable_calloc calloc
  #define scalable_realloc realloc
  #define scalable_free free
#endif

#ifdef OCCT_MMGT_OPT_FLEXIBLE
  #include <Standard_MMgrOpt.hpp>
  #include <Standard_Assert.hpp>

  #ifdef OCCT_UWP
    #define getenv(x) NULL
  #endif

  #ifndef OCCT_MMGT_OPT_DEFAULT
    #define OCCT_MMGT_OPT_DEFAULT 0
  #endif
namespace
{

  class Standard_MMgrRaw : public Standard_MMgrRoot
  {
  public:
    Standard_MMgrRaw(const bool theToClear = false) { myClear = theToClear; }

    void* Allocate(const size_t theSize) override
    {

      void* aPtr = (myClear ? calloc(theSize, sizeof(char)) : malloc(theSize));
      if (!aPtr)
        throw Standard_OutOfMemory("Standard_MMgrRaw::Allocate(): malloc failed");
      return aPtr;
    }

    void* Reallocate(void* thePtr, const size_t theSize) override
    {
      void* aNewStorage = (void*)realloc(thePtr, theSize);
      if (!aNewStorage)
        throw Standard_OutOfMemory("Standard_MMgrRaw::Reallocate(): realloc failed");

      return aNewStorage;
    }

    void Free(void* thePtr) override { free(thePtr); }

  protected:
    bool myClear;
  };

  class Standard_MMgrTBBalloc : public Standard_MMgrRoot
  {
  public:
    Standard_MMgrTBBalloc(const bool theClear = false) { myClear = theClear; }

    void* Allocate(const size_t theSize) override
    {

      void* aPtr = (myClear ? scalable_calloc(theSize, sizeof(char)) : scalable_malloc(theSize));
      if (!aPtr)
        throw Standard_OutOfMemory("Standard_MMgrTBBalloc::Allocate(): malloc failed");
      return aPtr;
    }

    void* Reallocate(void* thePtr, const size_t theSize) override
    {
      void* aNewStorage = (void*)scalable_realloc(thePtr, theSize);
      if (!aNewStorage)
        throw Standard_OutOfMemory("Standard_MMgrTBBalloc::Reallocate(): realloc failed");

      return aNewStorage;
    }

    void Free(void* thePtr) override { scalable_free(thePtr); }

  protected:
    bool myClear;
  };

  class Standard_MMgrFactory
  {
  public:
    static Standard_MMgrRoot* GetMMgr();
    ~Standard_MMgrFactory();

  private:
    Standard_MMgrFactory();
    Standard_MMgrFactory(const Standard_MMgrFactory&);
    Standard_MMgrFactory& operator=(const Standard_MMgrFactory&);

  private:
    Standard_MMgrRoot* myFMMgr;
  };

  Standard_MMgrFactory::Standard_MMgrFactory()
      : myFMMgr(NULL)
  {

    Standard_STATIC_ASSERT(sizeof(char) == 1);
    Standard_STATIC_ASSERT(sizeof(short) == 2);
    Standard_STATIC_ASSERT(sizeof(char16_t) == 2);
    Standard_STATIC_ASSERT(sizeof(char32_t) == 4);
  #ifdef _WIN32
    Standard_STATIC_ASSERT(sizeof(wchar_t) == sizeof(char16_t));
  #endif

    char* aVar;
    aVar          = getenv("MMGT_OPT");
    int anAllocId = (aVar ? atoi(aVar) : OCCT_MMGT_OPT_DEFAULT);

  #if defined(HAVE_TBB) && defined(_M_IX86)
    if (anAllocId == 2)
    {

      static const DWORD _SSE2_FEATURE_BIT(0x04000000);
      DWORD volatile dwFeature;
      _asm
      {
        push eax
        push ebx
        push ecx
        push edx

         
        mov eax, 1
        cpuid
        mov dwFeature, edx

        pop edx
        pop ecx
        pop ebx
        pop eax
      }
      if ((dwFeature & _SSE2_FEATURE_BIT) == 0) anAllocId = 0;
    }
  #endif

    aVar         = getenv("MMGT_CLEAR");
    bool toClear = (aVar ? (atoi(aVar) != 0) : true);

  #if defined(_MSC_VER)
    aVar = getenv("MMGT_LFH");
    if (aVar == NULL || atoi(aVar) != 0)
    {
      ULONG  aHeapInfo = 2;
      HANDLE aCRTHeap  = (HANDLE)_get_heap_handle();
      HeapSetInformation(aCRTHeap, HeapCompatibilityInformation, &aHeapInfo, sizeof(aHeapInfo));
    }
  #endif

    switch (anAllocId)
    {
      case 1:
      {
        aVar           = getenv("MMGT_MMAP");
        bool bMMap     = (aVar ? (atoi(aVar) != 0) : true);
        aVar           = getenv("MMGT_CELLSIZE");
        int aCellSize  = (aVar ? atoi(aVar) : 200);
        aVar           = getenv("MMGT_NBPAGES");
        int aNbPages   = (aVar ? atoi(aVar) : 1000);
        aVar           = getenv("MMGT_THRESHOLD");
        int aThreshold = (aVar ? atoi(aVar) : 40000);
        myFMMgr        = new Standard_MMgrOpt(toClear, bMMap, aCellSize, aNbPages, aThreshold);
        break;
      }
      case 2:
        myFMMgr = new Standard_MMgrTBBalloc(toClear);
        break;
      case 0:
      default:
        myFMMgr = new Standard_MMgrRaw(toClear);
    }
    allocatorTypeInstance() = static_cast<Standard::AllocatorType>(anAllocId);
  }

  Standard_MMgrFactory::~Standard_MMgrFactory()
  {
    if (myFMMgr)
      myFMMgr->Purge(true);
  }

  Standard_MMgrRoot* Standard_MMgrFactory::GetMMgr()
  {
    static Standard_MMgrFactory aFactory;
    return aFactory.myFMMgr;
  }
} // namespace
#endif

Standard::AllocatorType Standard::GetAllocatorType()
{
  return allocatorTypeInstance();
}

void* Standard::Allocate(const size_t theSize)
{
#ifdef OCCT_MMGT_OPT_FLEXIBLE
  return Standard_MMgrFactory::GetMMgr()->Allocate(theSize);
#elif defined OCCT_MMGT_OPT_JEMALLOC
  void* aPtr = je_calloc(theSize, sizeof(char));
  if (!aPtr)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Allocate(): malloc failed");
  return aPtr;
#elif defined OCCT_MMGT_OPT_TBB
  void* aPtr = scalable_calloc(theSize, sizeof(char));
  if (!aPtr)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Allocate(): malloc failed");
  return aPtr;
#else
  void* aPtr = calloc(theSize, sizeof(char));
  if (!aPtr)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Allocate(): malloc failed");
  return aPtr;
#endif
}

void* Standard::AllocateOptimal(const size_t theSize)
{
#ifdef OCCT_MMGT_OPT_FLEXIBLE
  return Standard_MMgrFactory::GetMMgr()->Allocate(theSize);
#elif defined OCCT_MMGT_OPT_JEMALLOC
  return je_malloc(theSize);
#elif defined OCCT_MMGT_OPT_TBB
  return scalable_malloc(theSize);
#else
  return malloc(theSize);
#endif
}

void Standard::Free(void* theStorage)
{
#ifdef OCCT_MMGT_OPT_FLEXIBLE
  Standard_MMgrFactory::GetMMgr()->Free(theStorage);
#elif defined OCCT_MMGT_OPT_JEMALLOC
  je_free(theStorage);
#elif defined OCCT_MMGT_OPT_TBB
  scalable_free(theStorage);
#else
  free(theStorage);
#endif
}

void* Standard::Reallocate(void* theStorage, const size_t theSize)
{

#ifdef OCCT_MMGT_OPT_FLEXIBLE
  return Standard_MMgrFactory::GetMMgr()->Reallocate(theStorage, theSize);
#elif defined OCCT_MMGT_OPT_JEMALLOC
  void* aNewStorage = (void*)je_realloc(theStorage, theSize);
  if (!aNewStorage)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Reallocate(): realloc failed");
  return aNewStorage;
#elif defined OCCT_MMGT_OPT_TBB
  void* aNewStorage = (void*)scalable_realloc(theStorage, theSize);
  if (!aNewStorage)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Reallocate(): realloc failed");
  return aNewStorage;
#else
  void* aNewStorage = (void*)realloc(theStorage, theSize);
  if (!aNewStorage)
    throw Standard_OutOfMemory("Standard_MMgrRaw::Reallocate(): realloc failed");
  return aNewStorage;
#endif
}

int Standard::Purge()
{
#ifdef OCCT_MMGT_OPT_FLEXIBLE
  return Standard_MMgrFactory::GetMMgr()->Purge();
#else
  return true;
#endif
}

void* Standard::AllocateAligned(const size_t theSize, const size_t theAlign)
{
#ifdef OCCT_MMGT_OPT_JEMALLOC
  return je_aligned_alloc(theAlign, theSize);
#elif defined OCCT_MMGT_OPT_TBB
  return scalable_aligned_malloc(theSize, theAlign);
#else
  #if defined(_MSC_VER)
  return _aligned_malloc(theSize, theAlign);
  #elif defined(__ANDROID__) || defined(__QNX__)
  return memalign(theAlign, theSize);
  #elif (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))             \
         && (defined(__i386) || defined(__x86_64)))
  return _mm_malloc(theSize, theAlign);
  #else
  void* aPtr;
  if (posix_memalign(&aPtr, theAlign, theSize))
  {
    return nullptr;
  }
  return aPtr;
  #endif
#endif
}

void Standard::FreeAligned(void* thePtrAligned)
{
#ifdef OCCT_MMGT_OPT_JEMALLOC
  return je_free(thePtrAligned);
#elif defined OCCT_MMGT_OPT_TBB
  return scalable_aligned_free(thePtrAligned);
#else
  #if defined(_MSC_VER)
  _aligned_free(thePtrAligned);
  #elif defined(__ANDROID__) || defined(__QNX__)
  free(thePtrAligned);
  #elif (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))             \
         && (defined(__i386) || defined(__x86_64)))
  _mm_free(thePtrAligned);
  #else
  free(thePtrAligned);
  #endif
#endif
}
