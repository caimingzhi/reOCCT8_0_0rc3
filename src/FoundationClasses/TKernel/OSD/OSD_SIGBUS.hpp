#pragma once


#include <Standard_SStream.hpp>
#include <OSD_Signal.hpp>

#if !defined No_Exception && !defined No_OSD_SIGBUS
  #define OSD_SIGBUS_Raise_if(CONDITION, MESSAGE)                                                  \
    if (CONDITION)                                                                                 \
      throw OSD_SIGBUS(MESSAGE);
#else
  #define OSD_SIGBUS_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_SIGBUS, OSD_Signal)

