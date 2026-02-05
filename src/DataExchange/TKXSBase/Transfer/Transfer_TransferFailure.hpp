#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Interface_InterfaceError.hpp>

#if !defined No_Exception && !defined No_Transfer_TransferFailure
  #define Transfer_TransferFailure_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw Transfer_TransferFailure(MESSAGE);
#else
  #define Transfer_TransferFailure_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Transfer_TransferFailure, Interface_InterfaceError)
