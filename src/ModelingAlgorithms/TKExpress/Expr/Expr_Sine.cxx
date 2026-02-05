#include <Expr.hpp>
#include <Expr_ArcSine.hpp>
#include <Expr_Cosine.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Sine.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Sine, Expr_UnaryExpression)

Expr_Sine::Expr_Sine(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_Sine::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::sin(myNVexp->GetValue()));
  }
  if (myexp->IsKind(STANDARD_TYPE(Expr_ArcSine)))
  {
    return myexp->SubExpression(1);
  }
  occ::handle<Expr_Sine> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Sine::Copy() const
{
  return new Expr_Sine(Expr::CopyShare(Operand()));
}

bool Expr_Sine::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_Sine)))
  {
    occ::handle<Expr_GeneralExpression> myexp = Operand();
    return myexp->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_Sine::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Sine::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp    = Operand();
  occ::handle<Expr_GeneralExpression> myder    = myexp->Derivative(X);
  occ::handle<Expr_Cosine>            firstder = new Expr_Cosine(Expr::CopyShare(myexp));
  occ::handle<Expr_Product>           resu     = firstder->ShallowSimplified() * myder;
  return resu->ShallowSimplified();
}

double Expr_Sine::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                           const NCollection_Array1<double>&                         vals) const
{
  return std::sin(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_Sine::String() const
{
  TCollection_AsciiString str("Sin(");
  str += Operand()->String();
  str += ")";
  return str;
}
