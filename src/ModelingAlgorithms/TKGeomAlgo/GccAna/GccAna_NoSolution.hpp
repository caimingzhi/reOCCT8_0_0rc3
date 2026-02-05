#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_GccAna_NoSolution
  #define GccAna_NoSolution_Raise_if(CONDITION, MESSAGE)                                           \
    if (CONDITION)                                                                                 \
      throw GccAna_NoSolution(MESSAGE);
#else
  #define GccAna_NoSolution_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(GccAna_NoSolution, Standard_Failure)
