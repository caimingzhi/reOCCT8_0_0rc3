#include <Expr_NamedUnknown.hpp>
#include <Expr_SingleRelation.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_SingleRelation, Expr_GeneralRelation)

void Expr_SingleRelation::SetFirstMember(const occ::handle<Expr_GeneralExpression>& exp)
{
  myFirstMember = exp;
}

void Expr_SingleRelation::SetSecondMember(const occ::handle<Expr_GeneralExpression>& exp)
{
  mySecondMember = exp;
}

occ::handle<Expr_GeneralExpression> Expr_SingleRelation::FirstMember() const
{
  return myFirstMember;
}

occ::handle<Expr_GeneralExpression> Expr_SingleRelation::SecondMember() const
{
  return mySecondMember;
}

bool Expr_SingleRelation::IsLinear() const
{
  if (!myFirstMember->IsLinear())
  {
    return false;
  }
  if (!mySecondMember->IsLinear())
  {
    return false;
  }
  return true;
}

bool Expr_SingleRelation::Contains(const occ::handle<Expr_GeneralExpression>& exp) const
{
  if (myFirstMember == exp)
  {
    return true;
  }
  if (mySecondMember == exp)
  {
    return true;
  }
  if (myFirstMember->Contains(exp))
  {
    return true;
  }
  return mySecondMember->Contains(exp);
}

void Expr_SingleRelation::Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                  const occ::handle<Expr_GeneralExpression>& with)
{
  if (myFirstMember == var)
  {
    SetFirstMember(with);
  }
  else
  {
    if (myFirstMember->Contains(var))
    {
      myFirstMember->Replace(var, with);
    }
  }
  if (mySecondMember == var)
  {
    SetSecondMember(with);
  }
  else
  {
    if (mySecondMember->Contains(var))
    {
      mySecondMember->Replace(var, with);
    }
  }
}

int Expr_SingleRelation::NbOfSubRelations() const
{
  return 0;
}

occ::handle<Expr_GeneralRelation> Expr_SingleRelation::SubRelation(const int) const
{
  throw Standard_OutOfRange();
}

int Expr_SingleRelation::NbOfSingleRelations() const
{
  return 1;
}
