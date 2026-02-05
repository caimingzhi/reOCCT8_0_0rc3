#include <Expr.hpp>
#include <Expr_Division.hpp>
#include <Expr_Exponential.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_LogOfe.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_LogOfe, Expr_UnaryExpression)

Expr_LogOfe::Expr_LogOfe(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_LogOfe::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::log(myNVexp->GetValue()));
  }
  if (myexp->IsKind(STANDARD_TYPE(Expr_Exponential)))
  {
    return myexp->SubExpression(1);
  }
  occ::handle<Expr_LogOfe> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_LogOfe::Copy() const
{
  return new Expr_LogOfe(Expr::CopyShare(Operand()));
}

bool Expr_LogOfe::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_LogOfe)))
  {
    occ::handle<Expr_GeneralExpression> myexp = Operand();
    return myexp->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_LogOfe::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_LogOfe::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp  = Operand();
  occ::handle<Expr_GeneralExpression> myder  = myexp->Derivative(X);
  occ::handle<Expr_Division>          thediv = myder / Expr::CopyShare(myexp);
  return thediv->ShallowSimplified();
}

double Expr_LogOfe::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                             const NCollection_Array1<double>&                         vals) const
{
  return std::log(Operand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_LogOfe::String() const
{
  TCollection_AsciiString str("Ln(");
  str += Operand()->String();
  str += ")";
  return str;
}
