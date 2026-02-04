#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Draw_Failure
  #define Draw_Failure_Raise_if(CONDITION, MESSAGE)                                                \
    if (CONDITION)                                                                                 \
      throw Draw_Failure(MESSAGE);
#else
  #define Draw_Failure_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Draw_Failure, Standard_Failure)

