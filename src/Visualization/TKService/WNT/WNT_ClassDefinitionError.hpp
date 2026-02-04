#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_ConstructionError.hpp>

#if !defined No_Exception && !defined No_WNT_ClassDefinitionError
  #define WNT_ClassDefinitionError_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw WNT_ClassDefinitionError(MESSAGE);
#else
  #define WNT_ClassDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(WNT_ClassDefinitionError, Standard_ConstructionError)

