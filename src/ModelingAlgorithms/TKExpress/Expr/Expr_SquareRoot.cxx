#include <Expr.hpp>
#include <Expr_Division.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Square.hpp>
#include <Expr_SquareRoot.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_SquareRoot, Expr_UnaryExpression)

Expr_SquareRoot::Expr_SquareRoot(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_SquareRoot::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::sqrt(myNVexp->GetValue()));
  }
  if (myexp->IsKind(STANDARD_TYPE(Expr_Square)))
  {
    return myexp->SubExpression(1);
  }
  occ::handle<Expr_SquareRoot> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_SquareRoot::Copy() const
{
  return new Expr_SquareRoot(Expr::CopyShare(Operand()));
}

bool Expr_SquareRoot::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_SquareRoot)))
  {
    return Operand()->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_SquareRoot::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_SquareRoot::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp   = Operand();
  occ::handle<Expr_GeneralExpression> myder   = myexp->Derivative(X);
  occ::handle<Expr_SquareRoot>        sq      = new Expr_SquareRoot(Expr::CopyShare(myexp));
  occ::handle<Expr_Product>           theprod = 2.0 * sq;
  occ::handle<Expr_Division>          resu    = myder / theprod->ShallowSimplified();
  return resu->ShallowSimplified();
}

double Expr_SquareRoot::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                 const NCollection_Array1<double>& vals) const
{
  return std::sqrt(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_SquareRoot::String() const
{
  TCollection_AsciiString str("Sqrt(");
  str += Operand()->String();
  str += ")";
  return str;
}
