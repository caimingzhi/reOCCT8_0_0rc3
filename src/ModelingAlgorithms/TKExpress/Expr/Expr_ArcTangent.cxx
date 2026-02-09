#include <Expr.hpp>
#include <Expr_ArcTangent.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Square.hpp>
#include <Expr_Sum.hpp>
#include <Expr_Tangent.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArcTangent, Expr_UnaryExpression)

Expr_ArcTangent::Expr_ArcTangent(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArcTangent::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::atan(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Tangent)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArcTangent> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArcTangent::Copy() const
{
  return new Expr_ArcTangent(Expr::CopyShare(Operand()));
}

bool Expr_ArcTangent::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArcTangent)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArcTangent::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArcTangent::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);

  occ::handle<Expr_Square> sq = new Expr_Square(Expr::CopyShare(op));

  occ::handle<Expr_Sum> thesum = 1.0 + sq->ShallowSimplified();

  occ::handle<Expr_Division> thediv = derop / thesum->ShallowSimplified();

  return thediv->ShallowSimplified();
}

double Expr_ArcTangent::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                 const NCollection_Array1<double>& vals) const
{
  return std::atan(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_ArcTangent::String() const
{
  TCollection_AsciiString str("ATan(");
  str += Operand()->String();
  str += ")";
  return str;
}
