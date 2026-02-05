#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Standard_NoMoreObject
  #define Standard_NoMoreObject_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw Standard_NoMoreObject(MESSAGE);
#else
  #define Standard_NoMoreObject_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_NoMoreObject, Standard_DomainError)
