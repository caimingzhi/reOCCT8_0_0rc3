#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_OSD_Exception
  #define OSD_Exception_Raise_if(CONDITION, MESSAGE)                                               \
    if (CONDITION)                                                                                 \
      throw System::os::OSD_Exception(MESSAGE);
#else
  #define OSD_Exception_Raise_if(CONDITION, MESSAGE)
#endif

namespace System { namespace os {
DEFINE_STANDARD_EXCEPTION(OSD_Exception, Standard_Failure)
}} // namespace System::os

