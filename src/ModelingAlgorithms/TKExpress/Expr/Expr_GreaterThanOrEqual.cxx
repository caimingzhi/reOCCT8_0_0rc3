#include <Expr.hpp>
#include <Expr_GeneralExpression.hpp>
#include <Expr_GreaterThanOrEqual.hpp>
#include <Expr_NumericValue.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_GreaterThanOrEqual, Expr_SingleRelation)

Expr_GreaterThanOrEqual::Expr_GreaterThanOrEqual(const occ::handle<Expr_GeneralExpression>& exp1,
                                                 const occ::handle<Expr_GeneralExpression>& exp2)
{
  SetFirstMember(exp1);
  SetSecondMember(exp2);
}

bool Expr_GreaterThanOrEqual::IsSatisfied() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  fm                                     = fm->Simplified();
  sm                                     = sm->Simplified();
  if (fm->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    if (sm->IsKind(STANDARD_TYPE(Expr_NumericValue)))
    {
      occ::handle<Expr_NumericValue> nfm = occ::down_cast<Expr_NumericValue>(fm);
      occ::handle<Expr_NumericValue> nsm = occ::down_cast<Expr_NumericValue>(sm);
      return (nfm->GetValue() >= nsm->GetValue());
    }
  }
  return false;
}

occ::handle<Expr_GeneralRelation> Expr_GreaterThanOrEqual::Simplified() const
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  return new Expr_GreaterThanOrEqual(fm->Simplified(), sm->Simplified());
}

void Expr_GreaterThanOrEqual::Simplify()
{
  occ::handle<Expr_GeneralExpression> fm = FirstMember();
  occ::handle<Expr_GeneralExpression> sm = SecondMember();
  SetFirstMember(fm->Simplified());
  SetSecondMember(sm->Simplified());
}

occ::handle<Expr_GeneralRelation> Expr_GreaterThanOrEqual::Copy() const
{
  return new Expr_GreaterThanOrEqual(Expr::CopyShare(FirstMember()),
                                     Expr::CopyShare(SecondMember()));
}

TCollection_AsciiString Expr_GreaterThanOrEqual::String() const
{
  return FirstMember()->String() + " >= " + SecondMember()->String();
}
