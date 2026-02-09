#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ExprIntrp_Generator.hpp>
class Expr_GeneralExpression;
class TCollection_AsciiString;

class ExprIntrp_GenExp : public ExprIntrp_Generator
{

public:
  Standard_EXPORT static occ::handle<ExprIntrp_GenExp> Create();

  Standard_EXPORT void Process(const TCollection_AsciiString& str);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Expression() const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_GenExp, ExprIntrp_Generator)

private:
  Standard_EXPORT ExprIntrp_GenExp();

  bool                                done;
  occ::handle<Expr_GeneralExpression> myExpression;
};
