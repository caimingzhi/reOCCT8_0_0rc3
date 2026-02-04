#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Interface_InterfaceError
  #define Interface_InterfaceError_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw Interface_InterfaceError(MESSAGE);
#else
  #define Interface_InterfaceError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Interface_InterfaceError, Standard_Failure)

