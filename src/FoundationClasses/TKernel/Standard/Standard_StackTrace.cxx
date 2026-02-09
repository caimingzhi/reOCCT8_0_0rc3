#include <Standard.hpp>

#include <Message.hpp>

#include <mutex>

#include <Standard_WarningDisableFunctionCast.hpp>

#if defined(__APPLE__)
  #import <TargetConditionals.h>
#endif

#if defined(__EMSCRIPTEN__)
  #include <emscripten/emscripten.h>
#elif defined(__ANDROID__)

#elif defined(__QNX__)

#elif !defined(_WIN32) && !(defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
  #include <execinfo.h>
#elif defined(_WIN32) && !defined(OCCT_UWP)

  #include <Standard_WarningsDisable.hpp>
  #include <windows.h>
  #include <dbghelp.h>
  #include <Standard_WarningsRestore.hpp>

class Standard_DbgHelper
{
public:
  typedef BOOL(WINAPI* SYMINITIALIZEPROC)(HANDLE, PCSTR, BOOL);
  typedef BOOL(WINAPI* STACKWALK64PROC)(DWORD,
                                        HANDLE,
                                        HANDLE,
                                        LPSTACKFRAME64,
                                        PVOID,
                                        PREAD_PROCESS_MEMORY_ROUTINE64,
                                        PFUNCTION_TABLE_ACCESS_ROUTINE64,
                                        PGET_MODULE_BASE_ROUTINE64,
                                        PTRANSLATE_ADDRESS_ROUTINE64);
  typedef BOOL(WINAPI* SYMCLEANUPPROC)(HANDLE);
  typedef BOOL(WINAPI* SYMFROMADDRPROC)(HANDLE, DWORD64, PDWORD64, PSYMBOL_INFO);

public:
  static Standard_DbgHelper& GetDbgHelper()
  {
    static Standard_DbgHelper aDbgHelper;
    return aDbgHelper;
  }

  static std::mutex& Mutex()
  {
    static std::mutex THE_MUTEX_LOCK;
    return THE_MUTEX_LOCK;
  }

public:
  SYMINITIALIZEPROC                SymInitialize;
  SYMCLEANUPPROC                   SymCleanup;
  STACKWALK64PROC                  StackWalk64;
  PFUNCTION_TABLE_ACCESS_ROUTINE64 SymFunctionTableAccess64;
  PGET_MODULE_BASE_ROUTINE64       SymGetModuleBase64;
  SYMFROMADDRPROC                  SymFromAddr;

  bool IsLoaded() const { return myDbgHelpLib != NULL; }

  const char* ErrorMessage() const { return myError; }

private:
  Standard_DbgHelper()
      : SymInitialize(NULL),
        SymCleanup(NULL),
        StackWalk64(NULL),
        SymFunctionTableAccess64(NULL),
        SymGetModuleBase64(NULL),
        SymFromAddr(NULL),
        myDbgHelpLib(LoadLibraryW(L"DbgHelp.dll")),
        myError(NULL)
  {
    if (myDbgHelpLib == NULL)
    {
      myError = "Standard_DbgHelper, Failed to load DbgHelp.dll";
      return;
    }

    if ((SymInitialize = (SYMINITIALIZEPROC)GetProcAddress(myDbgHelpLib, "SymInitialize")) == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: SymInitialize";
      unload();
      return;
    }
    if ((SymCleanup = (SYMCLEANUPPROC)GetProcAddress(myDbgHelpLib, "SymCleanup")) == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: SymCleanup";
      unload();
      return;
    }
    if ((StackWalk64 = (STACKWALK64PROC)GetProcAddress(myDbgHelpLib, "StackWalk64")) == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: StackWalk64";
      unload();
      return;
    }
    if ((SymFunctionTableAccess64 =
           (PFUNCTION_TABLE_ACCESS_ROUTINE64)GetProcAddress(myDbgHelpLib,
                                                            "SymFunctionTableAccess64"))
        == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: SymFunctionTableAccess64";
      unload();
      return;
    }
    if ((SymGetModuleBase64 =
           (PGET_MODULE_BASE_ROUTINE64)GetProcAddress(myDbgHelpLib, "SymGetModuleBase64"))
        == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: SymGetModuleBase64";
      unload();
      return;
    }
    if ((SymFromAddr = (SYMFROMADDRPROC)GetProcAddress(myDbgHelpLib, "SymFromAddr")) == NULL)
    {
      myError = "Standard_DbgHelper, Function not found in DbgHelp.dll: SymFromAddr";
      unload();
      return;
    }
  }

  ~Standard_DbgHelper() {}

  void unload()
  {
    if (myDbgHelpLib != NULL)
    {
      FreeLibrary(myDbgHelpLib);
      myDbgHelpLib = NULL;
    }
  }

private:
  Standard_DbgHelper(const Standard_DbgHelper&);
  Standard_DbgHelper& operator=(const Standard_DbgHelper&);

private:
  HMODULE     myDbgHelpLib;
  const char* myError;
};

#endif

bool Standard::StackTrace(char*     theBuffer,
                          const int theBufferSize,
                          const int theNbTraces = 10,
                          void*     theContext,
                          const int theNbTopSkip)
{
  (void)theContext;
  if (theBufferSize < 1 || theNbTraces < 1 || theBuffer == nullptr || theNbTopSkip < 0)
  {
    return false;
  }

#if defined(__EMSCRIPTEN__)

  return emscripten_get_callstack(EM_LOG_C_STACK | EM_LOG_DEMANGLE | EM_LOG_NO_PATHS
                                    | EM_LOG_FUNC_PARAMS,
                                  theBuffer,
                                  theBufferSize)
         > 0;
#elif defined(__ANDROID__)
  Message::SendTrace("Standard::StackTrace() is not implemented for this platform");
  return false;
#elif defined(__QNX__)

  Message::SendTrace("Standard::StackTrace() is not implemented for this platform");
  return false;
#elif defined(OCCT_UWP) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
  Message::SendTrace("Standard::StackTrace() is not implemented for this platform");
  return false;
#elif defined(_WIN32)

  #if defined(_M_X64)
  int          aNbTraces  = theNbTraces;
  const HANDLE anHProcess = GetCurrentProcess();
  const HANDLE anHThread  = GetCurrentThread();
  CONTEXT      aCtx;
  if (theContext != NULL)
  {
    memcpy(&aCtx, theContext, sizeof(aCtx));
  }
  else
  {
    ++aNbTraces;
    memset(&aCtx, 0, sizeof(aCtx));
    aCtx.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&aCtx);
  }

  std::lock_guard<std::mutex> aLock(Standard_DbgHelper::Mutex());
  Standard_DbgHelper&         aDbgHelp = Standard_DbgHelper::GetDbgHelper();
  if (!aDbgHelp.IsLoaded())
  {
    strcat_s(theBuffer, theBufferSize, "\n==Backtrace==\n");
    strcat_s(theBuffer, theBufferSize, aDbgHelp.ErrorMessage());
    strcat_s(theBuffer, theBufferSize, "\n=============");
    return false;
  }

  aDbgHelp.SymInitialize(anHProcess, NULL, TRUE);

  DWORD        anImage = 0;
  STACKFRAME64 aStackFrame;
  memset(&aStackFrame, 0, sizeof(aStackFrame));

  anImage                      = IMAGE_FILE_MACHINE_AMD64;
  aStackFrame.AddrPC.Offset    = aCtx.Rip;
  aStackFrame.AddrPC.Mode      = AddrModeFlat;
  aStackFrame.AddrFrame.Offset = aCtx.Rsp;
  aStackFrame.AddrFrame.Mode   = AddrModeFlat;
  aStackFrame.AddrStack.Offset = aCtx.Rsp;
  aStackFrame.AddrStack.Mode   = AddrModeFlat;

  char         aModBuffer[MAX_PATH] = {};
  char         aSymBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(CHAR)];
  SYMBOL_INFO* aSymbol  = (SYMBOL_INFO*)aSymBuffer;
  aSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
  aSymbol->MaxNameLen   = MAX_SYM_NAME;

  int aTopSkip = theNbTopSkip + 1;
  strcat_s(theBuffer, theBufferSize, "\n==Backtrace==");
  for (int aLineIter = 0; aLineIter < aNbTraces; ++aLineIter)
  {
    BOOL aRes = aDbgHelp.StackWalk64(anImage,
                                     anHProcess,
                                     anHThread,
                                     &aStackFrame,
                                     &aCtx,
                                     NULL,
                                     aDbgHelp.SymFunctionTableAccess64,
                                     aDbgHelp.SymGetModuleBase64,
                                     NULL);
    if (!aRes)
    {
      break;
    }

    if (theContext == NULL && aTopSkip > 0)
    {
      --aTopSkip;
      continue;
    }
    if (aStackFrame.AddrPC.Offset == 0)
    {
      break;
    }

    strcat_s(theBuffer, theBufferSize, "\n");

    const DWORD64 aModuleBase = aDbgHelp.SymGetModuleBase64(anHProcess, aStackFrame.AddrPC.Offset);
    if (aModuleBase != 0 && GetModuleFileNameA((HINSTANCE)aModuleBase, aModBuffer, MAX_PATH))
    {
      strcat_s(theBuffer, theBufferSize, aModBuffer);
    }

    DWORD64 aDisp = 0;
    strcat_s(theBuffer, theBufferSize, "(");
    if (aDbgHelp.SymFromAddr(anHProcess, aStackFrame.AddrPC.Offset, &aDisp, aSymbol))
    {
      strcat_s(theBuffer, theBufferSize, aSymbol->Name);
    }
    else
    {
      strcat_s(theBuffer, theBufferSize, "???");
    }
    strcat_s(theBuffer, theBufferSize, ")");
  }
  strcat_s(theBuffer, theBufferSize, "\n=============");

  aDbgHelp.SymCleanup(anHProcess);
  return true;
  #else
  Message::SendTrace("Standard::StackTrace() is not implemented for this CPU architecture");
  return false;
  #endif
#else
  const int aTopSkip  = theNbTopSkip + 1;
  int       aNbTraces = theNbTraces + aTopSkip;
  void**    aStackArr = (void**)alloca(sizeof(void*) * aNbTraces);
  if (aStackArr == nullptr)
  {
    return false;
  }

  aNbTraces = ::backtrace(aStackArr, aNbTraces);
  if (aNbTraces <= 1)
  {
    return false;
  }

  aNbTraces -= aTopSkip;
  char** aStrings = ::backtrace_symbols(aStackArr + aTopSkip, aNbTraces);
  if (aStrings == nullptr)
  {
    return false;
  }

  const size_t aLenInit = strlen(theBuffer);
  size_t       aLimit   = (size_t)theBufferSize - aLenInit - 1;
  if (aLimit > 14)
  {
    strcat(theBuffer, "\n==Backtrace==");
    aLimit -= 14;
  }
  for (int aLineIter = 0; aLineIter < aNbTraces; ++aLineIter)
  {
    const size_t aLen = strlen(aStrings[aLineIter]);
    if (aLen + 1 >= aLimit)
    {
      break;
    }

    strcat(theBuffer, "\n");
    strcat(theBuffer, aStrings[aLineIter]);
    aLimit -= aLen + 1;
  }
  free(aStrings);
  if (aLimit > 14)
  {
    strcat(theBuffer, "\n=============");
  }
  return true;
#endif
}
