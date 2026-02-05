#include <Expr.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_GeneralRelation.hpp>
#include <Expr_UnknownIterator.hpp>
#include <Expr_RUIterator.hpp>

occ::handle<Expr_GeneralExpression> Expr::CopyShare(const occ::handle<Expr_GeneralExpression>& exp)
{
  if (exp->IsShareable())
  {
    return exp;
  }
  return exp->Copy();
}

int Expr::NbOfFreeVariables(const occ::handle<Expr_GeneralRelation>& rel)
{
  int             nbvar = 0;
  Expr_RUIterator rit(rel);
  while (rit.More())
  {
    if (!rit.Value()->IsAssigned())
    {
      nbvar++;
    }
    rit.Next();
  }
  return nbvar;
}

int Expr::NbOfFreeVariables(const occ::handle<Expr_GeneralExpression>& exp)
{
  int                  nbvar = 0;
  Expr_UnknownIterator uit(exp);
  while (uit.More())
  {
    if (!uit.Value()->IsAssigned())
    {
      nbvar++;
    }
    uit.Next();
  }
  return nbvar;
}

double Expr::Sign(const double val)
{
  return std::copysign(1.0, val);
}
