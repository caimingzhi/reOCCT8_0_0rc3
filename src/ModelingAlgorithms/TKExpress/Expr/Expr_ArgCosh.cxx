#include <Expr.hpp>
#include <Expr_ArgCosh.hpp>
#include <Expr_Cosh.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Square.hpp>
#include <Expr_SquareRoot.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArgCosh, Expr_UnaryExpression)

Expr_ArgCosh::Expr_ArgCosh(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArgCosh::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::acosh(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Cosh)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArgCosh> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArgCosh::Copy() const
{
  return new Expr_ArgCosh(Expr::CopyShare(Operand()));
}

bool Expr_ArgCosh::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArgCosh)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArgCosh::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArgCosh::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);

  occ::handle<Expr_Square> sq = new Expr_Square(Expr::CopyShare(op));
  // X2 - 1
  occ::handle<Expr_Difference> thedif = sq->ShallowSimplified() - 1.0;

  // sqrt(X2 - 1)
  occ::handle<Expr_SquareRoot> theroot = new Expr_SquareRoot(thedif->ShallowSimplified());

  // ArgCosh'(F(X)) = F'(X)/sqrt(F(X)2-1)
  occ::handle<Expr_Division> thediv = derop / theroot->ShallowSimplified();

  return thediv->ShallowSimplified();
}

double Expr_ArgCosh::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                              const NCollection_Array1<double>&                         vals) const
{
  double val = Operand()->Evaluate(vars, vals);
  return std::log(val + std::sqrt(::Square(val) - 1.0));
}

TCollection_AsciiString Expr_ArgCosh::String() const
{
  TCollection_AsciiString str("ACosh(");
  str += Operand()->String();
  str += ")";
  return str;
}
