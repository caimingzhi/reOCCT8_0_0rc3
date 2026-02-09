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

class Standard_OutOfMemory : public Standard_ProgramError
{
public:
  Standard_EXPORT Standard_OutOfMemory(const char* theMessage = nullptr);

  Standard_EXPORT const char* what() const noexcept override;

  const char* ExceptionType() const noexcept override { return "Standard_OutOfMemory"; }

  Standard_EXPORT void SetMessageString(const char* theMessage);

private:
  char myBuffer[1024];
};
