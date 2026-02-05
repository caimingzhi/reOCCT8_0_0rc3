#include <Expr_InvalidOperand.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_UnaryExpression.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_UnaryExpression, Expr_GeneralExpression)

void Expr_UnaryExpression::SetOperand(const occ::handle<Expr_GeneralExpression>& exp)
{
  occ::handle<Expr_UnaryExpression> me = this;
  if (exp == me)
  {
    throw Expr_InvalidOperand();
  }
  if (exp->Contains(me))
  {
    throw Expr_InvalidOperand();
  }
  myOperand = exp;
}

void Expr_UnaryExpression::CreateOperand(const occ::handle<Expr_GeneralExpression>& exp)
{
  myOperand = exp;
}

int Expr_UnaryExpression::NbSubExpressions() const
{
  return 1;
}

const occ::handle<Expr_GeneralExpression>& Expr_UnaryExpression::SubExpression(const int I) const
{
  if (I != 1)
  {
    throw Standard_OutOfRange();
  }
  return myOperand;
}

bool Expr_UnaryExpression::ContainsUnknowns() const
{
  if (!myOperand->IsKind(STANDARD_TYPE(Expr_NamedUnknown)))
  {
    return myOperand->ContainsUnknowns();
  }
  return true;
}

bool Expr_UnaryExpression::Contains(const occ::handle<Expr_GeneralExpression>& exp) const
{
  if (myOperand != exp)
  {
    return myOperand->Contains(exp);
  }
  return true;
}

void Expr_UnaryExpression::Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                   const occ::handle<Expr_GeneralExpression>& with)
{
  if (myOperand == var)
  {
    SetOperand(with);
  }
  else
  {
    if (myOperand->Contains(var))
    {
      myOperand->Replace(var, with);
    }
  }
}

occ::handle<Expr_GeneralExpression> Expr_UnaryExpression::Simplified() const
{
  occ::handle<Expr_UnaryExpression>   cop = occ::down_cast<Expr_UnaryExpression>(Copy());
  occ::handle<Expr_GeneralExpression> op  = cop->Operand();
  cop->SetOperand(op->Simplified());
  return cop->ShallowSimplified();
}
