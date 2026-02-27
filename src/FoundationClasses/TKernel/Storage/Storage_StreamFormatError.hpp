#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Storage_StreamFormatError
  #define Storage_StreamFormatError_Raise_if(CONDITION, MESSAGE)                                   \
    if (CONDITION)                                                                                 \
      throw app::storage::Storage_StreamFormatError(MESSAGE);
#else
  #define Storage_StreamFormatError_Raise_if(CONDITION, MESSAGE)
#endif

namespace app { namespace storage {
DEFINE_STANDARD_EXCEPTION(Storage_StreamFormatError, Standard_Failure)
}} // namespace app::storage

