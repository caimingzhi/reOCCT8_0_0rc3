#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Storage_StreamReadError.hpp>

#if !defined No_Exception && !defined No_Storage_StreamExtCharParityError
  #define Storage_StreamExtCharParityError_Raise_if(CONDITION, MESSAGE)                            \
    if (CONDITION)                                                                                 \
      throw Storage_StreamExtCharParityError(MESSAGE);
#else
  #define Storage_StreamExtCharParityError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Storage_StreamExtCharParityError, Storage_StreamReadError)
