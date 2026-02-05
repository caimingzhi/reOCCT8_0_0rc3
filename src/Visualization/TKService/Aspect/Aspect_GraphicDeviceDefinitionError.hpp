#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_OutOfRange.hpp>

#if !defined No_Exception && !defined No_Aspect_GraphicDeviceDefinitionError
  #define Aspect_GraphicDeviceDefinitionError_Raise_if(CONDITION, MESSAGE)                         \
    if (CONDITION)                                                                                 \
      throw Aspect_GraphicDeviceDefinitionError(MESSAGE);
#else
  #define Aspect_GraphicDeviceDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Aspect_GraphicDeviceDefinitionError, Standard_OutOfRange)
