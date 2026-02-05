#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_ExprIntrp_SyntaxError
  #define ExprIntrp_SyntaxError_Raise_if(CONDITION, MESSAGE)                                       \
    if (CONDITION)                                                                                 \
      throw ExprIntrp_SyntaxError(MESSAGE);
#else
  #define ExprIntrp_SyntaxError_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(ExprIntrp_SyntaxError, Standard_Failure)
