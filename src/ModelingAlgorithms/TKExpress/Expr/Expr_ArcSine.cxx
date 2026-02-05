#include <Expr.hpp>
#include <Expr_ArcSine.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Sine.hpp>
#include <Expr_Square.hpp>
#include <Expr_SquareRoot.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArcSine, Expr_UnaryExpression)

Expr_ArcSine::Expr_ArcSine(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArcSine::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::asin(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Sine)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArcSine> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArcSine::Copy() const
{
  return new Expr_ArcSine(Expr::CopyShare(Operand()));
}

bool Expr_ArcSine::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArcSine)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArcSine::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArcSine::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);

  occ::handle<Expr_Square> sq = new Expr_Square(Expr::CopyShare(op));
  // 1 - X2
  occ::handle<Expr_Difference> thedif = 1.0 - sq->ShallowSimplified();

  // sqrt(1-X2)
  occ::handle<Expr_SquareRoot> theroot = new Expr_SquareRoot(thedif->ShallowSimplified());

  // ArcSine'(F(X)) = F'(X)/sqrt(1-F(X)2)
  occ::handle<Expr_Division> thediv = derop / theroot->ShallowSimplified();

  return thediv->ShallowSimplified();
}

double Expr_ArcSine::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                              const NCollection_Array1<double>&                         vals) const
{
  return std::asin(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_ArcSine::String() const
{
  TCollection_AsciiString str("ASin(");
  str += Operand()->String();
  str += ")";
  return str;
}
