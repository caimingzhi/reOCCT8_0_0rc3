#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_STACK_OVERFLOW
  #define OSD_Exception_STACK_OVERFLOW_Raise_if(CONDITION, MESSAGE)                                \
    if (CONDITION)                                                                                 \
      throw System::os::OSD_Exception_STACK_OVERFLOW(MESSAGE);
#else
  #define OSD_Exception_STACK_OVERFLOW_Raise_if(CONDITION, MESSAGE)
#endif

namespace System { namespace os {
DEFINE_STANDARD_EXCEPTION(OSD_Exception_STACK_OVERFLOW, System::os::OSD_Exception)
}} // namespace System::os

