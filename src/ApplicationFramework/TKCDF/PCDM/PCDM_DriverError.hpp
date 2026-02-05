#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_PCDM_DriverError
  #define PCDM_DriverError_Raise_if(CONDITION, MESSAGE)                                            \
    if (CONDITION)                                                                                 \
      throw PCDM_DriverError(MESSAGE);
#else
  #define PCDM_DriverError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(PCDM_DriverError, Standard_Failure)
