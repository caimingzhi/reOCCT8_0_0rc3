#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Interface_InterfaceError.hpp>

#if !defined No_Exception && !defined No_Interface_InterfaceMismatch
  #define Interface_InterfaceMismatch_Raise_if(CONDITION, MESSAGE)                                 \
    if (CONDITION)                                                                                 \
      throw Interface_InterfaceMismatch(MESSAGE);
#else
  #define Interface_InterfaceMismatch_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Interface_InterfaceMismatch, Interface_InterfaceError)

