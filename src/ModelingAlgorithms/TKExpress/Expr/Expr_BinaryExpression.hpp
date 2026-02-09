#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralExpression.hpp>
#include <Standard_Integer.hpp>
class Expr_NamedUnknown;

class Expr_BinaryExpression : public Expr_GeneralExpression
{

public:
  const occ::handle<Expr_GeneralExpression>& FirstOperand() const;

  const occ::handle<Expr_GeneralExpression>& SecondOperand() const;

  Standard_EXPORT void SetFirstOperand(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT void SetSecondOperand(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT int NbSubExpressions() const override;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  Standard_EXPORT bool ContainsUnknowns() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_BinaryExpression, Expr_GeneralExpression)

protected:
  Standard_EXPORT void CreateFirstOperand(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT void CreateSecondOperand(const occ::handle<Expr_GeneralExpression>& exp);

private:
  occ::handle<Expr_GeneralExpression> myFirstOperand;
  occ::handle<Expr_GeneralExpression> mySecondOperand;
};

inline const occ::handle<Expr_GeneralExpression>& Expr_BinaryExpression::FirstOperand() const
{
  return myFirstOperand;
}

inline const occ::handle<Expr_GeneralExpression>& Expr_BinaryExpression::SecondOperand() const
{
  return mySecondOperand;
}
