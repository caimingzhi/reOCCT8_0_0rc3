#include <Expr.hpp>
#include <Expr_ArgSinh.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Sinh.hpp>
#include <Expr_Square.hpp>
#include <Expr_SquareRoot.hpp>
#include <Expr_Sum.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_ArgSinh, Expr_UnaryExpression)

Expr_ArgSinh::Expr_ArgSinh(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_ArgSinh::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> op = Operand();
  if (op->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> valop = occ::down_cast<Expr_NumericValue>(op);
    return new Expr_NumericValue(std::asinh(valop->GetValue()));
  }
  if (op->IsKind(STANDARD_TYPE(Expr_Sinh)))
  {
    return op->SubExpression(1);
  }
  occ::handle<Expr_ArgSinh> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_ArgSinh::Copy() const
{
  return new Expr_ArgSinh(Expr::CopyShare(Operand()));
}

bool Expr_ArgSinh::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_ArgSinh)))
  {
    return false;
  }
  occ::handle<Expr_GeneralExpression> op = Operand();
  return op->IsIdentical(Other->SubExpression(1));
}

bool Expr_ArgSinh::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_ArgSinh::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> op    = Operand();
  occ::handle<Expr_GeneralExpression> derop = op->Derivative(X);

  occ::handle<Expr_Square> sq = new Expr_Square(Expr::CopyShare(op));

  occ::handle<Expr_Sum> thesum = sq->ShallowSimplified() + 1.0;

  occ::handle<Expr_SquareRoot> theroot = new Expr_SquareRoot(thesum->ShallowSimplified());

  occ::handle<Expr_Division> thediv = derop / theroot->ShallowSimplified();

  return thediv->ShallowSimplified();
}

double Expr_ArgSinh::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                              const NCollection_Array1<double>&                         vals) const
{
  double val = Operand()->Evaluate(vars, vals);
  return std::log(val + std::sqrt(::Square(val) + 1.0));
}

TCollection_AsciiString Expr_ArgSinh::String() const
{
  TCollection_AsciiString str("ASinh(");
  str += Operand()->String();
  str += ")";
  return str;
}
