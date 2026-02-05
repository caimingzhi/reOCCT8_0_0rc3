#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_OutOfRange.hpp>

#if !defined No_Exception && !defined No_V3d_BadValue
  #define V3d_BadValue_Raise_if(CONDITION, MESSAGE)                                                \
    if (CONDITION)                                                                                 \
      throw V3d_BadValue(MESSAGE);
#else
  #define V3d_BadValue_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(V3d_BadValue, Standard_OutOfRange)
