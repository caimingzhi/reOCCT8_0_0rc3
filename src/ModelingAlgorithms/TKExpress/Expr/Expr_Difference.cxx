#include <Expr.hpp>
#include <Expr_Difference.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Sum.hpp>
#include <Expr_UnaryMinus.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Difference, Expr_BinaryExpression)

Expr_Difference::Expr_Difference(const occ::handle<Expr_GeneralExpression>& exp1,
                                 const occ::handle<Expr_GeneralExpression>& exp2)
{
  CreateFirstOperand(exp1);
  CreateSecondOperand(exp2);
}

occ::handle<Expr_GeneralExpression> Expr_Difference::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();

  bool nvfirst  = myfirst->IsKind(STANDARD_TYPE(Expr_NumericValue));
  bool nvsecond = mysecond->IsKind(STANDARD_TYPE(Expr_NumericValue));
  if (nvfirst && nvsecond)
  {

    occ::handle<Expr_NumericValue> myNVfirst  = occ::down_cast<Expr_NumericValue>(myfirst);
    occ::handle<Expr_NumericValue> myNVsecond = occ::down_cast<Expr_NumericValue>(mysecond);
    return new Expr_NumericValue(myNVfirst->GetValue() - myNVsecond->GetValue());
  }
  if (nvfirst && !nvsecond)
  {

    occ::handle<Expr_NumericValue> myNVfirst = occ::down_cast<Expr_NumericValue>(myfirst);
    if (myNVfirst->GetValue() == 0.0)
    {

      return -mysecond;
    }
  }
  if (!nvfirst && nvsecond)
  {

    occ::handle<Expr_NumericValue> myNVsecond = occ::down_cast<Expr_NumericValue>(mysecond);
    if (myNVsecond->GetValue() == 0.0)
    {

      return myfirst;
    }
  }

  bool unfirst  = myfirst->IsKind(STANDARD_TYPE(Expr_UnaryMinus));
  bool unsecond = mysecond->IsKind(STANDARD_TYPE(Expr_UnaryMinus));
  if (unfirst && unsecond)
  {

    occ::handle<Expr_GeneralExpression> ssop1 = myfirst->SubExpression(1);
    occ::handle<Expr_GeneralExpression> ssop2 = mysecond->SubExpression(1);
    return ssop2 - ssop1;
  }
  if (unfirst && !unsecond)
  {

    occ::handle<Expr_GeneralExpression> ssop1 = myfirst->SubExpression(1);
    return -(ssop1 + mysecond);
  }
  if (!unfirst && unsecond)
  {

    occ::handle<Expr_GeneralExpression> ssop2 = mysecond->SubExpression(1);
    return myfirst + ssop2;
  }
  occ::handle<Expr_Difference> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Difference::Copy() const
{
  return Expr::CopyShare(FirstOperand()) - Expr::CopyShare(SecondOperand());
}

bool Expr_Difference::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  bool ident = false;
  if (Other->IsKind(STANDARD_TYPE(Expr_Difference)))
  {
    occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
    occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();
    occ::handle<Expr_Difference>        DOther   = occ::down_cast<Expr_Difference>(Other);
    occ::handle<Expr_GeneralExpression> fother   = DOther->FirstOperand();
    occ::handle<Expr_GeneralExpression> sother   = DOther->SecondOperand();
    if ((myfirst->IsIdentical(fother)) && (mysecond->IsIdentical(sother)))
    {
      ident = true;
    }
  }
  return ident;
}

bool Expr_Difference::IsLinear() const
{
  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();
  return (myfirst->IsLinear() && mysecond->IsLinear());
}

occ::handle<Expr_GeneralExpression> Expr_Difference::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();

  myfirst                          = myfirst->Derivative(X);
  mysecond                         = mysecond->Derivative(X);
  occ::handle<Expr_Difference> der = myfirst - mysecond;
  return der->ShallowSimplified();
}

occ::handle<Expr_GeneralExpression> Expr_Difference::NDerivative(
  const occ::handle<Expr_NamedUnknown>& X,
  const int                             N) const
{
  if (N <= 0)
  {
    throw Standard_OutOfRange();
  }
  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }
  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();

  myfirst                          = myfirst->NDerivative(X, N);
  mysecond                         = mysecond->NDerivative(X, N);
  occ::handle<Expr_Difference> der = myfirst - mysecond;
  return der->ShallowSimplified();
}

double Expr_Difference::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                 const NCollection_Array1<double>& vals) const
{
  double res = FirstOperand()->Evaluate(vars, vals);
  return res - SecondOperand()->Evaluate(vars, vals);
}

TCollection_AsciiString Expr_Difference::String() const
{
  occ::handle<Expr_GeneralExpression> op1 = FirstOperand();
  occ::handle<Expr_GeneralExpression> op2 = SecondOperand();
  TCollection_AsciiString             str;
  if (op1->NbSubExpressions() > 1)
  {
    str += "(";
    str += op1->String();
    str += ")";
  }
  else
  {
    str = op1->String();
  }
  str += "-";
  if (op2->NbSubExpressions() > 1)
  {
    str += "(";
    str += op2->String();
    str += ")";
  }
  else
  {
    str += op2->String();
  }
  return str;
}
