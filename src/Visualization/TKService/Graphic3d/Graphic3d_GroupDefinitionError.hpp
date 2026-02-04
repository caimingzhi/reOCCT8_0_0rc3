#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_OutOfRange.hpp>

#if !defined No_Exception && !defined No_Graphic3d_GroupDefinitionError
  #define Graphic3d_GroupDefinitionError_Raise_if(CONDITION, MESSAGE)                              \
    if (CONDITION)                                                                                 \
      throw Graphic3d_GroupDefinitionError(MESSAGE);
#else
  #define Graphic3d_GroupDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Graphic3d_GroupDefinitionError, Standard_OutOfRange)

