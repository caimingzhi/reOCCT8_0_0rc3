#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <Expr.hpp>
#include <NCollection_Array1.hpp>
#include <Expr_FunctionDerivative.hpp>
#include <Expr_GeneralFunction.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NotEvaluable.hpp>
#include <Expr_Operators.hpp>
#include <Expr_PolyFunction.hpp>
#include <Expr_Product.hpp>
#include <Expr_Sum.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
class Expr_NamedUnknown;

IMPLEMENT_STANDARD_RTTIEXT(Expr_PolyFunction, Expr_PolyExpression)

Expr_PolyFunction::Expr_PolyFunction(
  const occ::handle<Expr_GeneralFunction>&                       func,
  const NCollection_Array1<occ::handle<Expr_GeneralExpression>>& exps)
{
  for (int i = exps.Lower(); i <= exps.Upper(); i++)
  {
    AddOperand(exps(i));
  }
  myFunction = func;
}

occ::handle<Expr_GeneralFunction> Expr_PolyFunction::Function() const
{
  return myFunction;
}

occ::handle<Expr_GeneralExpression> Expr_PolyFunction::ShallowSimplified() const
{
  bool allval = true;
  int  max    = NbSubExpressions();
  int  i;
  for (i = 1; (i <= max) && allval; i++)
  {
    allval = SubExpression(i)->IsKind(STANDARD_TYPE(Expr_NumericValue));
  }
  if (allval)
  {
    NCollection_Array1<double>                         tabval(1, max);
    NCollection_Array1<occ::handle<Expr_NamedUnknown>> tabvar(1, max);
    for (i = 1; i <= max; i++)
    {
      tabval(i) = occ::down_cast<Expr_NumericValue>(SubExpression(i))->GetValue();
      tabvar(i) = myFunction->Variable(i);
    }
    double res = myFunction->Evaluate(tabvar, tabval);
    return new Expr_NumericValue(res);
  }
  occ::handle<Expr_PolyFunction> me = this;
  return me;
}

occ::handle<Expr_GeneralExpression> Expr_PolyFunction::Copy() const
{
  int                                                     max = NbSubExpressions();
  NCollection_Array1<occ::handle<Expr_GeneralExpression>> vars(1, max);
  for (int i = 1; i <= max; i++)
  {
    vars(i) = Expr::CopyShare(SubExpression(i));
  }
  return new Expr_PolyFunction(myFunction, vars);
}

bool Expr_PolyFunction::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_PolyFunction)))
  {
    return false;
  }
  if (Other->NbSubExpressions() != NbSubExpressions())
  {
    return false;
  }
  occ::handle<Expr_PolyFunction>    pother = occ::down_cast<Expr_PolyFunction>(Other);
  occ::handle<Expr_GeneralFunction> fother = pother->Function();
  if (!fother->IsIdentical(Function()))
  {
    return false;
  }
  int                                 max = NbSubExpressions();
  occ::handle<Expr_GeneralExpression> opother;
  for (int i = 1; i <= max; i++)
  {
    opother = pother->SubExpression(i);
    if (!opother->IsIdentical(SubExpression(i)))
    {
      return false;
    }
  }
  return true;
}

bool Expr_PolyFunction::IsLinear() const
{
  if (!ContainsUnknowns())
  {
    return true;
  }
  for (int i = 1; i <= NbOperands(); i++)
  {
    if (!Operand(i)->IsLinear())
    {
      return false;
    }
    if (!myFunction->IsLinearOnVariable(i))
    {
      return false;
    }
  }
  return true;
}

occ::handle<Expr_GeneralExpression> Expr_PolyFunction::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  occ::handle<Expr_GeneralExpression>                     myop;
  occ::handle<Expr_NamedUnknown>                          thevar;
  occ::handle<Expr_GeneralFunction>                       partderfunc;
  occ::handle<Expr_PolyFunction>                          partder;
  occ::handle<Expr_Product>                               partprod;
  int                                                     max = NbSubExpressions();
  NCollection_Array1<occ::handle<Expr_GeneralExpression>> theops(1, max);
  for (int k = 1; k <= max; k++)
  {
    theops(k) = Operand(k);
  }
  NCollection_Sequence<occ::handle<Expr_GeneralExpression>> thesum;
  for (int i = 1; i <= max; i++)
  {
    thevar      = myFunction->Variable(i);
    myop        = SubExpression(i);
    partderfunc = myFunction->Derivative(thevar);
    partder     = new Expr_PolyFunction(partderfunc, theops);
    partprod    = partder->ShallowSimplified() * myop->Derivative(X);
    thesum.Append(partprod->ShallowSimplified());
  }
  occ::handle<Expr_Sum> res = new Expr_Sum(thesum);
  return res->ShallowSimplified();
}

double Expr_PolyFunction::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                   const NCollection_Array1<double>& vals) const
{
  int                                                max = NbSubExpressions();
  NCollection_Array1<occ::handle<Expr_NamedUnknown>> varsfunc(1, max);
  NCollection_Array1<double>                         valsfunc(1, max);
  for (int i = 1; i <= max; i++)
  {
    varsfunc(i) = myFunction->Variable(i);
    valsfunc(i) = SubExpression(i)->Evaluate(vars, vals);
  }
  return myFunction->Evaluate(varsfunc, valsfunc);
}

TCollection_AsciiString Expr_PolyFunction::String() const
{
  TCollection_AsciiString res = myFunction->GetStringName();
  res += "(";
  int max = NbOperands();
  for (int i = 1; i <= max; i++)
  {
    res += Operand(i)->String();
    if (i != max)
    {
      res += ",";
    }
  }
  res += ")";
  return res;
}
