#pragma once


#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Quantity_DateDefinitionError
  #define Quantity_DateDefinitionError_Raise_if(CONDITION, MESSAGE)                                \
    if (CONDITION)                                                                                 \
      throw Quantity_DateDefinitionError(MESSAGE);
#else
  #define Quantity_DateDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Quantity_DateDefinitionError, Standard_DomainError)

