#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <OSD_Exception.hpp>

#if !defined No_Exception && !defined No_OSD_Exception_NONCONTINUABLE_EXCEPTION
  #define OSD_Exception_NONCONTINUABLE_EXCEPTION_Raise_if(CONDITION, MESSAGE)                      \
    if (CONDITION)                                                                                 \
      throw System::os::OSD_Exception_NONCONTINUABLE_EXCEPTION(MESSAGE);
#else
  #define OSD_Exception_NONCONTINUABLE_EXCEPTION_Raise_if(CONDITION, MESSAGE)
#endif

namespace System { namespace os {
DEFINE_STANDARD_EXCEPTION(OSD_Exception_NONCONTINUABLE_EXCEPTION, System::os::OSD_Exception)
}} // namespace System::os

