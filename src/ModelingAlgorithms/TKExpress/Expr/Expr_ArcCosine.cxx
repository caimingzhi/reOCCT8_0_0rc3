#include <Expr.hpp>
#include <Expr_ArcCosine.hpp>
#include <Expr_Cosine.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Square.hpp>
#include <Expr_SquareRoot.hpp>
#include <Expr_UnaryMinus.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArcCosine, Expr_UnaryExpression)

Expr_ArcCosine::Expr_ArcCosine(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArcCosine::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::acos(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Cosine)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArcCosine> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArcCosine::Copy() const
{
  return new Expr_ArcCosine(Expr::CopyShare(Operand()));
}

bool Expr_ArcCosine::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArcCosine)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArcCosine::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArcCosine::Derivative(
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

  occ::handle<Expr_SquareRoot> theroot = new Expr_SquareRoot(thedif->ShallowSimplified());

  occ::handle<Expr_UnaryMinus> theder = -(1.0 / theroot->ShallowSimplified());

  occ::handle<Expr_Product> result = theder->ShallowSimplified() * derop;

  return result->ShallowSimplified();
}

double Expr_ArcCosine::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                const NCollection_Array1<double>& vals) const
{
  return std::acos(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_ArcCosine::String() const
{
  TCollection_AsciiString str("ACos(");
  str += Operand()->String();
  str += ")";
  return str;
}
