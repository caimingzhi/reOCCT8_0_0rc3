#include <Expr.hpp>
#include <Expr_ArgSinh.hpp>
#include <Expr_Cosh.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <Expr_Sinh.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Sinh, Expr_UnaryExpression)

Expr_Sinh::Expr_Sinh(const occ::handle<Expr_GeneralExpression>& exp)
{
  CreateOperand(exp);
}

occ::handle<Expr_GeneralExpression> Expr_Sinh::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myexp = Operand();
  if (myexp->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVexp = occ::down_cast<Expr_NumericValue>(myexp);
    return new Expr_NumericValue(std::sinh(myNVexp->GetValue()));
  }
  if (myexp->IsKind(STANDARD_TYPE(Expr_ArgSinh)))
  {
    return myexp->SubExpression(1);
  }
  occ::handle<Expr_Sinh> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Sinh::Copy() const
{
  return new Expr_Sinh(Expr::CopyShare(Operand()));
}

bool Expr_Sinh::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (Other->IsKind(STANDARD_TYPE(Expr_Sinh)))
  {
    occ::handle<Expr_GeneralExpression> myexp = Operand();
    return myexp->IsIdentical(Other->SubExpression(1));
  }
  return false;
}

bool Expr_Sinh::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Sinh::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myexp    = Operand();
  occ::handle<Expr_GeneralExpression> myder    = myexp->Derivative(X);
  occ::handle<Expr_Cosh>              firstder = new Expr_Cosh(Expr::CopyShare(myexp));
  occ::handle<Expr_Product>           resu     = firstder->ShallowSimplified() * myder;
  return resu->ShallowSimplified();
}

double Expr_Sinh::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                           const NCollection_Array1<double>&                         vals) const
{
  double val = Operand()->Evaluate(vars, vals);
  return (std::exp(val) - std::exp(-val)) / 2.0;
}

TCollection_AsciiString Expr_Sinh::String() const
{
  TCollection_AsciiString str("Sinh(");
  str += Operand()->String();
  str += ")";
  return str;
}
