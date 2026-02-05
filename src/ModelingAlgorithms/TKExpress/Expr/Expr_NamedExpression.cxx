#include <Expr_NamedExpression.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_NamedExpression, Expr_GeneralExpression)

//=================================================================================================

const TCollection_AsciiString& Expr_NamedExpression::GetName() const
{
  return myName;
}

//=================================================================================================

void Expr_NamedExpression::SetName(const TCollection_AsciiString& name)
{
  myName = name;
}

//=================================================================================================

bool Expr_NamedExpression::IsShareable() const
{
  return true;
}

//=================================================================================================

bool Expr_NamedExpression::IsIdentical(const occ::handle<Expr_GeneralExpression>& theOther) const
{
  bool aResult(false);
  if (theOther->IsKind(STANDARD_TYPE(Expr_NamedExpression)))
  {
    //  occ::handle<Expr_NamedExpression> me = this;
    //  occ::handle<Expr_NamedExpression> NEOther = occ::down_cast<Expr_NamedExpression>(Other);
    //  return  (me == NEOther);

    // AGV 22.03.12: Comparison should be based on names rather than Handles
    const Expr_NamedExpression* pOther = static_cast<const Expr_NamedExpression*>(theOther.get());
    if (pOther == this || pOther->GetName().IsEqual(myName))
      aResult = true;
  }
  return aResult;
}

TCollection_AsciiString Expr_NamedExpression::String() const
{
  return GetName();
}
