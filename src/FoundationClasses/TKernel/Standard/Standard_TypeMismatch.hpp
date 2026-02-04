#pragma once


#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Standard_TypeMismatch
  #define Standard_TypeMismatch_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw Standard_TypeMismatch(MESSAGE);
#else
  #define Standard_TypeMismatch_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_TypeMismatch, Standard_DomainError)

