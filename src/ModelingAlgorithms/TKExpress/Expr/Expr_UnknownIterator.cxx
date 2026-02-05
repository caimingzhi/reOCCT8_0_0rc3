#include <Expr.hpp>
#include <Expr_UnknownIterator.hpp>
#include <Standard_NoMoreObject.hpp>

Expr_UnknownIterator::Expr_UnknownIterator(const occ::handle<Expr_GeneralExpression>& exp)
{
  Perform(exp);
  myCurrent = 1;
}

void Expr_UnknownIterator::Perform(const occ::handle<Expr_GeneralExpression>& exp)
{
  if (exp->IsKind(STANDARD_TYPE(Expr_NamedUnknown)))
  {
    occ::handle<Expr_NamedUnknown> varexp = occ::down_cast<Expr_NamedUnknown>(exp);
    if (!myMap.Contains(varexp))
    {
      myMap.Add(varexp);
    }
  }
  int nbsub = exp->NbSubExpressions();
  for (int i = 1; i <= nbsub; i++)
  {
    Perform(exp->SubExpression(i));
  }
}

bool Expr_UnknownIterator::More() const
{
  return (myCurrent <= myMap.Extent());
}

void Expr_UnknownIterator::Next()
{
  if (!More())
  {
    throw Standard_NoMoreObject();
  }
  myCurrent++;
}

occ::handle<Expr_NamedUnknown> Expr_UnknownIterator::Value() const
{
  return myMap(myCurrent);
}
