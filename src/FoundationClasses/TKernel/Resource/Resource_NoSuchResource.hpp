#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_NoSuchObject.hpp>

#if !defined No_Exception && !defined No_Resource_NoSuchResource
  #define Resource_NoSuchResource_Raise_if(CONDITION, MESSAGE)                                     \
    if (CONDITION)                                                                                 \
      throw Resource_NoSuchResource(MESSAGE);
#else
  #define Resource_NoSuchResource_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Resource_NoSuchResource, Standard_NoSuchObject)
