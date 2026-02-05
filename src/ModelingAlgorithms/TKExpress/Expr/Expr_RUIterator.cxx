#include <Expr.hpp>
#include <Expr_RelationIterator.hpp>
#include <Expr_RUIterator.hpp>
#include <Expr_SingleRelation.hpp>
#include <Expr_UnknownIterator.hpp>
#include <Standard_NoMoreObject.hpp>

Expr_RUIterator::Expr_RUIterator(const occ::handle<Expr_GeneralRelation>& rel)
{
  Expr_RelationIterator            ri(rel);
  occ::handle<Expr_SingleRelation> srel;
  occ::handle<Expr_NamedUnknown>   var;
  myCurrent = 1;
  while (ri.More())
  {
    srel = ri.Value();
    ri.Next();
    Expr_UnknownIterator ui1(srel->FirstMember());
    while (ui1.More())
    {
      var = ui1.Value();
      ui1.Next();
      if (!myMap.Contains(var))
      {
        myMap.Add(var);
      }
    }
    Expr_UnknownIterator ui2(srel->SecondMember());
    while (ui2.More())
    {
      var = ui2.Value();
      ui2.Next();
      if (!myMap.Contains(var))
      {
        myMap.Add(var);
      }
    }
  }
}

bool Expr_RUIterator::More() const
{
  return (myCurrent <= myMap.Extent());
}

void Expr_RUIterator::Next()
{
  if (!More())
  {
    throw Standard_NoMoreObject();
  }
  myCurrent++;
}

occ::handle<Expr_NamedUnknown> Expr_RUIterator::Value() const
{
  return myMap(myCurrent);
}
