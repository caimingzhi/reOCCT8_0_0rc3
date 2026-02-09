#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralExpression.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class Expr_NamedUnknown;

class Expr_PolyExpression : public Expr_GeneralExpression
{

public:
  Standard_EXPORT int NbOperands() const;

  const occ::handle<Expr_GeneralExpression>& Operand(const int index) const;

  Standard_EXPORT void SetOperand(const occ::handle<Expr_GeneralExpression>& exp, const int index);

  Standard_EXPORT int NbSubExpressions() const override;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  Standard_EXPORT bool ContainsUnknowns() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_PolyExpression, Expr_GeneralExpression)

protected:
  Standard_EXPORT Expr_PolyExpression();

  Standard_EXPORT void AddOperand(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT void RemoveOperand(const int index);

private:
  NCollection_Sequence<occ::handle<Expr_GeneralExpression>> myOperands;
};

inline const occ::handle<Expr_GeneralExpression>& Expr_PolyExpression::Operand(
  const int index) const
{
  return myOperands(index);
}
