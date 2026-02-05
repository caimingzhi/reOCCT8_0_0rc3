#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DimensionError.hpp>

class math_NotSquare;
DEFINE_STANDARD_HANDLE(math_NotSquare, Standard_DimensionError)

#if !defined No_Exception && !defined No_math_NotSquare
  #define math_NotSquare_Raise_if(CONDITION, MESSAGE)                                              \
    if (CONDITION)                                                                                 \
      throw math_NotSquare(MESSAGE);
#else
  #define math_NotSquare_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(math_NotSquare, Standard_DimensionError)
