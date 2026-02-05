#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Standard_DomainError
  #define Standard_DomainError_Raise_if(CONDITION, MESSAGE)                                        \
    if (CONDITION)                                                                                 \
      throw Standard_DomainError(MESSAGE);
#else
  #define Standard_DomainError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_DomainError, Standard_Failure)
