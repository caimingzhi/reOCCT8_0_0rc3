#pragma once

#include <Standard_SStream.hpp>
#include <Standard_RangeError.hpp>

#if (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))

  #define Standard_OutOfRange_Always_Raise_if(CONDITION, MESSAGE)                                  \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wstrict-overflow\"") if (    \
      CONDITION) throw Standard_OutOfRange(MESSAGE);                                               \
    _Pragma("GCC diagnostic pop")
#else
  #define Standard_OutOfRange_Always_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw Standard_OutOfRange(MESSAGE);
#endif

#if !defined No_Exception && !defined No_Standard_OutOfRange
  #define Standard_OutOfRange_Raise_if(CONDITION, MESSAGE)                                         \
    Standard_OutOfRange_Always_Raise_if(CONDITION, MESSAGE)
#else
  #define Standard_OutOfRange_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Standard_OutOfRange, Standard_RangeError)
