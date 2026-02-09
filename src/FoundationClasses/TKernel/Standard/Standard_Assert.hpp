#pragma once

#include <Standard_ProgramError.hpp>

inline void Standard_ASSERT_DO_NOTHING() {}

#ifdef _DEBUG
  #if (defined(_WIN32) || defined(__WIN32__))
    #if defined(_MSC_VER) || defined(__MINGW64__)

      #define Standard_ASSERT_DBGBREAK_() __debugbreak()
    #else

      #include <windows.h>
      #define Standard_ASSERT_DBGBREAK_() DebugBreak()
    #endif
  #elif defined(__EMSCRIPTEN__)
    #include <emscripten.h>
    #define Standard_ASSERT_DBGBREAK_() emscripten_debugger()
  #else

    #include <signal.h>
    #define Standard_ASSERT_DBGBREAK_() raise(SIGTRAP)
  #endif

  #if defined(_MSC_VER)
    #include <crtdbg.h>

inline bool Standard_ASSERT_REPORT_(const char* theFile,
                                    const int   theLine,
                                    const char* theExpr,
                                    const char* theDesc)
{

  return _CrtDbgReport(_CRT_ASSERT,
                       theFile,
                       theLine,
                       NULL,
                       "%s\n(Condition: \"%s\")\n",
                       theDesc,
                       theExpr)
         == 1;
}
  #else

inline bool Standard_ASSERT_REPORT_(const char* theFile,
                                    const int   theLine,
                                    const char* theExpr,
                                    const char* theDesc)
{
  std::cerr << "ERROR: statement '" << theExpr << "' is not TRUE!\n"
            << "\nFile: '" << theFile << "'"
            << "\nLine: " << theLine << "\n";
  if (theDesc != NULL && *theDesc != '\0')
    std::cerr << "Description: " << theDesc << "\n";

  std::cerr << std::flush;
  return true;
}
  #endif

  #define Standard_ASSERT_INVOKE_(theExpr, theDesc)                                                \
    if (Standard_ASSERT_REPORT_(__FILE__, __LINE__, #theExpr, theDesc))                            \
    {                                                                                              \
      Standard_ASSERT_DBGBREAK_();                                                                 \
    }                                                                                              \
    else                                                                                           \
      Standard_ASSERT_DO_NOTHING()

  #define Standard_ASSERT(theExpr, theDesc, theAction)                                             \
    if (!(theExpr))                                                                                \
    {                                                                                              \
      Standard_ASSERT_INVOKE_(theExpr, theDesc);                                                   \
      theAction;                                                                                   \
    }                                                                                              \
    else                                                                                           \
      Standard_ASSERT_DO_NOTHING()
  #define Standard_ASSERT_SKIP(theExpr, theDesc)                                                   \
    Standard_ASSERT(theExpr, theDesc, Standard_VOID_RETURN)
  #define Standard_ASSERT_VOID(theExpr, theDesc)                                                   \
    Standard_ASSERT(theExpr, theDesc, Standard_VOID_RETURN)
#else

  #define Standard_ASSERT_INVOKE_(theExpr, theDesc) Standard_ASSERT_DO_NOTHING()

  #define Standard_ASSERT(theExpr, theDesc, theAction)                                             \
    if (!(theExpr))                                                                                \
    {                                                                                              \
      theAction;                                                                                   \
    }                                                                                              \
    else                                                                                           \
      Standard_ASSERT_DO_NOTHING()
  #define Standard_ASSERT_SKIP(theExpr, theDesc) theExpr
  #define Standard_ASSERT_VOID(theExpr, theDesc) Standard_ASSERT_DO_NOTHING()

#endif

#define Standard_ASSERT_RAISE(theExpr, theDesc)                                                    \
  Standard_ASSERT(theExpr,                                                                         \
                  theDesc,                                                                         \
                  throw Standard_ProgramError("*** ERROR: ASSERT in file '" __FILE__               \
                                              "': \n" theDesc " (" #theExpr ")"))

#define Standard_VOID_RETURN

#define Standard_ASSERT_RETURN(theExpr, theDesc, theReturnValue)                                   \
  Standard_ASSERT(theExpr, theDesc, return theReturnValue)

#define Standard_ASSERT_INVOKE(theDesc) Standard_ASSERT_INVOKE_(always, theDesc)

template <bool condition>
struct Standard_Static_Assert
{
};

template <>
struct Standard_Static_Assert<true>
{
  static void assert_ok() {}
};

#define Standard_STATIC_ASSERT(theExpr) Standard_Static_Assert<theExpr>::assert_ok();

#ifdef _MSC_VER
  #pragma once
#endif
