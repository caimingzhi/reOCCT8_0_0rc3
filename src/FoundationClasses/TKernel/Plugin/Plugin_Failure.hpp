#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Plugin_Failure
  #define Plugin_Failure_Raise_if(CONDITION, MESSAGE)                                              \
    if (CONDITION)                                                                                 \
      throw Plugin_Failure(MESSAGE);
#else
  #define Plugin_Failure_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Plugin_Failure, Standard_Failure)
