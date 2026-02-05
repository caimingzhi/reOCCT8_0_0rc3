#include <Expr.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NumericValue.hpp>
#include <Expr_Sign.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Sign, Expr_UnaryExpression)

Expr_Sign::Expr_Sign(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_Sign::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(Expr::Sign(valop->GetValue()));
  }
  occ::handle<Expr_Sign> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Sign::Copy() const
{
  return new Expr_Sign(Expr::CopyShare(Operand()));
}

bool Expr_Sign::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_Sign)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_Sign::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Sign::Derivative(
  const occ::handle<Expr_NamedUnknown>&) const
{
  return new Expr_NumericValue(0.0);
}

double Expr_Sign::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                           const NCollection_Array1<double>&                         vals) const
{
  double res = Operand()->Evaluate(vars, vals);
  return Expr::Sign(res);
}

TCollection_AsciiString Expr_Sign::String() const
{
  TCollection_AsciiString str("Sign(");
  str += Operand()->String();
  str += ")";
  return str;
}
