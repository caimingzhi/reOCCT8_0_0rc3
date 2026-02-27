#pragma once

#include <Standard_SStream.hpp>
#include <OSD_Signal.hpp>

#if !defined No_Exception && !defined No_OSD_SIGHUP
  #define OSD_SIGHUP_Raise_if(CONDITION, MESSAGE)                                                  \
    if (CONDITION)                                                                                 \
      throw System::os::OSD_SIGHUP(MESSAGE);
#else
  #define OSD_SIGHUP_Raise_if(CONDITION, MESSAGE)
#endif

namespace System { namespace os {
DEFINE_STANDARD_EXCEPTION(OSD_SIGHUP, System::os::OSD_Signal)
}} // namespace System::os

