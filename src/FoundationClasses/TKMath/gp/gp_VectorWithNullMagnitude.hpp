#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_gp_VectorWithNullMagnitude
  #define gp_VectorWithNullMagnitude_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw gp_VectorWithNullMagnitude(MESSAGE);
#else
  #define gp_VectorWithNullMagnitude_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(gp_VectorWithNullMagnitude, Standard_DomainError)
