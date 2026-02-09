#include <Expr.hpp>
#include <Expr_Difference.hpp>
#include <Expr_Exponentiate.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_LogOfe.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_Operators.hpp>
#include <Expr_Product.hpp>
#include <NCollection_Sequence.hpp>
#include <Expr_Sum.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Exponentiate, Expr_BinaryExpression)

Expr_Exponentiate::Expr_Exponentiate(const occ::handle<Expr_GeneralExpression>& exp1,
                                     const occ::handle<Expr_GeneralExpression>& exp2)
{
  CreateFirstOperand(exp1);
  CreateSecondOperand(exp2);
}

occ::handle<Expr_GeneralExpression> Expr_Exponentiate::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();

  if (mysecond->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVs  = occ::down_cast<Expr_NumericValue>(mysecond);
    double                         myvals = myNVs->GetValue();
    if (myvals == 0.0)
    {

      return new Expr_NumericValue(1.0);
    }
    if (myvals == 1.0)
    {

      return myfirst;
    }
    if (myfirst->IsKind(STANDARD_TYPE(Expr_NumericValue)))
    {
      occ::handle<Expr_NumericValue> myNVf = occ::down_cast<Expr_NumericValue>(myfirst);
      return new Expr_NumericValue(std::pow(myNVf->GetValue(), myvals));
    }
  }
  if (myfirst->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    occ::handle<Expr_NumericValue> myNVf  = occ::down_cast<Expr_NumericValue>(myfirst);
    double                         myValf = myNVf->GetValue();
    if (myValf == 1.0)
    {
      return myNVf;
    }
  }
  occ::handle<Expr_Exponentiate> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_Exponentiate::Copy() const
{
  return new Expr_Exponentiate(Expr::CopyShare(FirstOperand()), Expr::CopyShare(SecondOperand()));
}

bool Expr_Exponentiate::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  bool ident = false;
  if (Other->IsKind(STANDARD_TYPE(Expr_Exponentiate)))
  {
    occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
    occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();
    if (myfirst->IsIdentical(Other->SubExpression(1)))
    {
      if (mysecond->IsIdentical(Other->SubExpression(2)))
      {
        ident = true;
      }
    }
  }
  return ident;
}

bool Expr_Exponentiate::IsLinear() const
{
  return !ContainsUnknowns();
}

occ::handle<Expr_GeneralExpression> Expr_Exponentiate::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{

  if (!Contains(X))
  {
    return new Expr_NumericValue(0.0);
  }

  occ::handle<Expr_GeneralExpression> myfirst  = FirstOperand();
  occ::handle<Expr_GeneralExpression> mysecond = SecondOperand();

  occ::handle<Expr_GeneralExpression> myfder = myfirst->Derivative(X);
  occ::handle<Expr_GeneralExpression> mysder = mysecond->Derivative(X);

  NCollection_Sequence<occ::handle<Expr_GeneralExpression>> prod1;
  prod1.Append(Expr::CopyShare(mysecond));

  occ::handle<Expr_Difference>   difh1 = Expr::CopyShare(mysecond) - 1.0;
  occ::handle<Expr_Exponentiate> exp1 =
    new Expr_Exponentiate(Expr::CopyShare(myfirst), difh1->ShallowSimplified());
  prod1.Append(exp1->ShallowSimplified());

  prod1.Append(myfder);

  occ::handle<Expr_Product> firstmember = new Expr_Product(prod1);

  NCollection_Sequence<occ::handle<Expr_GeneralExpression>> prod2;
  occ::handle<Expr_Exponentiate>                            exp2 =
    new Expr_Exponentiate(Expr::CopyShare(myfirst), Expr::CopyShare(mysecond));
  prod2.Append(exp2->ShallowSimplified());

  occ::handle<Expr_LogOfe> log = new Expr_LogOfe(Expr::CopyShare(myfirst));
  prod2.Append(log->ShallowSimplified());
  prod2.Append(mysder);

  occ::handle<Expr_Product> secondmember = new Expr_Product(prod2);

  occ::handle<Expr_Sum> resu = firstmember->ShallowSimplified() + secondmember->ShallowSimplified();
  return resu->ShallowSimplified();
}

double Expr_Exponentiate::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                   const NCollection_Array1<double>& vals) const
{
  double res = FirstOperand()->Evaluate(vars, vals);
  return std::pow(res, SecondOperand()->Evaluate(vars, vals));
}

TCollection_AsciiString Expr_Exponentiate::String() const
{
  occ::handle<Expr_GeneralExpression> op1 = FirstOperand();
  occ::handle<Expr_GeneralExpression> op2 = SecondOperand();
  TCollection_AsciiString             str;
  if (op1->NbSubExpressions() > 1)
  {
    str = "(";
    str += op1->String();
    str += ")";
  }
  else
  {
    str = op1->String();
  }
  str += "^";
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
