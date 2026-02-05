#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_V3d_UnMapped
  #define V3d_UnMapped_Raise_if(CONDITION, MESSAGE)                                                \
    if (CONDITION)                                                                                 \
      throw V3d_UnMapped(MESSAGE);
#else
  #define V3d_UnMapped_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(V3d_UnMapped, Standard_DomainError)
