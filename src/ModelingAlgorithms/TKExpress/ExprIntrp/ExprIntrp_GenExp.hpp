#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ExprIntrp_Generator.hpp>
class Expr_GeneralExpression;
class TCollection_AsciiString;

//! This class permits, from a string, to create any
//! kind of expression of package Expr by using
//! built-in functions such as Sin,Cos, etc, and by
//! creating variables.
class ExprIntrp_GenExp : public ExprIntrp_Generator
{

public:
  Standard_EXPORT static occ::handle<ExprIntrp_GenExp> Create();

  //! Processes given string.
  Standard_EXPORT void Process(const TCollection_AsciiString& str);

  //! Returns false if any syntax error has occurred during
  //! process.
  Standard_EXPORT bool IsDone() const;

  //! Returns expression generated. Raises an exception if
  //! IsDone answers false.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> Expression() const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_GenExp, ExprIntrp_Generator)

private:
  //! Creates an empty generator
  Standard_EXPORT ExprIntrp_GenExp();

  bool                                done;
  occ::handle<Expr_GeneralExpression> myExpression;
};
