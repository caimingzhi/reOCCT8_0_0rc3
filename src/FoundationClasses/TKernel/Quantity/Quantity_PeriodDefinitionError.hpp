#pragma once

#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Quantity_PeriodDefinitionError
  #define Quantity_PeriodDefinitionError_Raise_if(CONDITION, MESSAGE)                              \
    if (CONDITION)                                                                                 \
      throw Quantity_PeriodDefinitionError(MESSAGE);
#else
  #define Quantity_PeriodDefinitionError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Quantity_PeriodDefinitionError, Standard_DomainError)
