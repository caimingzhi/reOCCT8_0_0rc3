#pragma once

#include <Standard.hpp>

#include <setjmp.h>
#include <variant>
#include <iostream>

#include <OSD_SIGBUS.hpp>
#include <OSD_SIGHUP.hpp>
#include <OSD_SIGILL.hpp>
#include <OSD_SIGINT.hpp>
#include <OSD_SIGKILL.hpp>
#include <OSD_SIGQUIT.hpp>
#include <OSD_SIGSEGV.hpp>
#include <OSD_SIGSYS.hpp>
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
#include <Standard_DivideByZero.hpp>
#include <Standard_NumericError.hpp>
#include <Standard_Overflow.hpp>
#include <Standard_ProgramError.hpp>
#include <Standard_Underflow.hpp>

#if defined(OCC_CONVERT_SIGNALS)

  #define OCC_CATCH_SIGNALS                                                                        \
    Standard_ErrorHandler _aHandler;                                                               \
    if (setjmp(_aHandler.Label()))                                                                 \
    {                                                                                              \
      _aHandler.Raise();                                                                           \
    }

  #if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__)
    #pragma GCC diagnostic ignored "-Wclobbered"
  #endif

#else

  #define OCC_CATCH_SIGNALS

#endif

class Standard_ErrorHandler
{
public:
  using SignalException = std::variant<std::monostate,
                                       OSD_SIGBUS,
                                       OSD_SIGHUP,
                                       OSD_SIGILL,
                                       OSD_SIGINT,
                                       OSD_SIGKILL,
                                       OSD_SIGQUIT,
                                       OSD_SIGSEGV,
                                       OSD_SIGSYS,
                                       OSD_Exception_ACCESS_VIOLATION,
                                       OSD_Exception_ARRAY_BOUNDS_EXCEEDED,
                                       OSD_Exception_ILLEGAL_INSTRUCTION,
                                       OSD_Exception_IN_PAGE_ERROR,
                                       OSD_Exception_INT_OVERFLOW,
                                       OSD_Exception_INVALID_DISPOSITION,
                                       OSD_Exception_NONCONTINUABLE_EXCEPTION,
                                       OSD_Exception_PRIV_INSTRUCTION,
                                       OSD_Exception_STACK_OVERFLOW,
                                       OSD_Exception_STATUS_NO_MEMORY,
                                       Standard_DivideByZero,
                                       Standard_NumericError,
                                       Standard_Overflow,
                                       Standard_ProgramError,
                                       Standard_Underflow>;

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Standard_ErrorHandler();

  Standard_EXPORT void Destroy();

  ~Standard_ErrorHandler() { Destroy(); }

  Standard_EXPORT void Raise();

  jmp_buf& Label() { return myLabel; }

  const SignalException& Error() const { return myCaughtError; }

  Standard_EXPORT static bool IsInTryBlock();

  template <typename T>
  static void Abort(const T& theError);

private:
  void Unlink();

  Standard_EXPORT static Standard_ErrorHandler* FindHandler();

public:
  class Callback
  {
  public:
    DEFINE_STANDARD_ALLOC

#if defined(OCC_CONVERT_SIGNALS)
    Standard_EXPORT
#endif
      void
      RegisterCallback();

#if defined(OCC_CONVERT_SIGNALS)
    Standard_EXPORT
#endif
      void
      UnregisterCallback();

#if defined(OCC_CONVERT_SIGNALS)
    Standard_EXPORT
#endif
      virtual ~Callback();

    Standard_EXPORT virtual void DestroyCallback() = 0;

  protected:
#if defined(OCC_CONVERT_SIGNALS)
    Standard_EXPORT
#endif
      Callback();

  private:
    void* myHandler = nullptr;
    void* myPrev    = nullptr;
    void* myNext    = nullptr;

    friend class Standard_ErrorHandler;
  };

private:
  SignalException        myCaughtError;
  Standard_ErrorHandler* myPrevious    = nullptr;
  Callback*              myCallbackPtr = nullptr;
  jmp_buf                myLabel       = {};
};

template <typename T>
void Standard_ErrorHandler::Abort(const T& theError)
{
#ifndef OCC_CONVERT_SIGNALS
  throw theError;
#else
  Standard_ErrorHandler* anActive = FindHandler();
  if (anActive == nullptr)
  {
    std::cerr << "*** Abort *** an exception was raised, but no catch was found." << std::endl;
    std::cerr << "\t... The exception is: " << theError.what() << std::endl;
    exit(1);
  }
  anActive->myCaughtError = theError;
  longjmp(anActive->myLabel, true);
#endif
}

#if !defined(OCC_CONVERT_SIGNALS)
inline Standard_ErrorHandler::Callback::Callback() {}

inline Standard_ErrorHandler::Callback::~Callback() {}

inline void Standard_ErrorHandler::Callback::RegisterCallback() {}

inline void Standard_ErrorHandler::Callback::UnregisterCallback() {}
#endif

typedef Standard_ErrorHandler::Callback Standard_ErrorHandlerCallback;
