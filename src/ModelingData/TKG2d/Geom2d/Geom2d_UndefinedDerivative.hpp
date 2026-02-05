#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Geom2d_UndefinedDerivative
  #define Geom2d_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)                                  \
    if (CONDITION)                                                                                 \
      throw Geom2d_UndefinedDerivative(MESSAGE);
#else
  #define Geom2d_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Geom2d_UndefinedDerivative, Standard_DomainError)
