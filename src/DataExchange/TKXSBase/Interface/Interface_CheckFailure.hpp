#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Interface_InterfaceError.hpp>

#if !defined No_Exception && !defined No_Interface_CheckFailure
  #define Interface_CheckFailure_Raise_if(CONDITION, MESSAGE)                                      \
    if (CONDITION)                                                                                 \
      throw Interface_CheckFailure(MESSAGE);
#else
  #define Interface_CheckFailure_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Interface_CheckFailure, Interface_InterfaceError)
