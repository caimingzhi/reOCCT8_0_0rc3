#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_StdFail_NotDone
  #define StdFail_NotDone_Raise_if(CONDITION, MESSAGE)                                             \
    if (CONDITION)                                                                                 \
      throw StdFail_NotDone(MESSAGE);
#else
  #define StdFail_NotDone_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(StdFail_NotDone, Standard_Failure)

