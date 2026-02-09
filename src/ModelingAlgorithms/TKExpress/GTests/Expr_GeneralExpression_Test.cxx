

#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <ExprIntrp_GenExp.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

TEST(Expr_GeneralExpression_Test, OCC902_ExpressionDerivative)
{

  TCollection_AsciiString anExpStr("5");
  anExpStr.AssignCat("*x");
  anExpStr.Prepend("Exp(");
  anExpStr.AssignCat(")");

  occ::handle<ExprIntrp_GenExp> anExprIntrp = ExprIntrp_GenExp::Create();

  anExprIntrp->Process(anExpStr);

  ASSERT_TRUE(anExprIntrp->IsDone()) << "Expression interpretation should succeed";

  occ::handle<Expr_GeneralExpression> anExpr = anExprIntrp->Expression();
  ASSERT_FALSE(anExpr.IsNull()) << "Expression should not be null";

  occ::handle<Expr_NamedUnknown>      aVar     = new Expr_NamedUnknown("x");
  occ::handle<Expr_GeneralExpression> aNewExpr = anExpr->Derivative(aVar);

  ASSERT_FALSE(aNewExpr.IsNull()) << "Derivative should not be null";

  TCollection_AsciiString aDerivativeStr = aNewExpr->String();

  bool isCorrect = (aDerivativeStr == "Exp(5*x)*5") || (aDerivativeStr == "5*Exp(5*x)");

  EXPECT_TRUE(isCorrect) << "Derivative result was: " << aDerivativeStr.ToCString()
                         << ", expected either 'Exp(5*x)*5' or '5*Exp(5*x)'";
}
