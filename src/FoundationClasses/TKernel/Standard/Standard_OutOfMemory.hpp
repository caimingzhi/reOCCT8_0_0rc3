#pragma once


#include <Standard_ProgramError.hpp>

#include <memory>

#if !defined No_Exception && !defined No_Standard_OutOfMemory
  #define Standard_OutOfMemory_Raise_if(CONDITION, MESSAGE)                                        \
    if (CONDITION)                                                                                 \
      throw Standard_OutOfMemory(MESSAGE);
#else
  #define Standard_OutOfMemory_Raise_if(CONDITION, MESSAGE)
#endif

//! Standard_OutOfMemory exception is defined explicitly and not by
//! macro DEFINE_STANDARD_EXCEPTION, to avoid necessity of dynamic
//! memory allocations during throwing and stack unwinding:
//!
//! - message string is stored as field, not allocated dynamically
//!   (storable message length is limited by buffer size)
//!
//! The reason is that in out-of-memory condition any memory allocation can
//! fail, thus use of operator new for allocation of new exception instance
//! is dangerous (can cause recursion until stack overflow, see #24836).
class Standard_OutOfMemory : public Standard_ProgramError
{
public:
  //! Constructor is kept public for backward compatibility.
  //! @param theMessage optional error message
  Standard_EXPORT Standard_OutOfMemory(const char* theMessage = nullptr);

  //! Returns error message (implements std::exception interface).
  Standard_EXPORT const char* what() const noexcept override;

  //! Returns the exception type name.
  const char* ExceptionType() const noexcept override { return "Standard_OutOfMemory"; }

  //! Sets error message.
  //! @param theMessage error message (can be nullptr)
  Standard_EXPORT void SetMessageString(const char* theMessage);

private:
  char myBuffer[1024];
};

