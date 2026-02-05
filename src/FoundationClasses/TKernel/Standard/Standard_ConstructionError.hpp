#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Standard_ConstructionError
  #define Standard_ConstructionError_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw Standard_ConstructionError(MESSAGE);
#else
  #define Standard_ConstructionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_ConstructionError, Standard_DomainError)
