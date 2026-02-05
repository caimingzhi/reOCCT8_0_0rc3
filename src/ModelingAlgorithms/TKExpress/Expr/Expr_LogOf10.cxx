#include <Expr.hpp>
#include <Expr_Division.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_LogOf10.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_LogOf10, Expr_UnaryExpression)

Expr_LogOf10::Expr_LogOf10(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_LogOf10::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::log10(myNVexp->GetValue()));
  }
  occ::handle<Expr_LogOf10> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_LogOf10::Copy() const
{
  return new Expr_LogOf10(Expr::CopyShare(Operand()));
}

bool Expr_LogOf10::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_LogOf10)))
  {
    occ::handle<Expr_GeneralExpression> myexp = Operand();
    return myexp->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_LogOf10::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_LogOf10::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp   = Operand();
  occ::handle<Expr_GeneralExpression> myder   = myexp->Derivative(X);
  double                              vlog    = std::log(10.0);
  occ::handle<Expr_NumericValue>      vallog  = new Expr_NumericValue(vlog);
  occ::handle<Expr_Product>           theprod = Expr::CopyShare(myexp) * vallog;
  occ::handle<Expr_Division>          thediv  = myder / theprod->ShallowSimplified();
  return thediv->ShallowSimplified();
}

double Expr_LogOf10::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                              const NCollection_Array1<double>&                         vals) const
{
  return std::log10(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_LogOf10::String() const
{
  TCollection_AsciiString str("log(");
  str += Operand()->String();
  str += ")";
  return str;
}
