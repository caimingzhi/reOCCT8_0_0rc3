#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_LProp_NotDefined
  #define LProp_NotDefined_Raise_if(CONDITION, MESSAGE)                                            \
    if (CONDITION)                                                                                 \
      throw LProp_NotDefined(MESSAGE);
#else
  #define LProp_NotDefined_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(LProp_NotDefined, Standard_Failure)
