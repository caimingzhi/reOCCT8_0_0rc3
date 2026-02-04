#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Standard_ProgramError
  #define Standard_ProgramError_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw Standard_ProgramError(MESSAGE);
#else
  #define Standard_ProgramError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_ProgramError, Standard_Failure)

