#pragma once

#if defined(_MSC_VER) && (_MSC_VER < 1600)
  #error C++11 compatible compiler is required (Visual Studio 2010 or newer)
#endif

#ifdef OCCT_NO_DEPRECATED
  #define Standard_DEPRECATED_WARNING(theMsg)
#elif defined(__GNUC__) || defined(__clang__)

  #define Standard_DEPRECATED_WARNING_PRAGMA(x) _Pragma(#x)
  #define Standard_DEPRECATED_WARNING(theMsg) Standard_DEPRECATED_WARNING_PRAGMA(GCC warning theMsg)
#elif defined(_MSC_VER)
  #define Standard_DEPRECATED_WARNING(theMsg)                                                      \
    __pragma(message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): warning: " theMsg))
#else
  #define Standard_DEPRECATED_WARNING(theMsg)
#endif

#define Standard_MACRO_DEPRECATED(theMsg) Standard_DEPRECATED_WARNING(theMsg)

#define Standard_HEADER_DEPRECATED(theMsg) Standard_DEPRECATED_WARNING(theMsg)

#define Standard_OVERRIDE                                                                          \
  Standard_MACRO_DEPRECATED("Standard_OVERRIDE is deprecated, use override directly") override

#define Standard_DELETE                                                                            \
  Standard_MACRO_DEPRECATED("Standard_DELETE is deprecated, use = delete directly") = delete

#define Standard_FALLTHROUGH                                                                       \
  Standard_MACRO_DEPRECATED("Standard_FALLTHROUGH is deprecated, use [[fallthrough]]; directly")   \
    [[fallthrough]];

#define Standard_NODISCARD                                                                         \
  Standard_MACRO_DEPRECATED("Standard_NODISCARD is deprecated, use [[nodiscard]] directly")        \
    [[nodiscard]]

#if defined(__GNUC__) || defined(__clang__)
  #define Standard_UNUSED __attribute__((unused))
#else
  #define Standard_UNUSED
#endif

#if defined(__clang__)                                                                             \
  || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)))
  #define Standard_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
  #define Standard_NOINLINE __declspec(noinline)
#else
  #define Standard_NOINLINE
#endif

#define Standard_THREADLOCAL                                                                       \
  Standard_MACRO_DEPRECATED(                                                                       \
    "Standard_THREADLOCAL is deprecated, use thread_local directly") thread_local

#ifdef OCCT_NO_DEPRECATED
  #define Standard_DEPRECATED(theMsg)
#else
  #if defined(_MSC_VER)
    #define Standard_DEPRECATED(theMsg) __declspec(deprecated(theMsg))
  #elif defined(__GNUC__)                                                                          \
    && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5) || defined(__clang__))
    #define Standard_DEPRECATED(theMsg) __attribute__((deprecated(theMsg)))
  #elif defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
    #define Standard_DEPRECATED(theMsg) __attribute__((deprecated))
  #else
    #define Standard_DEPRECATED(theMsg)
  #endif
#endif

#if defined(__ICL) || defined(__INTEL_COMPILER)
  #define Standard_DISABLE_DEPRECATION_WARNINGS                                                    \
    __pragma(warning(push)) __pragma(warning(disable : 1478))
  #define Standard_ENABLE_DEPRECATION_WARNINGS __pragma(warning(pop))
#elif (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))              \
  || defined(__clang__)

  #define Standard_DISABLE_DEPRECATION_WARNINGS                                                    \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
  #define Standard_ENABLE_DEPRECATION_WARNINGS                                                     \
    _Pragma("GCC diagnostic warning \"-Wdeprecated-declarations\"")
#elif defined(_MSC_VER)
  #define Standard_DISABLE_DEPRECATION_WARNINGS                                                    \
    __pragma(warning(push)) __pragma(warning(disable : 4996))
  #define Standard_ENABLE_DEPRECATION_WARNINGS __pragma(warning(pop))
#else
  #define Standard_DISABLE_DEPRECATION_WARNINGS
  #define Standard_ENABLE_DEPRECATION_WARNINGS
#endif

#ifdef _WIN32

  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX NOMINMAX
  #endif
  #ifndef NOMSG
    #define NOMSG NOMSG
  #endif
  #ifndef NODRAWTEXT
    #define NODRAWTEXT NODRAWTEXT
  #endif
  #ifndef NONLS
    #define NONLS NONLS
  #endif
  #ifndef NOGDI
    #define NOGDI NOGDI
  #endif
  #ifndef NOSERVICE
    #define NOSERVICE NOSERVICE
  #endif
  #ifndef NOKERNEL
    #define NOKERNEL NOKERNEL
  #endif
  #ifndef NOUSER
    #define NOUSER NOUSER
  #endif
  #ifndef NOMCX
    #define NOMCX NOMCX
  #endif
  #ifndef NOIME
    #define NOIME NOIME
  #endif

#endif

#if defined(_WIN32) && !defined(OCCT_STATIC_BUILD) && !defined(HAVE_NO_DLL)

  #ifndef Standard_EXPORT
    #define Standard_EXPORT __declspec(dllexport)

    #define Standard_EXPORTEXTERN __declspec(dllexport) extern
    #define Standard_EXPORTEXTERNC extern "C" __declspec(dllexport)
  #endif

  #ifndef Standard_IMPORT
    #define Standard_IMPORT __declspec(dllimport) extern
    #define Standard_IMPORTC extern "C" __declspec(dllimport)
  #endif

#else

  #ifndef Standard_EXPORT
    #define Standard_EXPORT

    #define Standard_EXPORTEXTERN extern
    #define Standard_EXPORTEXTERNC extern "C"
  #endif

  #ifndef Standard_IMPORT
    #define Standard_IMPORT extern
    #define Standard_IMPORTC extern "C"
  #endif

  #if __SUNPRO_CC_COMPAT == 5
    #define _MEMORY_H
  #endif

#endif

#if defined(__has_attribute)
  #if __has_attribute(visibility)
    #define Standard_HIDDEN __attribute__((visibility("hidden")))
  #else
    #define Standard_HIDDEN
  #endif
#elif defined(__GNUC__) || defined(__clang__)
  #define Standard_HIDDEN __attribute__((visibility("hidden")))
#else
  #define Standard_HIDDEN
#endif

#if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_APP
  #define OCCT_UWP
#else
  #ifdef OCCT_UWP
    #undef OCCT_UWP
  #endif
#endif

#define Standard_HASATOMIC                                                                         \
  Standard_MACRO_DEPRECATED(                                                                       \
    "Standard_HASATOMIC is deprecated, std::atomic is always available in C++17") 1

#define Standard_ATOMIC(theType)                                                                   \
  Standard_MACRO_DEPRECATED("Standard_ATOMIC is deprecated, use std::atomic<T> directly")          \
    std::atomic<theType>

#define Standard_Noexcept                                                                          \
  Standard_MACRO_DEPRECATED("Standard_Noexcept is deprecated, use noexcept directly") noexcept

#if defined(_MSC_VER) && defined(_MSVC_LANG) && _MSVC_LANG >= 201703L

  #define Standard_CPP17_OR_HIGHER 1
#elif defined(__cplusplus) && __cplusplus >= 201703L

  #define Standard_CPP17_OR_HIGHER 1
#else
  #define Standard_CPP17_OR_HIGHER 0
#endif
