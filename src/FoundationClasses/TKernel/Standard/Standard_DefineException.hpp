#pragma once


#include <Standard_SStream.hpp>

#include <memory>

//! @brief Defines an exception class inheriting from Standard_Failure.
//!
//! This macro creates a complete exception class with:
//! - Constructors that forward to base class
//! - ExceptionType() override returning the class name
//!
//! Usage:
//! @code
//! DEFINE_STANDARD_EXCEPTION(Standard_OutOfRange, Standard_RangeError)
//! @endcode
//!
//! @param C1 Name of the exception class to define
//! @param C2 Name of the parent exception class (must be Standard_Failure or derived)
#define DEFINE_STANDARD_EXCEPTION(C1, C2)                                                          \
  class C1 : public C2                                                                             \
  {                                                                                                \
  public:                                                                                          \
    C1(const char* theMessage = "")                                                                \
        : C2(theMessage)                                                                           \
    {                                                                                              \
    }                                                                                              \
                                                                                                   \
    C1(const char* theMessage, const char* theStackTrace)                                          \
        : C2(theMessage, theStackTrace)                                                            \
    {                                                                                              \
    }                                                                                              \
                                                                                                   \
    const char* ExceptionType() const noexcept override                                            \
    {                                                                                              \
      return #C1;                                                                                  \
    }                                                                                              \
  };

