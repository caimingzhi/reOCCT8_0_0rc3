#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Geom_UndefinedDerivative
  #define Geom_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)                                    \
    if (CONDITION)                                                                                 \
      throw Geom_UndefinedDerivative(MESSAGE);
#else
  #define Geom_UndefinedDerivative_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Geom_UndefinedDerivative, Standard_DomainError)

