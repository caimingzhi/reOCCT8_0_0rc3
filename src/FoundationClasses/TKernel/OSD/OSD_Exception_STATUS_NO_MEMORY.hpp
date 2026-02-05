#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_STATUS_NO_MEMORY
  #define OSD_Exception_STATUS_NO_MEMORY_Raise_if(CONDITION, MESSAGE)                              \
    if (CONDITION)                                                                                 \
      throw OSD_Exception_STATUS_NO_MEMORY(MESSAGE);
#else
  #define OSD_Exception_STATUS_NO_MEMORY_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_Exception_STATUS_NO_MEMORY, OSD_Exception)
