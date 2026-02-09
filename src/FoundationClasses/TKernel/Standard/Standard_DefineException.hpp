#pragma once

#include <Standard_SStream.hpp>

#include <memory>

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
