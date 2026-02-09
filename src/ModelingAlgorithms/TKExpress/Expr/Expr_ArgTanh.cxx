#include <Expr.hpp>
#include <Expr_ArgTanh.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Square.hpp>
#include <Expr_Tanh.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArgTanh, Expr_UnaryExpression)

Expr_ArgTanh::Expr_ArgTanh(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArgTanh::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::atanh(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Tanh)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArgTanh> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArgTanh::Copy() const
{
  return new Expr_ArgTanh(Expr::CopyShare(Operand()));
}

bool Expr_ArgTanh::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArgTanh)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArgTanh::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArgTanh::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);

  occ::handle<Expr_Square> sq = new Expr_Square(Expr::CopyShare(op));

  occ::handle<Expr_Difference> thedif = 1.0 - sq->ShallowSimplified();

  occ::handle<Expr_Division> thediv = derop / thedif->ShallowSimplified();

  return thediv->ShallowSimplified();
}

double Expr_ArgTanh::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                              const NCollection_Array1<double>&                         vals) const
{
  double val = Operand()->Evaluate(vars, vals);
  return std::log((1.0 + val) / (1.0 - val)) / 2.0;
}

TCollection_AsciiString Expr_ArgTanh::String() const
{
  TCollection_AsciiString str("ATanh(");
  str += Operand()->String();
  str += ")";
  return str;
}
