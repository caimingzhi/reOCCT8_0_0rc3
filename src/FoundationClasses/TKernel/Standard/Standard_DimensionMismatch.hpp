#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DimensionError.hpp>

#if !defined No_Exception && !defined No_Standard_DimensionMismatch
  #define Standard_DimensionMismatch_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw Standard_DimensionMismatch(MESSAGE);
#else
  #define Standard_DimensionMismatch_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_DimensionMismatch, Standard_DimensionError)
