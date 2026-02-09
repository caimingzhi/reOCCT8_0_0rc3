#pragma once

#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)
  #define DEFINE_STANDARD_ALLOC_ARRAY
#else
  #define DEFINE_STANDARD_ALLOC_ARRAY                                                              \
    void* operator new[](size_t theSize)                                                           \
    {                                                                                              \
      return Standard::Allocate(theSize);                                                          \
    }                                                                                              \
    void operator delete[](void* theAddress)                                                       \
    {                                                                                              \
      Standard::Free(theAddress);                                                                  \
    }
#endif

#if defined(__BORLANDC__) || (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530))
  #define DEFINE_STANDARD_ALLOC_PLACEMENT                                                          \
    void* operator new(size_t, void* theAddress) noexcept                                          \
    {                                                                                              \
      return theAddress;                                                                           \
    }
#else
  #define DEFINE_STANDARD_ALLOC_PLACEMENT                                                          \
    void* operator new(size_t, void* theAddress) noexcept                                          \
    {                                                                                              \
      return theAddress;                                                                           \
    }                                                                                              \
    void operator delete(void*, void*) noexcept {}
#endif

#define DEFINE_STANDARD_ALLOC                                                                      \
  void* operator new(size_t theSize)                                                               \
  {                                                                                                \
    return Standard::Allocate(theSize);                                                            \
  }                                                                                                \
  void operator delete(void* theAddress)                                                           \
  {                                                                                                \
    Standard::Free(theAddress);                                                                    \
  }                                                                                                \
  DEFINE_STANDARD_ALLOC_ARRAY                                                                      \
  DEFINE_STANDARD_ALLOC_PLACEMENT

#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x420)
inline void* operator new(size_t, void* anAddress) noexcept
{
  return anAddress;
}
#endif

#if defined(_MSC_VER)
  #define STANDARD_ALIGNED(theAlignment, theType, theVar)                                          \
    __declspec(align(theAlignment)) theType theVar
#elif defined(__GNUC__)
  #define STANDARD_ALIGNED(theAlignment, theType, theVar)                                          \
    theType __attribute__((aligned(theAlignment))) theVar
#else
  #define STANDARD_ALIGNED(theAlignment, theType, theVar) theType theVar
#endif
