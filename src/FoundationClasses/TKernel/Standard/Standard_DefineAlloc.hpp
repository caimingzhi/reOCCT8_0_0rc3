#pragma once


// Macro to override new and delete operators for arrays.
// Defined to empty for old SUN compiler
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

// Macro to override placement new and placement delete operators.
// For Borland C and old SUN compilers do not define placement delete
// as it is not supported.
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

// Macro to override operators new and delete to use OCC memory manager
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

// Declare operator new in global scope for old sun compiler
  #if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x420)
inline void* operator new(size_t, void* anAddress) noexcept
{
  return anAddress;
}
  #endif

//! @def STANDARD_ALIGNED(theAlignment, theType, theVar)
//! Declare variable with memory alignment.
//! @code
//!   static const STANDARD_ALIGNED(8, char, THE_ARRAY)[] = {0xFF, 0xFE, 0xFA, 0xFB, 0xFF, 0x11,
//!   0x22, 0x33};
//! @endcode
#if defined(_MSC_VER)
  #define STANDARD_ALIGNED(theAlignment, theType, theVar)                                          \
    __declspec(align(theAlignment)) theType theVar
#elif defined(__GNUC__)
  #define STANDARD_ALIGNED(theAlignment, theType, theVar)                                          \
    theType __attribute__((aligned(theAlignment))) theVar
#else
  #define STANDARD_ALIGNED(theAlignment, theType, theVar) theType theVar
#endif

