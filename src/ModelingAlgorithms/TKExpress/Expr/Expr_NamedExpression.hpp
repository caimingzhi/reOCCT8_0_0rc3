#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <Expr_GeneralExpression.hpp>

class Expr_NamedExpression : public Expr_GeneralExpression
{

public:
  Standard_EXPORT const TCollection_AsciiString& GetName() const;

  Standard_EXPORT void SetName(const TCollection_AsciiString& name);

  Standard_EXPORT bool IsShareable() const override;

  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const override;

  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_NamedExpression, Expr_GeneralExpression)

private:
  TCollection_AsciiString myName;
};
