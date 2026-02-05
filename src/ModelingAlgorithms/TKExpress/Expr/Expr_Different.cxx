#include <Expr.hpp>
#include <Expr_Different.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_GeneralRelation.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_Different, Expr_SingleRelation)

Expr_Different::Expr_Different(const occ::handle<Expr_GeneralExpression>& exp1,
                               const occ::handle<Expr_GeneralExpression>& exp2)
{
  SetFirstMember(exp1);
  SetSecondMember(exp2);
}

bool Expr_Different::IsSatisfied() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  fm                                     = fm->Simplified();
  sm                                     = sm->Simplified();
  return (!fm->IsIdentical(sm));
}

occ::handle<Expr_GeneralRelation> Expr_Different::Simplified() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  return new Expr_Different(fm->Simplified(), sm->Simplified());
}

void Expr_Different::Simplify()
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  SetFirstMember(fm->Simplified());
  SetSecondMember(sm->Simplified());
}

occ::handle<Expr_GeneralRelation> Expr_Different::Copy() const
{
  return new Expr_Different(Expr::CopyShare(FirstMember()), Expr::CopyShare(SecondMember()));
}

TCollection_AsciiString Expr_Different::String() const
{
  return FirstMember()->String() + " <> " + SecondMember()->String();
}
