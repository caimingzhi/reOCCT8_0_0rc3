#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralExpression.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_NumericValue : public Expr_GeneralExpression
{

public:
  Standard_EXPORT Expr_NumericValue(const double val);

  Standard_EXPORT double GetValue() const;

  Standard_EXPORT void SetValue(const double val);

  Standard_EXPORT int NbSubExpressions() const override;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> ShallowSimplified() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Copy() const override;

  Standard_EXPORT bool ContainsUnknowns() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const override;

  Standard_EXPORT bool IsLinear() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Derivative(
    const occ::handle<Expr_NamedUnknown>& X) const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> NDerivative(
    const occ::handle<Expr_NamedUnknown>& X,
    const int                             N) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& vals) const override;

  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_NumericValue, Expr_GeneralExpression)

private:
  double myValue;
};
