#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Signal.hpp>

#if !defined No_Exception && !defined No_OSD_SIGSEGV
  #define OSD_SIGSEGV_Raise_if(CONDITION, MESSAGE)                                                 \
    if (CONDITION)                                                                                 \
      throw OSD_SIGSEGV(MESSAGE);
#else
  #define OSD_SIGSEGV_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_SIGSEGV, OSD_Signal)

