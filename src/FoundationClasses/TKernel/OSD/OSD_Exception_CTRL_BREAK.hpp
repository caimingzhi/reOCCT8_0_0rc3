#pragma once

#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_CTRL_BREAK
  #define OSD_Exception_CTRL_BREAK_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw OSD_Exception_CTRL_BREAK(MESSAGE);
#else
  #define OSD_Exception_CTRL_BREAK_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_Exception_CTRL_BREAK, OSD_Exception)
