#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NotEvaluable.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_GeneralExpression, Standard_Transient)

bool Expr_GeneralExpression::IsShareable() const
{
  return false;
}

occ::handle<Expr_GeneralExpression> Expr_GeneralExpression::NDerivative(
  const occ::handle<Expr_NamedUnknown>& X,
  const int                             N) const
{
  if (N <= 0)
  {
    throw Standard_OutOfRange();
  }
  occ::handle<Expr_GeneralExpression> first = Derivative(X);
  if (N > 1)
  {
    return first->NDerivative(X, N - 1);
  }
  return first;
}

double Expr_GeneralExpression::EvaluateNumeric() const
{
  if (ContainsUnknowns())
  {
    throw Expr_NotEvaluable();
  }
  NCollection_Array1<occ::handle<Expr_NamedUnknown>> tabvr(1, 1);
  NCollection_Array1<double>                         tabvl(1, 1);
  return Evaluate(tabvr, tabvl);
}
