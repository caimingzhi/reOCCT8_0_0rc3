#pragma once

#include <Standard.hpp>

#include <Expr_SingleRelation.hpp>
class Expr_GeneralExpression;
class Expr_GeneralRelation;
class TCollection_AsciiString;

class Expr_Equal : public Expr_SingleRelation
{

public:
  Standard_EXPORT Expr_Equal(const occ::handle<Expr_GeneralExpression>& exp1,
                             const occ::handle<Expr_GeneralExpression>& exp2);

  Standard_EXPORT bool IsSatisfied() const override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> Simplified() const override;

  Standard_EXPORT void Simplify() override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> Copy() const override;

  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_Equal, Expr_SingleRelation)
};
