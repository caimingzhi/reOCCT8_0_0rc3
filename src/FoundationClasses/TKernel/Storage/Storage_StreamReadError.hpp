#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Storage_StreamReadError
  #define Storage_StreamReadError_Raise_if(CONDITION, MESSAGE)                                     \
    if (CONDITION)                                                                                 \
      throw app::storage::Storage_StreamReadError(MESSAGE);
#else
  #define Storage_StreamReadError_Raise_if(CONDITION, MESSAGE)
#endif

namespace app { namespace storage {
DEFINE_STANDARD_EXCEPTION(Storage_StreamReadError, Standard_Failure)
}} // namespace app::storage

