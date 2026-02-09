#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralExpression.hpp>
#include <Standard_Integer.hpp>
class Expr_NamedUnknown;

class Expr_UnaryExpression : public Expr_GeneralExpression
{

public:
  const occ::handle<Expr_GeneralExpression>& Operand() const;

  Standard_EXPORT void SetOperand(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT int NbSubExpressions() const override;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  Standard_EXPORT bool ContainsUnknowns() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_UnaryExpression, Expr_GeneralExpression)

protected:
  Standard_EXPORT void CreateOperand(const occ::handle<Expr_GeneralExpression>& exp);

private:
  occ::handle<Expr_GeneralExpression> myOperand;
};

inline const occ::handle<Expr_GeneralExpression>& Expr_UnaryExpression::Operand() const
{
  return myOperand;
}
