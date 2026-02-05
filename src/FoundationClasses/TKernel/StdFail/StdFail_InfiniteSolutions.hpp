#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_StdFail_InfiniteSolutions
  #define StdFail_InfiniteSolutions_Raise_if(CONDITION, MESSAGE)                                   \
    if (CONDITION)                                                                                 \
      throw StdFail_InfiniteSolutions(MESSAGE);
#else
  #define StdFail_InfiniteSolutions_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(StdFail_InfiniteSolutions, Standard_Failure)
