#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_NumericError.hpp>

#if !defined No_Exception && !defined No_Standard_DivideByZero
  #define Standard_DivideByZero_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw Standard_DivideByZero(MESSAGE);
#else
  #define Standard_DivideByZero_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_DivideByZero, Standard_NumericError)

