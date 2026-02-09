#pragma once

#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Standard_RangeError
  #if (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))

    #define Standard_RangeError_Raise_if(CONDITION, MESSAGE)                                       \
      _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wstrict-overflow\"") if (  \
        CONDITION) throw Standard_RangeError(MESSAGE);                                             \
      _Pragma("GCC diagnostic pop")
  #else
    #define Standard_RangeError_Raise_if(CONDITION, MESSAGE)                                       \
      if (CONDITION)                                                                               \
        throw Standard_RangeError(MESSAGE);
  #endif
#else
  #define Standard_RangeError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_RangeError, Standard_DomainError)
