#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_RangeError.hpp>

#if !defined No_Exception && !defined No_Standard_NegativeValue
  #define Standard_NegativeValue_Raise_if(CONDITION, MESSAGE)                                      \
    if (CONDITION)                                                                                 \
      throw Standard_NegativeValue(MESSAGE);
#else
  #define Standard_NegativeValue_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_NegativeValue, Standard_RangeError)
