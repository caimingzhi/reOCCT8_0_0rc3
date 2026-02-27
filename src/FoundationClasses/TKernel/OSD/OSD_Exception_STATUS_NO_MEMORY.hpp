#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_STATUS_NO_MEMORY
  #define OSD_Exception_STATUS_NO_MEMORY_Raise_if(CONDITION, MESSAGE)                              \
    if (CONDITION)                                                                                 \
      throw System::os::OSD_Exception_STATUS_NO_MEMORY(MESSAGE);
#else
  #define OSD_Exception_STATUS_NO_MEMORY_Raise_if(CONDITION, MESSAGE)
#endif

namespace System { namespace os {
DEFINE_STANDARD_EXCEPTION(OSD_Exception_STATUS_NO_MEMORY, System::os::OSD_Exception)
}} // namespace System::os

