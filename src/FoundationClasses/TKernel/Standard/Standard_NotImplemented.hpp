#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_ProgramError.hpp>

#if !defined No_Exception && !defined No_Standard_NotImplemented
  #define Standard_NotImplemented_Raise_if(CONDITION, MESSAGE)                                     \
    if (CONDITION)                                                                                 \
      throw Standard_NotImplemented(MESSAGE);
#else
  #define Standard_NotImplemented_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_NotImplemented, Standard_ProgramError)

