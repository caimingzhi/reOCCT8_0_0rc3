#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_RangeError.hpp>

#if !defined No_Exception && !defined No_Standard_NullValue
  #define Standard_NullValue_Raise_if(CONDITION, MESSAGE)                                          \
    if (CONDITION)                                                                                 \
      throw Standard_NullValue(MESSAGE);
#else
  #define Standard_NullValue_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_NullValue, Standard_RangeError)
