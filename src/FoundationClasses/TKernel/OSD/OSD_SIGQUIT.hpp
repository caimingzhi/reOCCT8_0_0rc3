#pragma once


#include <Standard_SStream.hpp>
#include <OSD_Signal.hpp>

#if !defined No_Exception && !defined No_OSD_SIGQUIT
  #define OSD_SIGQUIT_Raise_if(CONDITION, MESSAGE)                                                 \
    if (CONDITION)                                                                                 \
      throw OSD_SIGQUIT(MESSAGE);
#else
  #define OSD_SIGQUIT_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_SIGQUIT, OSD_Signal)

