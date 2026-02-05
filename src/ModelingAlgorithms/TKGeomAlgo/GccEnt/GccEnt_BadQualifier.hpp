#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_GccEnt_BadQualifier
  #define GccEnt_BadQualifier_Raise_if(CONDITION, MESSAGE)                                         \
    if (CONDITION)                                                                                 \
      throw GccEnt_BadQualifier(MESSAGE);
#else
  #define GccEnt_BadQualifier_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(GccEnt_BadQualifier, Standard_DomainError)
