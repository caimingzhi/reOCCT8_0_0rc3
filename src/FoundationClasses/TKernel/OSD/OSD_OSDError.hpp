#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_OSD_OSDError
  #define OSD_OSDError_Raise_if(CONDITION, MESSAGE)                                                \
    if (CONDITION)                                                                                 \
      throw OSD_OSDError(MESSAGE);
#else
  #define OSD_OSDError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_OSDError, Standard_Failure)

