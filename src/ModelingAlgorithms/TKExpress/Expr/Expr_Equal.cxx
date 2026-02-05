#include <Expr.hpp>
#include <Expr_Equal.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_GeneralRelation.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Equal, Expr_SingleRelation)

Expr_Equal::Expr_Equal(const occ::handle<Expr_GeneralExpression>& exp1,
                       const occ::handle<Expr_GeneralExpression>& exp2)
{
  SetFirstMember(exp1);
  SetSecondMember(exp2);
}

bool Expr_Equal::IsSatisfied() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  fm                                     = fm->Simplified();
  sm                                     = sm->Simplified();
  return (fm->IsIdentical(sm));
}

occ::handle<Expr_GeneralRelation> Expr_Equal::Simplified() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  return new Expr_Equal(fm->Simplified(), sm->Simplified());
}

void Expr_Equal::Simplify()
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  SetFirstMember(fm->Simplified());
  SetSecondMember(sm->Simplified());
}

occ::handle<Expr_GeneralRelation> Expr_Equal::Copy() const
{
  return new Expr_Equal(Expr::CopyShare(FirstMember()), Expr::CopyShare(SecondMember()));
}

TCollection_AsciiString Expr_Equal::String() const
{
  return FirstMember()->String() + " = " + SecondMember()->String();
}
