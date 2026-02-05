#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_OutOfRange.hpp>

#if !defined No_Exception && !defined No_Aspect_WindowDefinitionError
  #define Aspect_WindowDefinitionError_Raise_if(CONDITION, MESSAGE)                                \
    if (CONDITION)                                                                                 \
      throw Aspect_WindowDefinitionError(MESSAGE);
#else
  #define Aspect_WindowDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Aspect_WindowDefinitionError, Standard_OutOfRange)
