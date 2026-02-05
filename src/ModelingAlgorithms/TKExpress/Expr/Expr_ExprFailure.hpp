#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

#if !defined No_Exception && !defined No_Expr_ExprFailure
  #define Expr_ExprFailure_Raise_if(CONDITION, MESSAGE)                                            \
    if (CONDITION)                                                                                 \
      throw Expr_ExprFailure(MESSAGE);
#else
  #define Expr_ExprFailure_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Expr_ExprFailure, Standard_Failure)
