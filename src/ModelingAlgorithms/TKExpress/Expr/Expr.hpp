#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class Expr_GeneralExpression;
class Expr_GeneralRelation;

//! This package describes the data structure of any
//! expression, relation or function used in mathematics.
//! It also describes the assignment of variables. Standard
//! mathematical functions are implemented such as
//! trigonometrics, hyperbolics, and log functions.
class Expr
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Expr_GeneralExpression> CopyShare(
    const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT static int NbOfFreeVariables(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT static int NbOfFreeVariables(const occ::handle<Expr_GeneralRelation>& exp);

  Standard_EXPORT static double Sign(const double val);
};
