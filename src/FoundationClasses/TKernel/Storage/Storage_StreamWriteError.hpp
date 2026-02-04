#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Storage_StreamWriteError
  #define Storage_StreamWriteError_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw Storage_StreamWriteError(MESSAGE);
#else
  #define Storage_StreamWriteError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Storage_StreamWriteError, Standard_Failure)

