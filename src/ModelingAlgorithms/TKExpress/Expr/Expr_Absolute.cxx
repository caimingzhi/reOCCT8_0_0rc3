#include <Expr.hpp>
#include <Expr_Absolute.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Sign.hpp>
#include <Expr_UnaryMinus.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Absolute, Expr_UnaryExpression)

Expr_Absolute::Expr_Absolute(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_Absolute::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::abs(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_UnaryMinus)))
  {
    return new Expr_Absolute(op->SubExpression(1));
  }
  occ::handle<Expr_Absolute> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Absolute::Copy() const
{
  return new Expr_Absolute(Expr::CopyShare(Operand()));
}

bool Expr_Absolute::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_Absolute)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_Absolute::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Absolute::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);
  occ::handle<Expr_Sign>              myder = new Expr_Sign(Expr::CopyShare(op));
  occ::handle<Expr_Product>           resul = myder->ShallowSimplified() * derop;
  return resul->ShallowSimplified();
}

double Expr_Absolute::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                               const NCollection_Array1<double>&                         vals) const
{
  return std::abs(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_Absolute::String() const
{
  TCollection_AsciiString str("Abs(");
  str += Operand()->String();
  str += ")";
  return str;
}
