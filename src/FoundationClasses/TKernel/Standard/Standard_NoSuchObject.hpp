#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Standard_NoSuchObject
  #define Standard_NoSuchObject_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw Standard_NoSuchObject(MESSAGE);
#else
  #define Standard_NoSuchObject_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_NoSuchObject, Standard_DomainError)

