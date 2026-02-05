#include <Expr.hpp>
#include <Expr_ArcCosine.hpp>
#include <Expr_Cosine.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Sine.hpp>
#include <Expr_UnaryMinus.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Cosine, Expr_UnaryExpression)

Expr_Cosine::Expr_Cosine(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_Cosine::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::cos(myNVexp->GetValue()));
  }
  if (myexp->IsKind(STANDARD_TYPE(Expr_ArcCosine)))
  {
    return myexp->SubExpression(1);
  }
  occ::handle<Expr_Cosine> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Cosine::Copy() const
{
  return new Expr_Cosine(Expr::CopyShare(Operand()));
}

bool Expr_Cosine::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_Cosine)))
  {
    occ::handle<Expr_GeneralExpression> myexp = Operand();
    return myexp->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_Cosine::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Cosine::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp    = Operand();
  occ::handle<Expr_GeneralExpression> myder    = myexp->Derivative(X);
  occ::handle<Expr_Sine>              firstder = new Expr_Sine(Expr::CopyShare(myexp));
  occ::handle<Expr_UnaryMinus>        fder     = -(firstder->ShallowSimplified());
  occ::handle<Expr_Product>           resu     = fder->ShallowSimplified() * myder;
  return resu->ShallowSimplified();
}

double Expr_Cosine::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                             const NCollection_Array1<double>&                         vals) const
{
  return std::cos(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_Cosine::String() const
{
  TCollection_AsciiString str("Cos(");
  str += Operand()->String();
  str += ")";
  return str;
}
