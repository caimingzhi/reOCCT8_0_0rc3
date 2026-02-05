#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_NoSuchObject.hpp>

#if !defined No_Exception && !defined No_Units_NoSuchUnit
  #define Units_NoSuchUnit_Raise_if(CONDITION, MESSAGE)                                            \
    if (CONDITION)                                                                                 \
      throw Units_NoSuchUnit(MESSAGE);
#else
  #define Units_NoSuchUnit_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Units_NoSuchUnit, Standard_NoSuchObject)
