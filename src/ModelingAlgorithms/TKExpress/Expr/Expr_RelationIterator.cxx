#include <Expr_RelationIterator.hpp>
#include <Expr_SingleRelation.hpp>
#include <Expr_SystemRelation.hpp>
#include <Standard_NoMoreObject.hpp>
#include <Standard_NoSuchObject.hpp>

Expr_RelationIterator::Expr_RelationIterator(const occ::handle<Expr_GeneralRelation>& rel)
    : myRelation(1, rel->NbOfSingleRelations())
{
  if (rel->IsKind(STANDARD_TYPE(Expr_SingleRelation)))
  {
    myRelation(1) = occ::down_cast<Expr_SingleRelation>(rel);
  }
  else
  {
    int                               nbcur = 1;
    occ::handle<Expr_GeneralRelation> currel;
    for (int i = 1; i <= rel->NbOfSubRelations(); i++)
    {
      currel = rel->SubRelation(i);
      if (currel->IsKind(STANDARD_TYPE(Expr_SingleRelation)))
      {
        myRelation(nbcur) = occ::down_cast<Expr_SingleRelation>(currel);
        nbcur++;
      }
      else
      {
        Expr_RelationIterator subit(currel);
        while (subit.More())
        {
          myRelation(nbcur) = subit.Value();
          subit.Next();
          nbcur++;
        }
      }
    }
  }
  current = 1;
}

bool Expr_RelationIterator::More() const
{
  return (current <= myRelation.Length());
}

void Expr_RelationIterator::Next()
{
  if (!More())
  {
    throw Standard_NoMoreObject();
  }
  current++;
}

occ::handle<Expr_SingleRelation> Expr_RelationIterator::Value() const
{
  if (!More())
  {
    throw Standard_NoSuchObject();
  }
  return myRelation(current);
}
