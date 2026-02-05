#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_StdFail_UndefinedDerivative
  #define StdFail_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)                                 \
    if (CONDITION)                                                                                 \
      throw StdFail_UndefinedDerivative(MESSAGE);
#else
  #define StdFail_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(StdFail_UndefinedDerivative, Standard_DomainError)
