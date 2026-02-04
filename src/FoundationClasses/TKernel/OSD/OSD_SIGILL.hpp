#pragma once


#include <Standard_SStream.hpp>
#include <OSD_Signal.hpp>

#if !defined No_Exception && !defined No_OSD_SIGILL
  #define OSD_SIGILL_Raise_if(CONDITION, MESSAGE)                                                  \
    if (CONDITION)                                                                                 \
      throw OSD_SIGILL(MESSAGE);
#else
  #define OSD_SIGILL_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_SIGILL, OSD_Signal)

