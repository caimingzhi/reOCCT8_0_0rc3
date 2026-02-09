#include <Expr.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_InvalidAssignment.hpp>
#include <Expr_InvalidOperand.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NotAssigned.hpp>
#include <Expr_NotEvaluable.hpp>
#include <Expr_NumericValue.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_NamedUnknown, Expr_NamedExpression)

Expr_NamedUnknown::Expr_NamedUnknown(const TCollection_AsciiString& name)
{
  SetName(name);
  myExpression.Nullify();
}

const occ::handle<Expr_GeneralExpression>& Expr_NamedUnknown::AssignedExpression() const
{
  if (!IsAssigned())
  {
    throw Expr_NotAssigned();
  }
  return myExpression;
}

void Expr_NamedUnknown::Assign(const occ::handle<Expr_GeneralExpression>& exp)
{
  occ::handle<Expr_NamedUnknown> me = this;
  if (exp->Contains(me))
  {
    throw Expr_InvalidAssignment();
  }
  myExpression = exp;
}

const occ::handle<Expr_GeneralExpression>& Expr_NamedUnknown::SubExpression(const int I) const
{
  if (!IsAssigned())
  {
    throw Standard_OutOfRange();
  }
  if (I != 1)
  {
    throw Standard_OutOfRange();
  }
  return AssignedExpression();
}

occ::handle<Expr_GeneralExpression> Expr_NamedUnknown::Simplified() const
{
  if (!IsAssigned())
  {
    occ::handle<Expr_NamedUnknown> me = this;
    return me;
  }
  else
  {
    return myExpression->Simplified();
  }
}

occ::handle<Expr_GeneralExpression> Expr_NamedUnknown::Copy() const
{
  occ::handle<Expr_NamedUnknown> cop = new Expr_NamedUnknown(GetName());
  if (IsAssigned())
  {
    cop->Assign(Expr::CopyShare(myExpression));
  }
  return cop;
}

bool Expr_NamedUnknown::ContainsUnknowns() const
{
  if (IsAssigned())
  {
    if (myExpression->IsKind(STANDARD_TYPE(Expr_NamedUnknown)))
    {
      return true;
    }
    return myExpression->ContainsUnknowns();
  }
  else
  {
    return false;
  }
}

bool Expr_NamedUnknown::Contains(const occ::handle<Expr_GeneralExpression>& exp) const
{
  if (!IsAssigned())
  {
    const occ::handle<Expr_NamedUnknown> expNamed = occ::down_cast<Expr_NamedUnknown>(exp);
    if (expNamed.IsNull() || expNamed->IsAssigned())
      return false;

    return IsIdentical(expNamed);
  }
  if (myExpression == exp)
  {
    return true;
  }
  return myExpression->Contains(exp);
}

bool Expr_NamedUnknown::IsLinear() const
{
  if (IsAssigned())
  {
    return myExpression->IsLinear();
  }
  else
  {
    return true;
  }
}

occ::handle<Expr_GeneralExpression> Expr_NamedUnknown::Derivative(
  const occ::handle<Expr_NamedUnknown>& X) const
{
  occ::handle<Expr_NamedUnknown> me = this;
  if (!me->IsIdentical(X))
  {
    if (IsAssigned())
    {
      return myExpression->Derivative(X);
    }
    else
    {
      return new Expr_NumericValue(0.0);
    }
  }
  else
  {
    return new Expr_NumericValue(1.0);
  }
}

void Expr_NamedUnknown::Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                const occ::handle<Expr_GeneralExpression>& with)
{
  if (IsAssigned())
  {
    if (myExpression == var)
    {
      occ::handle<Expr_NamedUnknown> me = this;
      if (with->Contains(me))
      {
        throw Expr_InvalidOperand();
      }
      Assign(with);
    }
    else
    {
      if (myExpression->Contains(var))
      {
        myExpression->Replace(var, with);
      }
    }
  }
}

occ::handle<Expr_GeneralExpression> Expr_NamedUnknown::ShallowSimplified() const
{
  if (IsAssigned())
  {
    return myExpression;
  }
  occ::handle<Expr_NamedUnknown> me = this;
  return me;
}

double Expr_NamedUnknown::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                   const NCollection_Array1<double>& vals) const
{
  if (!IsAssigned())
  {
    occ::handle<Expr_NamedUnknown> me = this;
    for (int i = vars.Lower(); i <= vars.Upper(); i++)
    {
      if (me->GetName() == vars(i)->GetName())
      {
        return vals(i - vars.Lower() + vals.Lower());
      }
    }
    throw Expr_NotEvaluable();
  }
  return myExpression->Evaluate(vars, vals);
}

int Expr_NamedUnknown::NbSubExpressions() const
{
  if (IsAssigned())
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
