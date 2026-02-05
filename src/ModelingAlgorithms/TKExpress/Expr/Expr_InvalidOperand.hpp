#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Expr_ExprFailure.hpp>

#if !defined No_Exception && !defined No_Expr_InvalidOperand
  #define Expr_InvalidOperand_Raise_if(CONDITION, MESSAGE)                                         \
    if (CONDITION)                                                                                 \
      throw Expr_InvalidOperand(MESSAGE);
#else
  #define Expr_InvalidOperand_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Expr_InvalidOperand, Expr_ExprFailure)
