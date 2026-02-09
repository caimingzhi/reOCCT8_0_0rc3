#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_BinaryExpression.hpp>
#include <NCollection_Array1.hpp>
class Expr_GeneralFunction;
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_BinaryFunction : public Expr_BinaryExpression
{

public:
  Standard_EXPORT Expr_BinaryFunction(const occ::handle<Expr_GeneralFunction>&   func,
                                      const occ::handle<Expr_GeneralExpression>& exp1,
                                      const occ::handle<Expr_GeneralExpression>& exp2);

  Standard_EXPORT occ::handle<Expr_GeneralFunction> Function() const;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> ShallowSimplified() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Copy() const override;

  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const override;

  Standard_EXPORT bool IsLinear() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Derivative(
    const occ::handle<Expr_NamedUnknown>& X) const override;

  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& vals) const override;

  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_BinaryFunction, Expr_BinaryExpression)

private:
  occ::handle<Expr_GeneralFunction> myFunction;
};
