

#include <OSD.hpp>
#include <Standard_CString.hpp>
#include <OSD_Exception_CTRL_BREAK.hpp>
#include <Standard_DivideByZero.hpp>
#include <Standard_Overflow.hpp>
#include <Standard_Assert.hpp>

#include <mutex>
#include <csignal>

#include <Standard_WarningDisableFunctionCast.hpp>

static OSD_SignalMode OSD_WasSetSignal           = OSD_SignalMode_AsIs;
static int            OSD_SignalStackTraceLength = 0;

OSD_SignalMode OSD::SignalMode()
{
  return OSD_WasSetSignal;
}

int OSD::SignalStackTraceLength()
{
  return OSD_SignalStackTraceLength;
}

void OSD::SetSignalStackTraceLength(int theLength)
{
  OSD_SignalStackTraceLength = theLength;
}

#ifdef _WIN32

  #ifdef NOUSER
    #undef NOUSER
  #endif
  #ifdef NONLS
    #undef NONLS
  #endif
  #include <windows.h>

  #include <strsafe.h>

  #ifndef STATUS_FLOAT_MULTIPLE_FAULTS

    #define STATUS_FLOAT_MULTIPLE_FAULTS (0xC00002B4L)
    #define STATUS_FLOAT_MULTIPLE_TRAPS (0xC00002B5L)
  #endif

  #include <OSD_Exception_ACCESS_VIOLATION.hpp>
  #include <OSD_Exception_ARRAY_BOUNDS_EXCEEDED.hpp>
  #include <OSD_Exception_ILLEGAL_INSTRUCTION.hpp>
  #include <OSD_Exception_IN_PAGE_ERROR.hpp>
  #include <OSD_Exception_INT_OVERFLOW.hpp>
  #include <OSD_Exception_INVALID_DISPOSITION.hpp>
  #include <OSD_Exception_NONCONTINUABLE_EXCEPTION.hpp>
  #include <OSD_Exception_PRIV_INSTRUCTION.hpp>
  #include <OSD_Exception_STACK_OVERFLOW.hpp>
  #include <OSD_Exception_STATUS_NO_MEMORY.hpp>

  #include <OSD_Environment.hpp>
  #include <Standard_Underflow.hpp>
  #include <Standard_ProgramError.hpp>

  #ifdef _MSC_VER
    #include <eh.h>
    #include <malloc.h>
  #endif

  #include <process.h>
  #include <float.h>

static bool fCtrlBrk;

static bool fMsgBox;

static std::mutex THE_SIGNAL_MUTEX;

static LONG __fastcall _osd_raise(DWORD theCode, const char* theMsg, const char* theStack);
static BOOL WINAPI _osd_ctrl_break_handler(DWORD);

  #if !defined(OCCT_UWP) && !defined(__MINGW32__) && !defined(__CYGWIN32__)
static bool fDbgLoaded;
static LONG _osd_debug(void);
  #endif

  #define _OSD_FPX (_EM_INVALID | _EM_DENORMAL | _EM_ZERODIVIDE | _EM_OVERFLOW)

  #ifdef OCC_CONVERT_SIGNALS
    #define THROW_OR_JUMP(Type, Message, Stack) Standard_ErrorHandler::Abort(Type(Message, Stack))
  #else
    #define THROW_OR_JUMP(Type, Message, Stack) throw Type(Message, Stack)
  #endif

static LONG CallHandler(DWORD theExceptionCode, EXCEPTION_POINTERS* theExcPtr)
{
  ptrdiff_t ExceptionInformation1 = 0, ExceptionInformation0 = 0;
  if (theExcPtr != NULL)
  {
    ExceptionInformation1 = theExcPtr->ExceptionRecord->ExceptionInformation[1];
    ExceptionInformation0 = theExcPtr->ExceptionRecord->ExceptionInformation[0];
  }

  std::lock_guard<std::mutex> aLock(THE_SIGNAL_MUTEX);

  static char aBuffer[2048];

  bool isFloatErr = false;
  aBuffer[0]      = '\0';
  switch (theExceptionCode)
  {
    case EXCEPTION_FLT_DENORMAL_OPERAND:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT DENORMAL OPERAND");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT DIVIDE BY ZERO");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_INEXACT_RESULT:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT INEXACT RESULT");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_INVALID_OPERATION:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT INVALID OPERATION");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_OVERFLOW:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT OVERFLOW");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_STACK_CHECK:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT STACK CHECK");
      isFloatErr = true;
      break;
    }
    case EXCEPTION_FLT_UNDERFLOW:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT UNDERFLOW");
      isFloatErr = true;
      break;
    }
    case STATUS_FLOAT_MULTIPLE_TRAPS:
    {
      strcat_s(aBuffer,
               sizeof(aBuffer),
               "FLT MULTIPLE TRAPS (possible overflow in conversion of double to integer)");
      isFloatErr = true;
      break;
    }
    case STATUS_FLOAT_MULTIPLE_FAULTS:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "FLT MULTIPLE FAULTS");
      isFloatErr = true;
      break;
    }
    case STATUS_NO_MEMORY:
    {
      THROW_OR_JUMP(OSD_Exception_STATUS_NO_MEMORY,
                    "MEMORY ALLOCATION ERROR ( no room in the process heap )",
                    NULL);
      break;
    }
    case EXCEPTION_ACCESS_VIOLATION:
    {
      _snprintf_s(aBuffer,
                  sizeof(aBuffer),
                  _TRUNCATE,
                  "%s%s%s0x%.8p%s%s%s",
                  "ACCESS VIOLATION",
                  fMsgBox ? "\n" : " ",
                  "at address ",
                  (void*)ExceptionInformation1,
                  " during '",
                  ExceptionInformation0 ? "WRITE" : "READ",
                  "' operation");
      break;
    }
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "ARRAY BOUNDS EXCEEDED");
      break;
    }
    case EXCEPTION_DATATYPE_MISALIGNMENT:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "DATATYPE MISALIGNMENT");
      break;
    }
    case EXCEPTION_ILLEGAL_INSTRUCTION:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "ILLEGAL INSTRUCTION");
      break;
    }
    case EXCEPTION_IN_PAGE_ERROR:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "IN_PAGE ERROR");
      break;
    }
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "INTEGER DIVISION BY ZERO");
      break;
    }
    case EXCEPTION_INT_OVERFLOW:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "INTEGER OVERFLOW");
      break;
    }
    case EXCEPTION_INVALID_DISPOSITION:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "INVALID DISPOSITION");
      break;
    }
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "NONCONTINUABLE EXCEPTION");
      break;
    }
    case EXCEPTION_PRIV_INSTRUCTION:
    {
      strcat_s(aBuffer, sizeof(aBuffer), "PRIVILEGED INSTRUCTION ENCOUNTERED");
      break;
    }
    case EXCEPTION_STACK_OVERFLOW:
    {
  #if defined(_MSC_VER) && (_MSC_VER >= 1300) && !defined(OCCT_UWP)

      if (!_resetstkoflw())
      {
        strcat_s(aBuffer, sizeof(aBuffer), "Unrecoverable STACK OVERFLOW");
      }
      else
  #endif
      {
        strcat_s(aBuffer, sizeof(aBuffer), "STACK OVERFLOW");
      }
      break;
    }
    default:
    {
      _snprintf_s(aBuffer,
                  sizeof(aBuffer),
                  _TRUNCATE,
                  "unknown exception code 0x%x, params 0x%p 0x%p",
                  theExceptionCode,
                  (void*)ExceptionInformation1,
                  (void*)ExceptionInformation0);
    }
  }

  if (isFloatErr)
  {
    OSD::SetFloatingSignal(true);
  }

  const int aStackLength = OSD_SignalStackTraceLength;
  const int aStackBufLen = std::max(aStackLength * 200, 2048);
  char*     aStackBuffer = aStackLength != 0 ? (char*)alloca(aStackBufLen) : NULL;
  if (aStackBuffer != NULL)
  {
    memset(aStackBuffer, 0, aStackBufLen);
    Standard::StackTrace(aStackBuffer, aStackBufLen, aStackLength, theExcPtr->ContextRecord);
  }

  #if !defined(OCCT_UWP) && !defined(__MINGW32__) && !defined(__CYGWIN32__)

  if (aBuffer[0] != '\0' && fMsgBox && theExceptionCode != EXCEPTION_NONCONTINUABLE_EXCEPTION)
  {
    MessageBeep(MB_ICONHAND);
    char aMsgBoxBuffer[2048];
    strcat_s(aMsgBoxBuffer, sizeof(aMsgBoxBuffer), aBuffer);
    if (aStackBuffer != NULL)
    {
      strcat_s(aMsgBoxBuffer, sizeof(aMsgBoxBuffer), aStackBuffer);
    }
    int aChoice =
      ::MessageBoxA(0, aMsgBoxBuffer, "OCCT Exception Handler", MB_ABORTRETRYIGNORE | MB_ICONSTOP);
    if (aChoice == IDRETRY)
    {
      _osd_debug();
      DebugBreak();
    }
    else if (aChoice == IDABORT)
    {
      exit(0xFFFF);
    }
  }
  #endif

  return _osd_raise(theExceptionCode, aBuffer, aStackBuffer);
}

static void SIGWntHandler(int signum, int sub_code)
{

  std::lock_guard<std::mutex> aLock(THE_SIGNAL_MUTEX);

  switch (signum)
  {
    case SIGFPE:
      if (signal(signum, (void (*)(int))SIGWntHandler) == SIG_ERR)
        std::cout << "signal error" << std::endl;
      switch (sub_code)
      {
        case _FPE_INVALID:
          CallHandler(EXCEPTION_FLT_INVALID_OPERATION, NULL);
          break;
        case _FPE_DENORMAL:
          CallHandler(EXCEPTION_FLT_DENORMAL_OPERAND, NULL);
          break;
        case _FPE_ZERODIVIDE:
          CallHandler(EXCEPTION_FLT_DIVIDE_BY_ZERO, NULL);
          break;
        case _FPE_OVERFLOW:
          CallHandler(EXCEPTION_FLT_OVERFLOW, NULL);
          break;
        case _FPE_UNDERFLOW:
          CallHandler(EXCEPTION_FLT_UNDERFLOW, NULL);
          break;
        case _FPE_INEXACT:
          CallHandler(EXCEPTION_FLT_INEXACT_RESULT, NULL);
          break;
        default:
          std::cout
            << "SIGWntHandler(default) -> throw Standard_NumericError(\"Floating Point Error\");"
            << std::endl;
          THROW_OR_JUMP(Standard_NumericError, "Floating Point Error", NULL);
          break;
      }
      break;
    case SIGSEGV:
      if (signal(signum, (void (*)(int))SIGWntHandler) == SIG_ERR)
        std::cout << "signal error" << std::endl;
      CallHandler(EXCEPTION_ACCESS_VIOLATION, NULL);
      break;
    case SIGILL:
      if (signal(signum, (void (*)(int))SIGWntHandler) == SIG_ERR)
        std::cout << "signal error" << std::endl;
      CallHandler(EXCEPTION_ILLEGAL_INSTRUCTION, NULL);
      break;
    default:
      std::cout << "SIGWntHandler unexpected signal : " << signum << std::endl;
      break;
  }
  #ifndef OCCT_UWP
  DebugBreak();
  #endif
}

  #ifdef _MSC_VER

    #pragma warning(disable : 4535)

static void TranslateSE(unsigned int theCode, EXCEPTION_POINTERS* theExcPtr)
{
  CallHandler(theCode, theExcPtr);
}
  #endif

static LONG WINAPI WntHandler(EXCEPTION_POINTERS* lpXP)
{
  DWORD dwExceptionCode = lpXP->ExceptionRecord->ExceptionCode;
  return CallHandler(dwExceptionCode, lpXP);
}

void OSD::SetFloatingSignal(bool theFloatingSignal)
{
  _fpreset();
  _clearfp();

  _controlfp(theFloatingSignal ? 0 : _OSD_FPX, _OSD_FPX);
}

bool OSD::ToCatchFloatingSignals()
{

  int aControlWord = _controlfp(0, 0);
  return (_OSD_FPX & ~aControlWord) != 0;
}

void OSD::SetThreadLocalSignal(OSD_SignalMode theSignalMode, bool theFloatingSignal)
{
  #ifdef _MSC_VER
  _se_translator_function aPreviousFunc = NULL;
  if (theSignalMode == OSD_SignalMode_Set || theSignalMode == OSD_SignalMode_SetUnhandled)
    aPreviousFunc = _set_se_translator(TranslateSE);
  if (theSignalMode == OSD_SignalMode_Unset
      || (theSignalMode == OSD_SignalMode_SetUnhandled && aPreviousFunc != NULL))
    _set_se_translator(aPreviousFunc);
  #else
  (void)theSignalMode;
  #endif
  SetFloatingSignal(theFloatingSignal);
}

void OSD::SetSignal(OSD_SignalMode theSignalMode, bool theFloatingSignal)
{

  std::lock_guard<std::mutex> aLock(THE_SIGNAL_MUTEX);

  OSD_WasSetSignal = theSignalMode;

  #if !defined(OCCT_UWP) || defined(NTDDI_WIN10_TH2)
  OSD_Environment         env("CSF_DEBUG_MODE");
  TCollection_AsciiString val = env.Value();
  if (!env.Failed())
  {
    std::cout << "Environment variable CSF_DEBUG_MODE set.\n";
    fMsgBox = true;
    if (OSD_SignalStackTraceLength == 0)
    {

      OSD_SignalStackTraceLength = 10;
    }
  }
  else
  {
    fMsgBox = false;
  }

  {
    LPTOP_LEVEL_EXCEPTION_FILTER aPreviousFunc = NULL;
    if (theSignalMode == OSD_SignalMode_Set || theSignalMode == OSD_SignalMode_SetUnhandled)
    {
      aPreviousFunc = ::SetUnhandledExceptionFilter(WntHandler);
    }
    if (theSignalMode == OSD_SignalMode_Unset
        || (theSignalMode == OSD_SignalMode_SetUnhandled && aPreviousFunc != NULL))
    {
      ::SetUnhandledExceptionFilter(aPreviousFunc);
    }
  }
  #endif

  const int NBSIG               = 3;
  const int aSignalTypes[NBSIG] = {SIGSEGV, SIGILL, SIGFPE};
  for (int i = 0; i < NBSIG; ++i)
  {
    typedef void (*SignalFuncType)(int);
    SignalFuncType aPreviousFunc = SIG_DFL;
    if (theSignalMode == OSD_SignalMode_Set || theSignalMode == OSD_SignalMode_SetUnhandled)
    {
      aPreviousFunc = signal(aSignalTypes[i], (SignalFuncType)SIGWntHandler);
    }
    if (theSignalMode == OSD_SignalMode_Unset
        || (theSignalMode == OSD_SignalMode_SetUnhandled && aPreviousFunc != SIG_DFL
            && aPreviousFunc != SIG_ERR))
    {
      aPreviousFunc = signal(aSignalTypes[i], aPreviousFunc);
    }
    Standard_ASSERT(aPreviousFunc != SIG_ERR,
                    "signal() failed",
                    std::cout << "OSD::SetSignal(): signal() returns SIG_ERR");
  }

  fCtrlBrk = false;
  #ifndef OCCT_UWP
  if (theSignalMode == OSD_SignalMode_Set || theSignalMode == OSD_SignalMode_SetUnhandled)
  {
    SetConsoleCtrlHandler(&_osd_ctrl_break_handler, true);
  }
  else if (theSignalMode == OSD_SignalMode_Unset)
  {
    SetConsoleCtrlHandler(&_osd_ctrl_break_handler, false);
  }
  #endif

  SetThreadLocalSignal(theSignalMode, theFloatingSignal);
}

void OSD::ControlBreak()
{
  if (fCtrlBrk)
  {
    fCtrlBrk = false;
    throw OSD_Exception_CTRL_BREAK("*** INTERRUPT ***");
  }
}

  #ifndef OCCT_UWP

static BOOL WINAPI _osd_ctrl_break_handler(DWORD dwCode)
{
  if (dwCode == CTRL_C_EVENT || dwCode == CTRL_BREAK_EVENT)
  {
    MessageBeep(MB_ICONEXCLAMATION);
    fCtrlBrk = true;
  }
  else
    exit(254);

  return TRUE;
}
  #endif

static LONG __fastcall _osd_raise(DWORD theCode, const char* theMsg, const char* theStack)
{
  const char* aMsg = theMsg;
  if (aMsg[0] == '\x03')
  {
    ++aMsg;
  }

  switch (theCode)
  {
    case EXCEPTION_ACCESS_VIOLATION:
      THROW_OR_JUMP(OSD_Exception_ACCESS_VIOLATION, aMsg, theStack);
      break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
      THROW_OR_JUMP(OSD_Exception_ARRAY_BOUNDS_EXCEEDED, aMsg, theStack);
      break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
      THROW_OR_JUMP(Standard_ProgramError, aMsg, theStack);
      break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
      THROW_OR_JUMP(OSD_Exception_ILLEGAL_INSTRUCTION, aMsg, theStack);
      break;
    case EXCEPTION_IN_PAGE_ERROR:
      THROW_OR_JUMP(OSD_Exception_IN_PAGE_ERROR, aMsg, theStack);
      break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
      THROW_OR_JUMP(Standard_DivideByZero, aMsg, theStack);
      break;
    case EXCEPTION_INT_OVERFLOW:
      THROW_OR_JUMP(OSD_Exception_INT_OVERFLOW, aMsg, theStack);
      break;
    case EXCEPTION_INVALID_DISPOSITION:
      THROW_OR_JUMP(OSD_Exception_INVALID_DISPOSITION, aMsg, theStack);
      break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
      THROW_OR_JUMP(OSD_Exception_NONCONTINUABLE_EXCEPTION, aMsg, theStack);
      break;
    case EXCEPTION_PRIV_INSTRUCTION:
      THROW_OR_JUMP(OSD_Exception_PRIV_INSTRUCTION, aMsg, theStack);
      break;
    case EXCEPTION_STACK_OVERFLOW:
      THROW_OR_JUMP(OSD_Exception_STACK_OVERFLOW, aMsg, theStack);
      break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
      THROW_OR_JUMP(Standard_DivideByZero, aMsg, theStack);
      break;
    case EXCEPTION_FLT_STACK_CHECK:
    case EXCEPTION_FLT_OVERFLOW:
      THROW_OR_JUMP(Standard_Overflow, aMsg, theStack);
      break;
    case EXCEPTION_FLT_UNDERFLOW:
      THROW_OR_JUMP(Standard_Underflow, aMsg, theStack);
      break;
    case EXCEPTION_FLT_INVALID_OPERATION:
    case EXCEPTION_FLT_DENORMAL_OPERAND:
    case EXCEPTION_FLT_INEXACT_RESULT:
    case STATUS_FLOAT_MULTIPLE_TRAPS:
    case STATUS_FLOAT_MULTIPLE_FAULTS:
      THROW_OR_JUMP(Standard_NumericError, aMsg, theStack);
      break;
    default:
      break;
  }
  return EXCEPTION_EXECUTE_HANDLER;
}

  #if !defined(OCCT_UWP) && !defined(__MINGW32__) && !defined(__CYGWIN32__)

LONG _osd_debug(void)
{

  LONG action;

  if (!fDbgLoaded)
  {

    HKEY                hKey   = NULL;
    HANDLE              hEvent = INVALID_HANDLE_VALUE;
    DWORD               dwKeyType;
    DWORD               dwValueLen;
    TCHAR               keyValue[MAX_PATH];
    TCHAR               cmdLine[MAX_PATH];
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    STARTUPINFO         si;

    __try
    {

      if (RegOpenKey(HKEY_LOCAL_MACHINE,
                     TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug"),
                     &hKey)
          != ERROR_SUCCESS)
        __leave;

      dwValueLen = sizeof(keyValue);

      if (RegQueryValueEx(hKey,
                          TEXT("Debugger"),
                          NULL,
                          &dwKeyType,
                          (unsigned char*)keyValue,
                          &dwValueLen)
          != ERROR_SUCCESS)
        __leave;

      sa.nLength              = sizeof(SECURITY_ATTRIBUTES);
      sa.lpSecurityDescriptor = NULL;
      sa.bInheritHandle       = TRUE;

      if ((hEvent = CreateEvent(&sa, TRUE, FALSE, NULL)) == NULL)
        __leave;

      StringCchPrintf(cmdLine, _countof(cmdLine), keyValue, GetCurrentProcessId(), hEvent);

      ZeroMemory(&si, sizeof(STARTUPINFO));

      si.cb      = sizeof(STARTUPINFO);
      si.dwFlags = STARTF_FORCEONFEEDBACK;

      if (!CreateProcess(NULL,
                         cmdLine,
                         NULL,
                         NULL,
                         TRUE,
                         CREATE_DEFAULT_ERROR_MODE,
                         NULL,
                         NULL,
                         &si,
                         &pi))
        __leave;

      WaitForSingleObject(hEvent, INFINITE);

      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);

      fDbgLoaded = TRUE;
    }

    __finally
    {

      if (hKey != INVALID_HANDLE_VALUE)
        CloseHandle(hKey);

      if (hEvent != INVALID_HANDLE_VALUE)
        CloseHandle(hEvent);
    }
  }

  action = fDbgLoaded ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_EXECUTE_HANDLER;

  return action;
}
  #endif

#else

  #include <cstdio>

  #include <OSD_WhoAmI.hpp>
  #include <OSD_SIGHUP.hpp>
  #include <OSD_SIGINT.hpp>
  #include <OSD_SIGQUIT.hpp>
  #include <OSD_SIGILL.hpp>
  #include <OSD_SIGKILL.hpp>
  #include <OSD_SIGBUS.hpp>
  #include <OSD_SIGSEGV.hpp>
  #include <OSD_SIGSYS.hpp>
  #include <Standard_NumericError.hpp>

  #include <Standard_ErrorHandler.hpp>

  #include <pthread.h>

  #ifdef __linux__
    #include <cfenv>

  #endif

static bool fCtrlBrk;

typedef void(ACT_SIGIO_HANDLER)();
ACT_SIGIO_HANDLER* ADR_ACT_SIGIO_HANDLER = nullptr;

  #ifdef __GNUC__
    #include <cstdlib>
  #else
    #ifdef SA_SIGINFO
      #include <sys/siginfo.h>
    #endif
  #endif
typedef void (*SIG_PFV)(int);

  #if !defined(__ANDROID__) && !defined(__QNX__) && !defined(__EMSCRIPTEN__) && defined(__GLIBC__)
    #include <sys/signal.h>
  #endif

  #define _OSD_FPX (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW)

  #ifdef SA_SIGINFO
static void Handler(const int theSignal, siginfo_t*, void* const)
  #else
static void Handler(const int theSignal)
  #endif
{
  struct sigaction oldact, act;

  if (!sigaction(theSignal, nullptr, &oldact))
  {

    if (sigaction(theSignal, &oldact, &act))
      perror("sigaction");
  }
  else
  {
    perror("sigaction");
  }

  if (ADR_ACT_SIGIO_HANDLER != nullptr)
    (*ADR_ACT_SIGIO_HANDLER)();

  sigset_t set;
  sigemptyset(&set);
  switch (theSignal)
  {
    case SIGHUP:
      Standard_ErrorHandler::Abort(OSD_SIGHUP("SIGHUP 'hangup' detected."));
      exit(SIGHUP);
      break;
    case SIGINT:

      fCtrlBrk = true;

      break;
    case SIGQUIT:
      Standard_ErrorHandler::Abort(OSD_SIGQUIT("SIGQUIT 'quit' detected."));
      exit(SIGQUIT);
      break;
    case SIGILL:
      Standard_ErrorHandler::Abort(OSD_SIGILL("SIGILL 'illegal instruction' detected."));
      exit(SIGILL);
      break;
    case SIGKILL:
      Standard_ErrorHandler::Abort(OSD_SIGKILL("SIGKILL 'kill' detected."));
      exit(SIGKILL);
      break;
    case SIGBUS:
      sigaddset(&set, SIGBUS);
      sigprocmask(SIG_UNBLOCK, &set, nullptr);
      Standard_ErrorHandler::Abort(OSD_SIGBUS("SIGBUS 'bus error' detected."));
      exit(SIGBUS);
      break;
    case SIGSEGV:
      Standard_ErrorHandler::Abort(OSD_SIGSEGV("SIGSEGV 'segmentation violation' detected."));
      exit(SIGSEGV);
      break;
  #ifdef SIGSYS
    case SIGSYS:
      Standard_ErrorHandler::Abort(OSD_SIGSYS("SIGSYS 'bad argument to system call' detected."));
      exit(SIGSYS);
      break;
  #endif
    case SIGFPE:
      sigaddset(&set, SIGFPE);
      sigprocmask(SIG_UNBLOCK, &set, nullptr);
  #ifdef __linux__
      OSD::SetFloatingSignal(true);
  #endif
  #if (!defined(__sun)) && (!defined(SOLARIS))
      Standard_ErrorHandler::Abort(Standard_NumericError("SIGFPE Arithmetic exception detected"));
      break;
  #else

      if (aSigInfo)
      {
        switch (aSigInfo->si_code)
        {
          case FPE_FLTDIV_TRAP:
            Standard_ErrorHandler::Abort(Standard_DivideByZero("Floating Divide By Zero"));
            break;
          case FPE_INTDIV_TRAP:
            Standard_ErrorHandler::Abort(Standard_DivideByZero("Integer Divide By Zero"));
            break;
          case FPE_FLTOVF_TRAP:
            Standard_ErrorHandler::Abort(Standard_Overflow("Floating Overflow"));
            break;
          case FPE_INTOVF_TRAP:
            Standard_ErrorHandler::Abort(Standard_Overflow("Integer Overflow"));
            break;
          case FPE_FLTUND_TRAP:
            Standard_ErrorHandler::Abort(Standard_NumericError("Floating Underflow"));
            break;
          case FPE_FLTRES_TRAP:
            Standard_ErrorHandler::Abort(Standard_NumericError("Floating Point Inexact Result"));
            break;
          case FPE_FLTINV_TRAP:
            Standard_ErrorHandler::Abort(Standard_NumericError("Invalid Floating Point Operation"));
            break;
          default:
            Standard_ErrorHandler::Abort(Standard_NumericError("Numeric Error"));
            break;
        }
      }
      else
      {
        Standard_ErrorHandler::Abort(Standard_NumericError("SIGFPE Arithmetic exception detected"));
      }
  #endif
      break;
    default:
  #ifdef OCCT_DEBUG
      std::cout << "Unexpected signal " << theSignal << std::endl;
  #endif
      break;
  }
}

  #ifdef SA_SIGINFO

static void SegvHandler(const int theSignal, siginfo_t* theSigInfo, void* const theContext)
{
  (void)theSignal;
  (void)theContext;
  if (theSigInfo != nullptr)
  {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGSEGV);
    sigprocmask(SIG_UNBLOCK, &set, nullptr);
    void* anAddress = theSigInfo->si_addr;
    {
      char aMsg[100];
      Sprintf(aMsg, "SIGSEGV 'segmentation violation' detected. Address %lx.", (long)anAddress);

      const int aStackLength = OSD_SignalStackTraceLength;
      const int aStackBufLen = std::max(aStackLength * 200, 2048);
      char*     aStackBuffer = aStackLength != 0 ? (char*)alloca(aStackBufLen) : nullptr;
      if (aStackBuffer != nullptr)
      {
        memset(aStackBuffer, 0, aStackBufLen);
        Standard::StackTrace(aStackBuffer, aStackBufLen, aStackLength);
      }

      Standard_ErrorHandler::Abort(OSD_SIGSEGV(aMsg, aStackBuffer));
    }
  }
    #ifdef OCCT_DEBUG
  else
  {
    std::cout << "Wrong undefined address." << std::endl;
  }
    #endif
  exit(SIGSEGV);
}

  #elif defined(_hpux) || defined(HPUX)

static void SegvHandler(const int theSignal, siginfo_t* theSigInfo, void* const theContext)
{
  if (theContext != NULL)
  {
    unsigned long aSpace   = ((struct sigcontext*)theContext)->sc_sl.sl_ss.ss_cr20;
    unsigned long anOffset = ((struct sigcontext*)theContext)->sc_sl.sl_ss.ss_cr21;
    {
      char aMsg[100];
      Sprintf(aMsg, "SIGSEGV 'segmentation violation' detected. Address %lx", anOffset);
      Standard_ErrorHandler::Abort(OSD_SIGSEGV(aMsg));
    }
  }
    #ifdef OCCT_DEBUG
  else
  {
    std::cout << "Wrong undefined address." << std::endl;
  }
    #endif
  exit(SIGSEGV);
}

  #endif

void OSD::SetFloatingSignal(bool theFloatingSignal)
{
  #if defined(__linux__) && defined(__GLIBC__)
  feclearexcept(FE_ALL_EXCEPT);
  if (theFloatingSignal)
  {
    feenableexcept(_OSD_FPX);
  }
  else
  {
    fedisableexcept(_OSD_FPX);
  }
  #elif defined(__sun) || defined(SOLARIS)
  int                 aSunStat     = 0;
  sigfpe_handler_type anFpeHandler = (theFloatingSignal ? (sigfpe_handler_type)Handler : NULL);
  aSunStat                         = ieee_handler("set", "invalid", anFpeHandler);
  aSunStat                         = ieee_handler("set", "division", anFpeHandler) || aSunStat;
  aSunStat                         = ieee_handler("set", "overflow", anFpeHandler) || aSunStat;
  if (aSunStat)
  {
    #ifdef OCCT_DEBUG
    std::cerr << "ieee_handler does not work !!! KO\n";
    #endif
  }
  #else
  (void)theFloatingSignal;
  #endif
}

bool OSD::ToCatchFloatingSignals()
{
  #if defined(__linux__) && defined(__GLIBC__)
  return (fegetexcept() & _OSD_FPX) != 0;
  #else
  return false;
  #endif
}

void OSD::SetThreadLocalSignal(OSD_SignalMode, bool theFloatingSignal)
{
  SetFloatingSignal(theFloatingSignal);
}

void OSD::SetSignal(OSD_SignalMode theSignalMode, bool theFloatingSignal)
{
  SetFloatingSignal(theFloatingSignal);

  OSD_WasSetSignal = theSignalMode;
  if (theSignalMode == OSD_SignalMode_AsIs)
  {
    return;
  }

  struct sigaction anActSet, anActDfl, anActOld;
  sigemptyset(&anActSet.sa_mask);
  sigemptyset(&anActDfl.sa_mask);
  sigemptyset(&anActOld.sa_mask);
  #ifdef SA_RESTART
  anActSet.sa_flags = anActDfl.sa_flags = anActOld.sa_flags = SA_RESTART;
  #else
  anActSet.sa_flags = anActDfl.sa_flags = anActOld.sa_flags = 0;
  #endif
  #ifdef SA_SIGINFO
  anActSet.sa_flags     = anActSet.sa_flags | SA_SIGINFO;
  anActSet.sa_sigaction = Handler;
  #else
  anActSet.sa_handler = Handler;
  #endif
  anActDfl.sa_handler = SIG_DFL;

  const int NBSIG = 8;
  const int aSignalTypes[NBSIG] =
    {SIGFPE, SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGBUS, SIGSYS, SIGSEGV};
  for (int i = 0; i < NBSIG; ++i)
  {

    if (aSignalTypes[i] == SIGSEGV)
    {
  #ifdef SA_SIGINFO
      anActSet.sa_sigaction = SegvHandler;
  #else
      anActSet.sa_handler = SegvHandler;
  #endif
    }

    int retcode = -1;
    if (theSignalMode == OSD_SignalMode_Set || theSignalMode == OSD_SignalMode_SetUnhandled)
    {
      retcode = sigaction(aSignalTypes[i], &anActSet, &anActOld);
    }
    else if (theSignalMode == OSD_SignalMode_Unset)
    {
      retcode = sigaction(aSignalTypes[i], &anActDfl, &anActOld);
    }
    if (theSignalMode == OSD_SignalMode_SetUnhandled && retcode == 0
        && anActOld.sa_handler != SIG_DFL)
    {
      struct sigaction anActOld2;
      sigemptyset(&anActOld2.sa_mask);
      retcode = sigaction(aSignalTypes[i], &anActOld, &anActOld2);
    }
    Standard_ASSERT(retcode == 0,
                    "sigaction() failed",
                    std::cout << "OSD::SetSignal(): sigaction() failed for " << aSignalTypes[i]
                              << std::endl);
  }
}

void OSD ::ControlBreak()
{
  if (fCtrlBrk)
  {
    fCtrlBrk = false;
    throw OSD_Exception_CTRL_BREAK("*** INTERRUPT ***");
  }
}

#endif
