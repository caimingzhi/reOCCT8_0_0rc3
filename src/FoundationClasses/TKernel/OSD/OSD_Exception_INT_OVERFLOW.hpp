#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_INT_OVERFLOW
  #define OSD_Exception_INT_OVERFLOW_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw OSD_Exception_INT_OVERFLOW(MESSAGE);
#else
  #define OSD_Exception_INT_OVERFLOW_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(OSD_Exception_INT_OVERFLOW, OSD_Exception)

