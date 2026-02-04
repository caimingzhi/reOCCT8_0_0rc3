#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_OutOfRange.hpp>

#if !defined No_Exception && !defined No_Aspect_IdentDefinitionError
  #define Aspect_IdentDefinitionError_Raise_if(CONDITION, MESSAGE)                                 \
    if (CONDITION)                                                                                 \
      throw Aspect_IdentDefinitionError(MESSAGE);
#else
  #define Aspect_IdentDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Aspect_IdentDefinitionError, Standard_OutOfRange)

