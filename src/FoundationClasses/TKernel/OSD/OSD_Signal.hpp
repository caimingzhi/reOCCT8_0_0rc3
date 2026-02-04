#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_OSD_Signal
  #define OSD_Signal_Raise_if(CONDITION, MESSAGE)                                                  \
    if (CONDITION)                                                                                 \
      throw OSD_Signal(MESSAGE);
#else
  #define OSD_Signal_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_Signal, Standard_Failure)

