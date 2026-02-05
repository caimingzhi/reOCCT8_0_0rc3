#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_NumericError.hpp>

#if !defined No_Exception && !defined No_Standard_Underflow
  #define Standard_Underflow_Raise_if(CONDITION, MESSAGE)                                          \
    if (CONDITION)                                                                                 \
      throw Standard_Underflow(MESSAGE);
#else
  #define Standard_Underflow_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_Underflow, Standard_NumericError)
